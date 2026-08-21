#include <utils/psf.h>
#include <stdint.h>

uint32_t psf_get_width(uint8_t *font_data)
{
	switch (psf_check_ver(font_data)) {
		case 1: {
			return 8; 
		}
		case 2: {
			struct psf2_header *header;
			psf2_init_header(&header, font_data);
			return header->width;
		}
		default: 
			return 0;
	}
}

uint32_t psf_get_height(uint8_t *font_data)
{
	switch (psf_check_ver(font_data)) {
		case 1: {
			struct psf1_header *header;
			psf1_init_header(&header, font_data);
			return header->glyph_size; 
		}
		case 2: {
			struct psf2_header *header;
			psf2_init_header(&header, font_data);
			return header->height;
		}
		default: 
			return 0;
	}
}

/* returns 1 if psf1, 2 for psf2, 0 if not a psf */
int psf_check_ver(uint8_t *font_data)
{
	if (font_data[0] == PSF1_MAGIC1 &&
		font_data[1] == PSF1_MAGIC2) {
			return 1;
	} else if (font_data[0] == PSF2_MAGIC1 &&
		font_data[1] == PSF2_MAGIC2 &&
		font_data[2] == PSF2_MAGIC3 &&
		font_data[3] == PSF2_MAGIC4) {
			return 2;
	} else 
		return 0;
}