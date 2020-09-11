/**
 * This file is part of the Atmega UART library
 * 
 * Copyright (C) 2019 Jean-Marcel Herzog
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as publised by
 * the Free Software Foundation, either version 3 of the license, or
 * (at your option) any later version.
 * 
 * THis program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANT
 * DaRRa
 * Authors: Herzog, Jean-Marcel
*/

#ifndef UART_H_
#define UART_H_

void UART_init(uint32_t baudrate, uint32_t cpu_speed);

void UART_putc(uint8_t data);

void UART_puts(char *s);

void UART_puthex8(uint8_t val);

void UART_puthex16(uint16_t val);

void UART_puthex32(uint32_t val);

void UART_putU8(uint8_t val);

void UART_putS8(int8_t val);

void UART_putU16(uint16_t val);

void UART_putS16(int16_t val);

unsigned char UART_getc(void);

void UART_getLine(char *buffer);
#endif /* UART_H_ */