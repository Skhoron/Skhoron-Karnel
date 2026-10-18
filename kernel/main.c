/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (C) 2026 Skhoron */
#include <stdint.h>
#include <skhoron/boot_info.h>
#include "arch/x86_64/serial.h"

void kmain(const struct boot_info *bi)
{
	serial_init();
	serial_puts("Skhoron-Karnel: hello\n");

	if (!bi || bi->magic != BOOT_INFO_MAGIC) {
		serial_puts("boot_info: bad magic, halting\n");
		goto halt;
	}
	if (bi->version != BOOT_INFO_VERSION) {
		serial_puts("boot_info: version mismatch, halting\n");
		goto halt;
	}

	serial_puts("boot_info: ok, memory map entries: ");
	serial_put_hex(bi->mem_map_count);
	serial_puts("\n");

halt:
	for (;;)
		__asm__ volatile("cli; hlt");
}