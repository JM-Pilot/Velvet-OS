#include <utils/psf.h>
#include <drivers/video/framebuffer.h>
#include <stdint.h>
#include <stddef.h>
#include <drivers/uart/serial_con.h>

/* returns 0 if successful, 1 if failed */
/* font_data - is what `readelf -sW font.o` prints */
int psf1_init_header(struct psf1_header **header, uint8_t *font_data)
{
	/* Check if the magic correspond to the PSF1 Header */
	if (font_data[0] != PSF1_MAGIC1 || font_data[1] != PSF1_MAGIC2) return 1;

	*header = (struct psf1_header*)font_data;

	return 0;
}

/* this outputs to the framebuffer */
/* font_data - is what `readelf -sW font.o` prints */
void psf1_draw_char(uint8_t *font_data, uint16_t uc, 
	uint64_t x, uint64_t y, uint32_t fg, uint32_t bg)
{
	struct psf1_header *header;
	/* check if the font is correct */
	if (psf1_init_header(&header, font_data) == 1) {
		serial_con_puts("ERROR: FONT IS NOT PSF V1\n");
		return;
	}

	/* get the glyph containing the character.
	 * we would also check if we use 512 char mode or 256
	 * if the char is above 255 we display a happy face (lol) to not
	 * make an error
	 */
	uint8_t *glyph = (uint8_t*)font_data + sizeof(struct psf1_header) + 
		((uc < (header->mode & PSF1_MODE512 ? 512 : 256) ? uc : 1) * header->glyph_size);

	/* print the glyph */
	for (uint8_t gy = 0; gy < header->glyph_size; gy++) {
		/* byte containing off and on bits */
		uint8_t byte = glyph[gy];
		for (uint8_t gx = 0; gx < 8; gx++) {
			/* check the if the bit is on or not */
			if (byte & (0x80 >> gx)) {
				framebuffer_plot_pixel(fg, x + gx, y + gy);
			} else {
				framebuffer_plot_pixel(bg, x + gx, y + gy);
			}
		}
	}
}