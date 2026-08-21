#include <kernel/requests.h>
#include <drivers/uart/serial_con.h>
#include <drivers/video/framebuffer.h>
#include <arch/x86_64/cpu.h>
#include <utils/psf.h>

extern uint8_t _binary_assets_ter_u16n_psf_start[];
extern uint8_t _binary_assets_ter_u22n_psf_start[];

void kernel_main(void)
{
	serial_con_init();
	if (check_revision() == 1) {
		serial_con_puts("REVISION NOT SUPPORTED, HANGING\n");
		cpu_hang();
	}
	serial_con_puts("Hi ;)\n");
	framebuffer_init();

	psf1_draw_char(_binary_assets_ter_u16n_psf_start, 'A', 10, 10, 0xFFFFFF, 0);
	psf2_draw_char(_binary_assets_ter_u22n_psf_start, 'B', 10, 25, 0xFFFFFF, 0);
	cpu_hang();
}
