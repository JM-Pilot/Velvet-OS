#include <drivers/uart/serial_con.h>
#include <arch/x86_64/port_io.h>
#include <stdint.h>

/* we only need to use COM1 because com2 and 
 * others are barely used and its just bloat 
 */
#define PORT 0x3F8

int serial_con_init(void)
{
	/* initialize COM1 */

	/* stop all irq from interrupting */
	outb(PORT + 1, 	0x00);

	/* Set DLAB and Divisor to 3 */
	outb(PORT + 3, 	0x80);
	outb(PORT, 	0x03);
	outb(PORT + 1,	0x00);

	/* 8 Bits, no parity, one stop bit */
	outb(PORT + 3,  0x03);

	/* Enable First In First Out, clear them with 14 byte threshold*/
	outb(PORT + 2,	0xC7);

	/* Enable IRQ RTS/DSR Set */
	outb(PORT + 4,	0x0B);

	/* Set In Loopback Mode */
	outb(PORT + 4,	0x1E);

	/* Test */
	outb(PORT,	0xAE);
	if (inb(PORT) != 0xAE)
		return 1;

	/* Set in normal operation mode if not faulty */
	outb(PORT + 4, 	0x0F);
	
	/* clear the screen */
	serial_con_puts("\033[2J\033[H");
	return 0;
}

char serial_getchar(void)
{
	/* we wait until if we get any input */
	while ((inb(PORT + 5) & 1) == 0);
	return inb(PORT);
}

void serial_con_putc(char c)
{
	/* wait until we can output */
	while ((inb(PORT + 5) & 0x20) == 0);
	outb(PORT, c);
}

void serial_con_puts(const char *str)
{
	while (*str)
		serial_con_putc(*str++);
}