# SPDX-License-Identifier: GPL-2.0-only
# Copyright (C) 2026 Skhoron
CC      ?= gcc
LD      ?= ld
BUILD   := build

CFLAGS  := -std=gnu11 -Wall -Wextra -O2 -ffreestanding -fno-stack-protector -fno-tree-loop-distribute-patterns \
           -fno-pic -fno-pie -mno-red-zone -mno-sse -mno-mmx -mcmodel=kernel \
           -Iinclude -Ikernel
LDFLAGS := -nostdlib -static -z max-page-size=0x1000 -T kernel/linker.ld

SRC_C := $(shell find kernel -name '*.c')
SRC_S := $(shell find kernel -name '*.S')
OBJ   := $(patsubst %,$(BUILD)/%.o,$(SRC_C) $(SRC_S))

all: $(BUILD)/kernel.elf

$(BUILD)/kernel.elf: $(OBJ) kernel/linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.S.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all clean