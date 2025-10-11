SRCS := $(wildcard src/*.cpp) $(wildcard src/*.s)
CPU_FLAGS := --target=armv7m-none-eabi -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
STDLIB := \
-Itoolchain/stdlib/include/c++/14.2.0/arm-none-eabi/thumb/v7e-m+fp/hard \
-Itoolchain/stdlib/include/c++/14.2.0 \
-Itoolchain/stdlib/include \
-Itoolchain/stdlib/inc \
-Ltoolchain/stdlib/lib/nano \
-lgcc -lc -lg -lstdc++ -lnosys -lm
CFLAGS := $(CPU_FLAGS) -nostdlib -nostdinc -nodefaultlibs -Oz -Iinc -nostartfiles \
-fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-lto \
-ffunction-sections -fdata-sections -g0
LDFLAGS := -Wl,-T,linker.ld -Wl,--gc-sections $(STDLIB)

SHELL := /bin/bash
# PATH := toolchain/bin:$(PATH)
PATH := toolchain/bin/linux
LD_LIBRARY_PATH := toolchain/bin/linux

.ONESHELL:

all: clean compile flash

compile: $(SRCS)
	@set -e
	mkdir -p build
	clang $(CFLAGS) $^ $(LDFLAGS) -o build/main.elf
	llvm-objcopy -O ihex build/main.elf build/main.hex
	llvm-objcopy -O binary build/main.elf build/main.bin

clean:
	@set -e
	rm -rf build/*

flash:
	@set -e
	pyocd flash build/main.hex

# flash:
# 	@set -e
# 	for id in $$(pyocd json | jq -r '.boards[].unique_id'); do \
# 	    pyocd flash build/main.hex --target nrf52 --uid $$id & \
# 	wait; \
# 	done; \

disasm:
	arm-none-eabi-objdump -m arm -D -M force-thumb build/main.elf
