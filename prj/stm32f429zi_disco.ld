/**
 * Brief: Linker configuration for: STM32F429ZI-DISCOVERY
 * (c) alexey.gulchenko@gmail.com
 **/

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 2M
    RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
}

_stack_size     = 1024;
_data_start     = ORIGIN(RAM);
_stack_start    = ORIGIN(RAM) + LENGTH(RAM) - _stack_size;
_heap_end       = _stack_start;

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vectors))
        . = ALIGN(4);
    } >FLASH

    .initcall :
    {
        . = ALIGN(4);
        _initcall_start = .;
        KEEP(*(.init0))
        KEEP(*(.init1))
        KEEP(*(.init2))
        _initcall_end = .;
        . = ALIGN(4);
    } >FLASH

    .text :
    {
        . = ALIGN(4);
        _text_start = .;
        *(.text*)
        *(.rodata*)
        _text_end = .;
        . = ALIGN(4);
    } > FLASH

    __end_of_text = .;

    /* Initialized data sections */
    .data : AT(__end_of_text)
    {
        _data_start = .;
        . = ALIGN(4);
        *(.data*)
        _data_end = .;
        . = ALIGN(4);
    } > RAM

    /* Uninitialized data section */
    .bss :
    {
        _bss_start = .;
        . = ALIGN(4);
        *(.bss*)
        *(COMMON)
        _bss_end = .;
        . = ALIGN(4);
    } > RAM

    _heap_start = .;
    _heap_size = _stack_start - _heap_start;
    . = ALIGN(4);
    .heap : AT(_heap_start)
    {
        _heap_base = .;
        . = . + _heap_size;
        _heap_end = .;
    } > RAM

    . = ALIGN(4);
    .stack : AT(_stack_start)
    {
        . = . + _stack_size;
        _stack_top = _stack_start + _stack_size;
    } > RAM
}
