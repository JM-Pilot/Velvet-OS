#include <kernel/requests.h>
#include <drivers/uart/serial_con.h>
#include <drivers/video/framebuffer.h>
#include <arch/x86_64/cpu.h>

void kernel_main(void)
{
	serial_con_init();
	if (check_revision() == 1) {
		serial_con_puts("REVISION NOT SUPPORTED, HANGING\n");
		cpu_hang();
	}
	serial_con_puts("Hi ;)\n");
	framebuffer_init();

	
	for (int i = 0; i < 128; i++)
		framebuffer_plot_pixel(0x00FF00, i, i);
	
	for (;;);
}
