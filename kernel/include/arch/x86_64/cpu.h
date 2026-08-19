#ifndef ARCH_X86_64_CPU_H
#define ARCH_X86_64_CPU_H

static inline void cpu_hang(void)
{
	__asm__ volatile ("cli");
	for (;;) __asm__ volatile ("hlt");
}

#endif /* ARCH_X86_64_CPU_H */