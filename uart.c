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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "uart.h"
#include <stdbool.h>

/**
*
* @brief UART initialization
*
* @param baudrate UART baudrate
* @param cpu_speed cpu frequency
*
* @return void
*
*/
void UART_init(uint32_t baudrate, uint32_t cpu_speed)
{
	// calculate baudrate for UART baud rate register
	uint32_t ubrr_val = (cpu_speed + baudrate) / ((baudrate * 16) - 1);

	// write baudrate into register
	// devided in high-byte and low-byte
	UBRRH = (uint8_t)(ubrr_val >> 8);
	UBRR0L = (uint8_t)(ubrr_val);

	// activate receive and transmit
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// frame format: synchron 8N1
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

/**
*
* @brief Send ASCII character
*
* transmit a 8-bit character.
*
* @param data 8-Bit character
*
* @return void
*
*/
void UART_putc(uint8_t data)
{
	// wait until transmit buffer is free
	while (!(UCSRA & (1 << UDRE)))
		;

	// load data to register
	UDR = data;
}

/**
*
* @brief Send string
*
* @param s string to transmit
*
* @return void
*
*/
void UART_puts(char *s)
{

	// send character until NULL is reached
	while (*s > 0)
		UART_putc(*s++);
}

/**
*
* @brief Send 8-bit hexadecimal value
*
* Convert a 8-bit value to hexadecimal as ASCII.
*
* @param val 8-Bit value to transmit
*
* @return void
*
*/
void UART_puthex8(uint8_t val)
{
	// extract upper and lower nibble from input value
	uint8_t upperNibble = (val & 0xF0) >> 4;
	uint8_t lowerNibble = (val & 0x0F);

	// convert nibble to ASCII hex value
	upperNibble += upperNibble > 9 ? 'A' - 10 : '0';
	lowerNibble += lowerNibble > 9 ? 'A' - 10 : '0';

	// send two ASCII values
	UART_putc(upperNibble);
	UART_putc(lowerNibble);
}

/**
*
* @brief Send 16-bit hex value
*
* Convert a 16-bit value to hex-value as ASCII.
*
* @param val 16-bit value to transmit
*
* @return void
*
*/
void UART_puthex16(uint16_t val)
{
	// transmit high byte
	UART_puthex8((uint8_t)(val >> 8));

	// transmit low byte
	UART_puthex8((uint8_t)(val & 0x00FF));
}

/**
*
* @brief Send 32-bit hex value
*
* Convert a 32-bit value to hex-value as ASCII.
*
* @param val 32-Bit value to transmit
*
* @return void
*
*/
void UART_puthex32(uint32_t val)
{
	// transmit upper 16 bit
	UART_puthex16((uint16_t)(val >> 16));

	// transmit lower 16 bit
	UART_puthex16((uint16_t)(val & 0x0000FFFF));
}

/**
*
* @brief Send 8 bit unsigned value
*
* @param val 8-Bit value to transmit
*
* @return void
*
*/
void UART_putU8(uint8_t val)
{
	uint8_t digit1 = '0', digit2 = '0';

	while (val >= 100)
	{
		val -= 100;
		digit1++;
	}

	while (val >= 10)
	{
		val -= 10;
		digit2++;
	}

	// send first character (or ignore leading 0)
	if (digit1 != 0)
		UART_putc(digit1);

	// send second character (or ignore leading 0)
	if ((digit1 != '0') || (digit2 != '0'))
		UART_putc(digit2);

	// send last character
	UART_putc(val + '0');
}

/**
*
* @brief Send signed 8-bit value
*
* @param val 8-Bit value to transmit
*
* @return void
*/
void UART_putS8(int8_t val)
{
	// negative number? bit 7 -> 1
	if (val & 0x80)
	{
		// send sign
		UART_putc('-');

		// convert to positive number
		val = -(val - 1);
	}

	// send number
	UART_putc(val);
}

/**
*
* @brief Send 16-bit unsigned value
*
* @param val 16-Bit value to transmit
*
* @return void
*
*/
void UART_putU16(uint16_t val)
{
	uint8_t digit1 = '0', digit2 = '0', digit3 = '0', digit4 = '0';

	// extract 10000
	while (val >= 10000)
	{
		val -= 10000;
		digit1++;
	}

	// extract 1000
	while (val >= 1000)
	{
		val -= 1000;
		digit2++;
	}

	// extract 100
	while (val >= 100)
	{
		val -= 100;
		digit3++;
	}

	// extract 10
	while (val >= 10)
	{
		val -= 10;
		digit4++;
	}

	bool prevprint = 0; // previous place > 0 flag

	// send 10000 (or ignore leading 0)
	if (digit1 != '0')
	{
		UART_putc(digit1);
		prevprint = 1;
	}

	// send 1000 (or ignore leading 0)
	if (prevprint || digit2 != '0')
	{
		UART_putc(digit2);
		prevprint = 1;
	}

	// send 100 (or ignore leading 0)
	if (prevprint || digit3 != '0')
	{
		UART_putc(digit3);
		prevprint = 1;
	}

	// send 10 (or ignore leading 0)
	if (prevprint || digit4 != '0')
		UART_putc(digit4);

	// send 1 (or ignore leading 0)
	UART_putc(val + '0');
}

/**
*
* @brief Send 16-bit signed value
*
* @param val 16-Bit signed value to transmit
*
* @return void
*
*/
void UART_putS16(int16_t val)
{
	// negative number? bit 7 -> 1
	if (val & 0x8000)
	{
		// send sign
		UART_putc('-');

		// convert to positive number
		val = ~(val - 1);
	}

	// send number
	UART_putU16((uint16_t)val);
}

/**
*
* @brief Read UART character
*
* @return ASCII value
*
*/
unsigned char UART_getc(void)
{
	// Wait for values
	while (!(UCSRA & (1 << RXC)))
		;

	return UDR;
}

/**
*
* @brief Read UART string
*
* @param buffer	String for transmit value
*
* @param n length of the string
*
* @return void
*
*/
void UART_getLine(char *buffer)
{
	uint8_t bufferIndex = 0;
	int bufferLength = strlen(buffer);

	char c;

	// loop until termination character of string is reached
	// buffer index have to be smaller than n (for terminating 0)
	do
	{
		// receive character
		c = UART_getc();

		// place character in buffer
		buffer[bufferIndex++] = c;
	} while (bufferIndex < bufferLength && c != '\r');

	// make sure, that string end with '\0'
	buffer[bufferIndex] = 0;
}