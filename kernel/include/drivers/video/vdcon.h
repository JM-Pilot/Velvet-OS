/* ViDeo Console */

#ifndef DRIVER_VIDEO_VDCON_H
#define DRIVER_VIDEO_VDCON_H

#include <stdint.h>

void vdcon_init(void);
void vdcon_putc(char c);
void vdcon_puts(const char *str);
void vdcon_switch_font(uint8_t *font_data);
void vdcon_set_fg(uint32_t col);
void vdcon_set_bg(uint32_t col);
#endif /* DRIVER_VIDEO_CON_H */