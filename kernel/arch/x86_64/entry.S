/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (C) 2026 Skhoron */
/* Kernel entry. The bootloader jumps here in 64-bit mode with paging on,
 * the kernel mapped in the higher half and a pointer to struct boot_info
 * in %rdi (System V ABI). */

	.section .bss
	.align 16
boot_stack_bottom:
	.skip 16384
boot_stack_top:

	.section .text
	.global _start
	.type _start, @function
_start:
	cli
	lea boot_stack_top(%rip), %rsp
	xor %rbp, %rbp
	call kmain
1:	hlt
	jmp 1b
	.size _start, . - _start

	.section .note.GNU-stack,"",@progbits