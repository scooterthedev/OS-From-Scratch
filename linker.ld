ENTRY(kernel_main)
OUTPUT_FORMAT(elf64-x86-64)
SECTIONS
{
    . = 1M;

    .text ALIGN(4K) : {
        _kernel_start = .;
        *(.text*)
    }

    .rodata ALIGN(4K) : {
        *(.rodata*)
    }

    .data ALIGN(4K) : {
        *(.data*)
    }

    .bss ALIGN(4K) : {
        *(.bss*)
        *(COMMON)
    }
    _kernel_end = .;
}
