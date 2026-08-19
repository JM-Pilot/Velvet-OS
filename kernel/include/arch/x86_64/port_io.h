#ifndef ARCH_X86_64_PORT_IO_H
#define ARCH_X86_64_PORT_IO_H

#include <stdint.h>

/* BYTE (UINT8_T) */
static inline void outb(uint16_t port, uint8_t val)
{
	/* we just use the __asm__ */
	__asm__ volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t val; 	/* value from the port, this will be returned */
	__asm__ volatile ("inb %w1, %b0" : "=a"(val) : "Nd"(port));
	return val;
}


/* Word (UINT16_T) */
static inline void outw(uint16_t port, uint16_t val)
{
	__asm__ volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port));
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t val;
	__asm__ volatile ("inw %w1, %w0" : "=a"(val) : "Nd"(port));
	return val;
}

/* Long (UINT32_T) */ 
static inline void outl(uint16_t port, uint32_t val)
{
	__asm__ volatile ("outl %l0, %w1" : : "a"(val), "Nd"(port));
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t val;
	__asm__ volatile ("inl %w1, %l0" : "=a"(val) : "Nd"(port));
	return val;
}
#endif /* ARCH_X86_64_PORT_IO_H */