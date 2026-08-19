#ifndef DRIVERS_UART_SERIAL_CON_H
#define DRIVERS_UART_SERIAL_CON_H

char serial_getchar(void);
int serial_con_init(void);
void serial_con_putc(char c);
void serial_con_puts(const char *str);

#endif /* DRIVERS_UART_SERIAL_CON_H */