/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (C) 2026 Skhoron */
ENTRY(_start)

/* Higher half: top 2 GiB of the address space (matches -mcmodel=kernel). */
KERNEL_VMA = 0xFFFFFFFF80000000;

SECTIONS
{
	. = KERNEL_VMA + 1M;
	__kernel_start = .;

	.text : ALIGN(4K) { *(.text .text.*) }
	.rodata : ALIGN(4K) { *(.rodata .rodata.*) }
	.data : ALIGN(4K) { *(.data .data.*) }
	.bss : ALIGN(4K) {
		*(.bss .bss.*)
		*(COMMON)
	}

	__kernel_end = .;

	/DISCARD/ : { *(.comment) *(.note*) *(.eh_frame*) }
}