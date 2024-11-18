BITS 16
ORG 0x7C00

start:

hang:
    jmp hang ; As of right now, it's just an infinite loop

TIMES 510 - ($ - $$) db 0
; Defines where the bootloader is located
DW 0xAA55
