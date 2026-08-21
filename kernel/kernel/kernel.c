#include <kernel/requests.h>
#include <drivers/uart/serial_con.h>
#include <drivers/video/framebuffer.h>
#include <arch/x86_64/cpu.h>
#include <utils/psf.h>
#include <drivers/video/vdcon.h>
#include <kernel/kernel.h>
void kernel_main(void)
{
	serial_con_init();
	if (check_revision() == 1) {
		serial_con_puts("REVISION NOT SUPPORTED, HANGING\n");
		cpu_hang();
	}
	serial_con_puts("Hi ;)\n");
	framebuffer_init();
	vdcon_init();
	vdcon_switch_font(PSF_TER_U22N);

	klog(0, "vdcon Initialized\n");

	cpu_hang();
}

void klog(int lvl, const char *msg)
{
	/* reserve 0 for nothing ;) */
	switch (lvl) {
		case 1:
			vdcon_set_fg(0xd68720);
			break;
		case 2:
			vdcon_set_fg(0xe03731);
			break;
	}
	vdcon_puts(msg);
	serial_con_puts(msg);
	
	vdcon_set_fg(0xFFFFFF);
}