%include "words.inc"
%include "lib.inc"
%include "dict.inc"

section .bss
%define BUFFER 256
buf: resb BUFFER

extern find_word

global _start

section .rodata
key_not_found: db "No key!",0


overflow_buffer: db "Overflow buffer!",0

section .text

_start:
    xor rax, rax
    mov rdi, buf
    mov rsi, BUFFER
    call read_word
    test rax, rax
    jne .read_buffer
    mov rdi, overflow_buffer
    call .error
    jmp exit
.read_buffer:
    mov rdi, rax
    mov rsi, START_ELEMENT
    push rdx
    call find_word
    test rax, rax
    jne .key_found
    mov rdi, key_not_found
    call .error
    jmp exit
.key_found:
    pop rdx
    add rax,8
    add rax, rdx
    add rax, 1
    mov rdi, rax
    call print_string
    jmp exit
.error:
    xor rax, rax
    mov rsi, rdi
    call string_length
    mov rdx, rax
    mov rdi, 2
    mov rax, 1
    syscall
    ret