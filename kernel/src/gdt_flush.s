.global gdt_flush
gdt_flush:
    lgdt [rdi]
    mov ax, 0x10 ; Data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ; Jumping far to flush the pipeline
    jmp 0x08:flush

flush:
    ret