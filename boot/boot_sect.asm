BITS 16
ORG 0x7C00

start:
    cli
    cld

    ; Enable A20 line first
    call enable_a20

    xor ax, ax
    mov ss, ax
    mov sp, 0x7C00

    lgdt [gdt_descriptor]

    ; Enable protected mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp 08h:protected_mode

enable_a20:
    ; Fast A20 gate method
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[BITS 32]
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Check for CPUID support
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    xor eax, ecx
    jz no_long_mode

    ; Check for long mode support
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb no_long_mode

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz no_long_mode

    ; Enable PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Set up page tables
    ; This should be replaced with your actual page table setup
    mov eax, 0x1000
    mov cr3, eax

    ; Enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ; Load 64-bit GDT
    lgdt [gdt64_descriptor]
    
    ; Jump to 64-bit code
    jmp 0x08:long_mode_start

no_long_mode:
    hlt
    jmp $

gdt_start:
    dq 0x0000000000000000 ; Null
    dq 0x00CF9A000000FFFF ; 32-bit Code
    dq 0x00CF92000000FFFF

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt_end:

; 64-bit GDT
gdt64_start:
    dq 0x0000000000000000 ; Null
    dq 0x00AF9A000000FFFF ; 64-bit Code
    dq 0x00AF92000000FFFF ; 64-bit Data

gdt64_descriptor:
    dw gdt64_end - gdt64_start - 1
    dd gdt64_start

gdt64_end:

[BITS 64]
long_mode_start:
    ; Now in 64-bit mode
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Jump to kernel
    mov rax, 0x100000  ; Kernel loaded at 1MB
    jmp rax

times 510 - ($ - $$) db 0
DW 0xAA55
