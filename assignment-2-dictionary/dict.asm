
%define POINTER_SIZE 8
%include "lib.inc"
section .text
global find_word

extern string_length
extern string_equals

find_word:
    xor rax, rax
    mov r8, rdi
    mov r9, rsi
    .loop:
        add r9, POINTER_SIZE
        mov rsi, r9
        mov rdi, r8
        push r8
        push r9
        call string_equals
        pop r9
        pop r8
        cmp rax, 1
        je .found
        mov r9, [r9 - POINTER_SIZE]
        test r9, r9
        je .fail
        jmp .loop
    .found:
        sub r9, POINTER_SIZE
        mov rax, r9
        ret
    .fail:
        xor rax,rax
        ret
