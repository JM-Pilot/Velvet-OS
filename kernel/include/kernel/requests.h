#ifndef REQUESTS_H
#define REQUESTS_H

#include <limine.h>

extern volatile struct limine_framebuffer_request framebuffer_request;

int check_revision(void);

#endif /* REQUESTS_H */