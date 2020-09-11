# Atmega-UART-library

This is a easy header-only C library for UART (Universal Receiver Transmitter) communication of Atmega Microcontrollers.
The library fully tested on a Atmega328P build onboard the common known Arduino Uno R3 board.

## Features

Everything you need to communicate is implemented. Sending and receiving single bytes or full strings. Also there are some
helpful debugging features implemented. Therefore this library has implementions for type conversions to transmit a formatted Hex value
as ASCII character string.

For example:

```cpp
uint8_t i = 15;
uint8_t b = #A;
UART_puthex8(i); // this will send the string: #FF
UART_puthU8(b); // this will send the string: "10"
```

# How to use

The follow section will give you a little overview how to use this code.

## Include

This part is easy. Only include the header file as shown and start coding.

```c
#include "uart.h"
```

## UART Init

This code is needed to initialize the UART of the microcontroller. Without this line of code, the UART wont work as expected.

```c
void uart_init(unsigned long baudrate, unsigned long cpu_speed)
```

**cpu_speed:** has to be set in Hz.

## Send ASCII character

```c
void UART_putc(uint8_t asciiCharacter)
```

## Send String

```c
void UART_puts(char *s)
```

## Send a 8-bit hexadecimal value

```c
void UART_puthex8(uint8_t val)
```

## Send a 16-bit hexadecimal value

```c
void UART_puthex16(uint16_t val)
```

## Send a 32-bit hexadecimal value

```c
void UART_puthex32(uint32_t val)
```

## Send a 8-bit unsigned number

```c
void UART_putU8(uint_8t val)
```

## Send a 8-bit signed number

```c
void UART_putS8(int8_t val)
```

## Send a 16-bit unsigned number

```c
void UART_putU16(uint_16t val)
```

## Send a 16-bit signed number

```c
void UART_putS16(int16_t val)
```

## Read a single ASCII character

```c
unsigned char UART_getc(void)`
```

## Read a ASCII string

```c
void UART_getLine(char *buffer)
```

## Further links

[mikrocontroller.net - UART](https://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/Der_UART)
