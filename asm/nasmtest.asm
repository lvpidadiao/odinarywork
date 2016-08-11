    ;; this is the nasm intel syntax hello world
    global _start
    section .data
message:    db "hello, nasm!",10
len:    equ $-message

    section .asdf
anoth:  db "ni"
    section .text
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, anoth
    mov edx, 2
    int 80h

    mov eax, 1
    mov ebx, 0
    int 80h
