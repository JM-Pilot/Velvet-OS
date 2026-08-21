#include <drivers/video/vdcon.h>
#include <drivers/video/framebuffer.h>
#include <stdint.h>
#include <utils/psf.h>
#include <stdbool.h>

#define TAB_WIDTH 8

static uint64_t cursor_x, cursor_y;
static uint32_t fg, bg;
static uint32_t font_width, font_height;
static uint8_t *font = PSF_TER_U16N;
static uint64_t max_char_x, max_char_y;
static bool font_is_psf1;

void vdcon_init(void)
{
	cursor_x = 0;
	cursor_y = 0;
	fg = 0xFFFFFF;
	bg = 0;

	font_width = psf_get_width(font);
	font_height = psf_get_height(font);

	max_char_x = framebuffer->width / font_width;
	max_char_y = framebuffer->height / font_height;

	font_is_psf1 = psf_check_ver(font) == 1 ? true : false;
}

static void insert_newline(void)
{
	cursor_x = 0;
	if (cursor_y++ >= max_char_x)
		cursor_y--;
}

void vdcon_putc(char c)
{
	switch (c) {
		case '\n':
			insert_newline();
			return;
		case '\r':
			cursor_x = 0;
			return;
		case '\b':
			if (cursor_x == 0) return;
			cursor_x--;
			return;
		case '\t':
			cursor_x = TAB_WIDTH - (cursor_x % TAB_WIDTH);
			if (cursor_x >= max_char_x)
				insert_newline();
			return;
	}

	psf_draw_char(font, c, 
		cursor_x * font_width, 
		cursor_y * font_height, 
		fg, bg);

	if (cursor_x++ >= max_char_x)
		insert_newline();
}

void vdcon_puts(const char *str)
{
	while (*str)
		vdcon_putc(*str++);
}

void vdcon_switch_font(uint8_t *font_data)
{
	font = font_data;	
	font_is_psf1 = psf_check_ver(font) == 1 ? true : false;
	font_width = psf_get_width(font);
	font_height = psf_get_height(font);
}

void vdcon_set_fg(uint32_t col)
{
	fg = col;
}

void vdcon_set_bg(uint32_t col)
{
	bg = col;
}