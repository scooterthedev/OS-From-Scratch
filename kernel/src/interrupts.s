section .text
global keyboard_interrupt_handler

keyboard_interrupt_handler:
    pusha
    push r10
    push r11
    ; Call the C handler
    call keyboard_interrupt_handler
    pop r11
    pop r10
    popa
    iretq 