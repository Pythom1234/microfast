MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 512K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

OUTPUT_FORMAT("elf32-littlearm")

ENTRY(__reset)

SECTIONS
{
    .text : ALIGN(4)
    {
        KEEP(*(.vectors))
        KEEP(*(.faults)) // Fault handlers must be in a separate section due to compiler optimizations.
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    __sidata = LOADADDR(.data);
    .data : ALIGN(4)
    {
        __sdata = .;
        *(.data*)
        __edata = .;
        . = ALIGN(4);
    } > RAM AT> FLASH

    .bss : ALIGN(4)
    {
        __sbss = .;
        *(.bss*)
        __ebss = .;
        . = ALIGN(4);
    } > RAM
    end = .;
    __exidx_start = .;
    __exidx_end = .;
    _fini = .;


    /DISCARD/ :
    {
        *(.comment*)
        *(.ARM.exidx)
        *(.ARM.extab)
        *(.ARM.attributes)
        *(.debug*)
        *(.fini*)
        *(.fini_array*)
        *(.ctors*)
        *(.ctors_array*)
        *(.dtors*)
        *(.dtors_array*)
    }

    ASSERT((SIZEOF(.data) + SIZEOF(.bss)) <= LENGTH(RAM), "RAM overflow")
    ASSERT(SIZEOF(.text) <= LENGTH(FLASH), "FLASH overflow")

    __stack = ORIGIN(RAM) + LENGTH(RAM);
}
