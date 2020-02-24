#ifndef UART_H
#define UART_H

#include <stdio.h>
#include "stm32l475xx.h"


void uart_init(int baudrate);
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const uint8_t *str);
void uart_gets(uint8_t *str, size_t size);
uint32_t checksum(int datasize);

#endif //UART_H