#include <utils/psf.h>
#include <drivers/video/framebuffer.h>
#include <drivers/uart/serial_con.h>
#include <stdint.h>
#include <stddef.h>

/* returns 0 if successful, 1 if failed */
int psf2_init_header(struct psf2_header **header, uint8_t *font_data)
{
	if (font_data[0] != PSF2_MAGIC1 ||
		font_data[1] != PSF2_MAGIC2 ||
		font_data[2] != PSF2_MAGIC3 ||
		font_data[3] != PSF2_MAGIC4) return 1;
	
	*header = (struct psf2_header *)font_data;
	return 0;
}

void psf2_draw_char(uint8_t *font_data, uint16_t uc,
	uint64_t x, uint64_t y, uint64_t fg, uint64_t bg)
{
	struct psf2_header *header;
	if (psf2_init_header(&header, font_data) == 1) {
		serial_con_puts("ERROR: FONT IS NOT PSF V2\n");
		return;
	}

	/* get the glyph */
	uint8_t *glyph = (uint8_t*)font_data + header->header_size +
		(uc > 0 && uc < header->num_of_glyphs ? uc : 0) * header->bytes_per_glyph;

	uint32_t bpl = (header->width + 7) / 8;

	for (uint32_t gy = 0; gy < header->height; gy++) {
		uint8_t *current_byte = glyph + (bpl * gy); 
		uint8_t mask = 1 << 7;
		for (uint32_t gx = 0; gx < header->width; gx++) {
			uint32_t color = *current_byte & mask ? fg : bg;
			framebuffer_plot_pixel(color, x + gx, y + gy);

			/* move to next bit */
			mask >>= 1;

			/* move to the next byte if we reached the end bit */
			if (mask == 0) {
				mask = 1 << 7;
				current_byte++;
			}
		}
	}
}