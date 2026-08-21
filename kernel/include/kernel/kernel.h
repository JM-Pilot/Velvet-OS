#ifndef KERNEL_H
#define KERNEL_H

#define LOG_DEBUG 1
#define LOG_ERROR 2

void klog(int lvl, const char *msg);

#endif /* KERNEL_H */