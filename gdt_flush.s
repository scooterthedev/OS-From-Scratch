; gdt_flush.s
section .text
    global gdt_flush

gdt_flush:
    lgdt [rdi]             ; Load the GDT from the address in RDI
    mov ax, 0x10           ; Load the Data Segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ; Far jump to reload CS and flush the instruction pipeline
    jmp 0x08:.flush

.flush:
    ret