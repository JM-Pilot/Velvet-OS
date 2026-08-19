#include <drivers/video/framebuffer.h>
#include <kernel/requests.h>
#include <stdint.h>
#include <limine.h>
#include <stddef.h>
#include <drivers/uart/serial_con.h>
#include <arch/x86_64/cpu.h>

struct limine_framebuffer *framebuffer;

/* This points to the address where we can draw */
static uint32_t *video_ptr;


void framebuffer_init(void)
{
	if (framebuffer_request.response == NULL 
		|| framebuffer_request.response->framebuffer_count < 1) {
		serial_con_puts("framebuffer_request, invalid!\nhanging...");
		cpu_hang();
	}
	framebuffer = framebuffer_request.response->framebuffers[0];
	video_ptr = framebuffer->address;
}

void framebuffer_plot_pixel(uint32_t color, uint64_t x, uint64_t y)
{
	video_ptr[y * (framebuffer->pitch / 4) + x] = color;
}

uint32_t framebuffer_get_color(uint64_t x, uint64_t y)
{
	return video_ptr[y * (framebuffer->pitch / 4) + x];
}

void framebuffer_fill(uint32_t color)
{
	for (uint64_t y = 0; y < framebuffer->height; y++) {
		for (uint64_t x = 0; x < framebuffer->width; x++)
			framebuffer_plot_pixel(color, x, y);
	}
}