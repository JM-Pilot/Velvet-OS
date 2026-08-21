#include <utils/psf.h>
#include <stdint.h>

uint32_t psf_get_width(uint8_t *font_data)
{
	if (font_data[0] == PSF1_MAGIC1 &&
		font_data[1] == PSF1_MAGIC2) {
		return 8; /* all psf v1 fonts are 8 width */
	} else if (font_data[0] == PSF2_MAGIC1 &&
		font_data[1] == PSF2_MAGIC2 &&
		font_data[2] == PSF2_MAGIC3 &&
		font_data[3] == PSF2_MAGIC4) {
		
		struct psf2_header *header;
		psf2_init_header(&header, font_data);
		return header->width;
	} else 
		return 0;
}
uint32_t psf_get_height(uint8_t *font_data)
{
	if (font_data[0] == PSF1_MAGIC1 &&
		font_data[1] == PSF1_MAGIC2) {
			struct psf1_header *header;
			psf1_init_header(&header, font_data);
			return header->glyph_size; 
	} else if (font_data[0] == PSF2_MAGIC1 &&
		font_data[1] == PSF2_MAGIC2 &&
		font_data[2] == PSF2_MAGIC3 &&
		font_data[3] == PSF2_MAGIC4) {
			struct psf2_header *header;
			psf2_init_header(&header, font_data);
			return header->height;
	} else 
		return 0;
}