section .text
global timer_interrupt_handler

timer_interrupt_handler:
    pusha
    call timer_handler
    popa
    iretq 