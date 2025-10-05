SRCS := $(wildcard src/*.cpp) $(wildcard src/*.s)
CPU_FLAGS := --target=armv7m-none-eabi -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
STDLIB := -Istdlib/include/c++/14.2.0/arm-none-eabi/thumb/v7e-m+fp/hard \
-Istdlib/include/c++/14.2.0 \
-Istdlib/include \
-Istdlib/inc \
-Lstdlib/lib/nano \
-lgcc -lc -lg -lstdc++ -lnosys -lm
CFLAGS := $(CPU_FLAGS) -nostdlib -nostdinc -nodefaultlibs -Oz -Iinc -nostartfiles \
-fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-lto \
-ffunction-sections -fdata-sections -g0
LDFLAGS := -Wl,-T,linker.ld -Wl,--gc-sections $(STDLIB)

all: clean compile flash

compile: $(SRCS)
	mkdir -p build
	clang $(CFLAGS) $^ $(LDFLAGS) -o build/main.elf
	llvm-objcopy -O ihex build/main.elf build/main.hex
	llvm-objcopy -O binary build/main.elf build/main.bin

clean:
	rm -rf build/*

flash: all
	killall -q -9 openocd || true
	openocd -f interface/cmsis-dap.cfg \
			-f target/nrf52.cfg \
			-c "program build/main.hex reset"

disasm:
	arm-none-eabi-objdump -m arm -D -M force-thumb build/main.elf
