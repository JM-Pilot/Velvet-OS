#ifndef DRIVERS_VIDEO_FRAMEBUFFER_H
#define DRIVERS_VIDEO_FRAMEBUFFER_H

#include <stdint.h>
#include <limine.h>
extern struct limine_framebuffer *framebuffer;

void framebuffer_init(void);
void framebuffer_plot_pixel(uint32_t color, uint64_t x, uint64_t y);
uint32_t framebuffer_get_color(uint64_t x, uint64_t y);
void framebuffer_fill(uint32_t color);

#endif /* DRIVERS_VIDEO_FRAMEBUFFER_H */