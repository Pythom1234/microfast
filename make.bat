
mkdir build
del /Q /F build\*

setlocal enabledelayedexpansion
set SRC_FILES=
for %%f in (src\*.c) do (
    set SRC_FILES=!SRC_FILES! %%f
)

toolchain\bin\windows\clang ^
 --target=armv7m-none-eabi -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard ^
 -nostdlib -nostdinc -nodefaultlibs -Oz -Iinc -nostartfiles ^
 -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables -flto ^
 -ffunction-sections -fdata-sections -g0 -Wl,-T,linker.ld -Wl,--gc-sections ^
 -Itoolchain\stdlib\include\c++\14.2.0\arm-none-eabi\thumb\v7e-m+fp\hard ^
 -Itoolchain\stdlib\include\c++\14.2.0 ^
 -Itoolchain\stdlib\include ^
 -Itoolchain\stdlib\inc ^
 -Ltoolchain\stdlib\lib\nano ^
 -lgcc -lc -lg -lstdc++ -lnosys -lm -o build\main.elf ^
 !SRC_FILES!

if errorlevel 1 (
    exit /b 1
)

toolchain\bin\windows\llvm-objcopy -O ihex build\main.elf build\main.hex
toolchain\bin\windows\llvm-objcopy -O binary build\main.elf build\main.bin

toolchain\bin\windows\pyocd flash build\main.hex
