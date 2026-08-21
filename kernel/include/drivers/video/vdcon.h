/* ViDeo Console */

#ifndef DRIVER_VIDEO_VDCON_H
#define DRIVER_VIDEO_VDCON_H

#include <stdint.h>

void vdcon_init(void);
void vdcon_putc(char c);
void vdcon_puts(const char *str);
void vdcon_switch_font(uint8_t *font_data);
#endif /* DRIVER_VIDEO_CON_H */