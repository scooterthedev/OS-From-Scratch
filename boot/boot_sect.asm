BITS 16
ORG 0x7C00

start:
    cli
    cld

    xor ax, ax
    mov ss, ax
    mov sp, 0x7C00

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp 08h:protected_mode

[BITS 32]
protected_mode:
    ; Setting up registers
    mov ax, 0x10 ; This is the offset in the GDT for our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call enable_a20 ; Enabling the A20 line ie. the 21st bit of the address

    jmp 0x10:long_mode ; Switching to long mode by setting up a page table by loading CR3 and CR4

enable_a20:
    ret

gdt_start:
    dq 0x0000000000000000 ; Null
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt_end:

times 510 - ($ - $$) db 0
; Defines where the bootloader is located
DW 0xAA55

[BITS 64]
long_mode:
    ; Placeholder for long mode code
    ; For now, we'll halt the system
    hlt
    jmp $
