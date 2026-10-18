/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (C) 2026 Skhoron */
/* COM1 16550 UART, 115200 8N1. Written from the 16550 register description. */
#include "io.h"
#include "serial.h"

#define COM1 0x3F8

void serial_init(void)
{
	outb(COM1 + 1, 0x00);  /* interrupts off */
	outb(COM1 + 3, 0x80);  /* DLAB on */
	outb(COM1 + 0, 0x01);  /* divisor 1 = 115200 baud */
	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x03);  /* 8 bits, no parity, one stop bit */
	outb(COM1 + 2, 0xC7);  /* FIFO on, cleared, 14-byte threshold */
	outb(COM1 + 4, 0x0B);  /* DTR, RTS, OUT2 */
}

void serial_putc(char c)
{
	while (!(inb(COM1 + 5) & 0x20))
		;
	outb(COM1, (uint8_t)c);
}

void serial_puts(const char *s)
{
	for (; *s; s++) {
		if (*s == '\n')
			serial_putc('\r');
		serial_putc(*s);
	}
}

void serial_put_hex(uint64_t v)
{
	static const char d[] = "0123456789abcdef";

	serial_puts("0x");
	for (int i = 60; i >= 0; i -= 4)
		serial_putc(d[(v >> i) & 0xF]);
}