.global _start
_start:
    lea 0x8(%rsp), %rdi
    mov $0x40263c, %rax
    call *%rax