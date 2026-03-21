.global _start
_start:
    mov $0x6f9c802f, %rdi
    mov $0x402527, %rax
    call *%rax