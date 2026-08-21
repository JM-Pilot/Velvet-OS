#include <kernel/requests.h>
#include <drivers/uart/serial_con.h>
#include <drivers/video/framebuffer.h>
#include <arch/x86_64/cpu.h>
#include <utils/psf.h>
#include <drivers/video/vdcon.h>
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

	vdcon_puts("Hello World!\n");
	vdcon_switch_font(PSF_TER_U22N);
	vdcon_puts("Hello World!\n");


	cpu_hang();
}
