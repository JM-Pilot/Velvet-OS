/* PC Screen Font Utility */

#ifndef UTILS_PSF_H
#define UTILS_PSF_H

#include <stdint.h>

/* KERNEL BUILT IN FONTS */
extern uint8_t _binary_assets_ter_u16n_psf_start[];
#define PSF_TER_U16N _binary_assets_ter_u16n_psf_start
extern uint8_t _binary_assets_ter_u22n_psf_start[];
#define PSF_TER_U22N _binary_assets_ter_u22n_psf_start

#define PSF1_MAGIC1 0x36
#define PSF1_MAGIC2 0x04

/* 512 characters */
#define PSF1_MODE512 0x1

/* if these 2 are set, the font face will have a unicode table */
#define PSF1_MODEHASTAB 0x2
#define PSF1_MODESEQ 0x4

struct psf1_header {
	uint8_t magic[2];
	uint8_t mode;
	uint8_t glyph_size;
}__attribute__((packed));

int psf1_init_header(struct psf1_header **header, uint8_t *font_data);
void psf1_draw_char(uint8_t *font_data, uint16_t uc, 
	uint64_t x, uint64_t y, uint32_t fg, uint32_t bg);

#define PSF2_MAGIC1 0x72
#define PSF2_MAGIC2 0xB5
#define PSF2_MAGIC3 0x4A
#define PSF2_MAGIC4 0x86

/* same as PSF1_MODEHASTAB & PSF1_MODESEQ */
#define PSF2_HAS_UNICODE_TABLE 0x1

struct psf2_header {
	uint8_t magic[4];
	uint32_t version;
	uint32_t header_size;
	uint32_t flags;
	uint32_t num_of_glyphs;
	uint32_t bytes_per_glyph;
	uint32_t height;
	uint32_t width;
}__attribute__((packed));

int psf2_init_header(struct psf2_header **header, uint8_t *font_data);

/* THEY ARE UNICODE!!! */

void psf2_draw_char(uint8_t *font_data, uint16_t uc,
	uint64_t x, uint64_t y, uint64_t fg, uint64_t bg);



/* Helper functions */

uint32_t psf_get_width(uint8_t *font_data);
uint32_t psf_get_height(uint8_t *font_data);

int psf_check_ver(uint8_t *font_data);

void psf_draw_char(uint8_t *font_data, uint16_t uc, 
	uint64_t x, uint64_t y, 
	uint32_t fg, uint32_t bg);

#endif /* UTILS_PSF_H */
