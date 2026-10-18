/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (C) 2026 Skhoron */
#ifndef SKHORON_BOOT_INFO_H
#define SKHORON_BOOT_INFO_H

#include <stdint.h>

/* Contract between the bootloader and the kernel. See docs/boot-protocol.md.
 * Any change here must bump BOOT_INFO_VERSION and update the document. */

#define BOOT_INFO_MAGIC   0x534B484F524F4E31ULL  /* "SKHORON1" */
#define BOOT_INFO_VERSION 1

enum mem_type {
	MEM_USABLE = 1,
	MEM_RESERVED,
	MEM_ACPI_RECLAIMABLE,
	MEM_ACPI_NVS,
	MEM_BOOTLOADER,   /* loader data, reclaimable after boot */
	MEM_KERNEL,
};

struct mem_region {
	uint64_t base;
	uint64_t length;
	uint32_t type;    /* enum mem_type */
	uint32_t _pad;
};

struct framebuffer {
	uint64_t base;    /* physical address, 0 if absent */
	uint32_t width;
	uint32_t height;
	uint32_t pitch;   /* bytes per line */
	uint32_t bpp;
};

struct boot_info {
	uint64_t magic;
	uint32_t version;
	uint32_t _pad;
	uint64_t mem_map;          /* physical address of struct mem_region[] */
	uint64_t mem_map_count;
	uint64_t acpi_rsdp;        /* physical address, 0 if absent */
	uint64_t kernel_phys_base;
	uint64_t kernel_virt_base;
	struct framebuffer fb;
};

#endif