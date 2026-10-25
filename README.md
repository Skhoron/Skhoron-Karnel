Skhoron-Karnel

An operating system kernel written from scratch. License: GPL-2.0-only.

Copyright (C) 2026 Skhoron.

Goal: a working OS built on this kernel: booting, memory, processes, system calls, disk, filesystem, shell. There are no graphics or visual styling.

Principles:

- the kernel is subordinate to its owner; there are no hidden restrictions;
- ideas are taken from Linux and open specifications; code is not copied;
- languages: assembly, C, Rust modules; the common boundary between languages is the C ABI.

Current status:

- available: repository structure, kernel entry point ("entry.S"), output to COM1, linker script, building "kernel.elf";
- not available: UEFI bootloader (the contract is described in "docs/boot-protocol.md"), paging, interrupts, everything else.

Build: "make" (gcc and ld for x86_64 are required). Output: "build/kernel.elf".

Documents: "docs/principles.md", "docs/boot-protocol.md", "docs/ideas.md", "docs/sources.md".