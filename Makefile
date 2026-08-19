OUTPUT = velvetOS
KERNEL = kernel
TOOLS = tools
BOOT = boot
BIN = bin
ISO_BUILD = $(BIN)/iso_build
all: kernel

# Get necessary tools

# OVMF: UEFI 
ovmf: $(TOOLS)/edk2-ovmf-bins
$(TOOLS)/edk2-ovmf-bins:
	curl -L --progress-bar \
	https://github.com/osdev0/edk2-ovmf-stable-bins/releases/latest/download/edk2-ovmf-bins.tar.gz \
	| gunzip | tar -xf - --one-top-level=$(TOOLS)

# LIMINE: Protocol and Bootloaded
limine-binaries: $(TOOLS)/limine-binary
$(TOOLS)/limine-binary:
	curl -L --progress-bar \
	https://github.com/Limine-Bootloader/Limine/releases/latest/download/limine-binary.tar.gz \
	| gunzip | tar -xf - --one-top-level=$(TOOLS)
	$(MAKE) -C $(TOOLS)/limine-binary

# Compile the kernel ;)
.PHONY: kernel
kernel:
	$(MAKE) -C $(KERNEL) OUTPUT="$(OUTPUT)"

# Make the iso
.PHONY: iso
iso: $(BIN)/$(OUTPUT).iso
$(BIN)/$(OUTPUT).iso: kernel limine-binaries
	@echo "Building ISO"
	@mkdir -p $(ISO_BUILD)/boot/limine
	@cp $(BOOT)/limine.conf $(ISO_BUILD)/boot/limine
	@cp $(BIN)/$(OUTPUT)-kernel.elf $(ISO_BUILD)
	@cp $(TOOLS)/limine-binary/*.bin $(ISO_BUILD)/boot/limine
	@cp $(TOOLS)/limine-binary/limine-bios.sys $(ISO_BUILD)/boot/limine
	@cp $(TOOLS)/limine-binary/BOOTX64.EFI $(ISO_BUILD)/boot/limine
	@xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		$(ISO_BUILD) -o $@ 2>/dev/null
	@./$(TOOLS)/limine-binary/limine bios-install $@ 2>/dev/null
	@echo "Finished Building ISO."
	@echo "Final Image: $@"


# Run / Emulate
QEMU_FLAGS = \
	-M q35,accel=kvm \
	-cpu host \
	-d int,cpu_reset -D $(BIN)/QEMU_LOGS.txt \
	-serial stdio
run-bios: iso
	qemu-system-x86_64 \
		-cdrom $(BIN)/$(OUTPUT).iso \
		-boot d \
		$(QEMU_FLAGS)

run-uefi: run-efi
run-efi: iso ovmf
	qemu-system-x86_64 \
		-drive if=pflash,unit=0,format=raw,file=$(TOOLS)/edk2-ovmf-bins/ovmf-code-x86_64.fd,readonly=on \
		-cdrom $(BIN)/$(OUTPUT).iso \
		-boot d \
		$(QEMU_FLAGS)
# Clean up :D
clean:
	rm -rf $(BIN)
clean-tools:
	rm -rf $(TOOLS)