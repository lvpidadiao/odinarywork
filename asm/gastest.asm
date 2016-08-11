
    ;; two sample helloworld asm
    .global _start
    .section .data
message:    .ascii "hello, gas!\n"
    len = . - message
    .section .text
_start:
    movl $4, %eax
    movl $1, %ebx
    movl $message, %ecx
    movl $len, %edx
    int $0x80

    movl $1, %eax
; the 12 is the return code , can be found with $?
    movl $12, %ebx
    int $0x80
