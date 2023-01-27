%define SYS_READ 0
%define FD_STDIN 0
%define SYS_WRITE 1
%define FD_STDOUT 0
%define EXIT 60
%define NULL_TERMINATOR 0
%define NEW_STRING 0xA
%define TAB 0x9
%define SPACE 0x20
section .text
 
; Принимает код возврата и завершает текущий процесс
exit: 
    mov rax, EXIT
    syscall

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax
        .loop:
            cmp byte[rdi+rax], NULL_TERMINATOR ;Проверить текущий элеме равно 0
            je .end
            inc rax
            jmp .loop
        .end:
            ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    xor rax, rax
    mov rsi, rdi
    call string_length  ;Узнать длину стоки
    mov rdx, rax        ;Указать длину на строки
    mov rdi, FD_STDOUT          ;Указать на stdout
    mov rax, SYS_WRITE          ;syscall 'write'
    syscall
    ret

; Принимает код символа и выводит его в stdout
print_char:
    xor rax, rax
    push rdi
    mov rsi, rsp        ;Указать на адрес символа вывода
    pop rdi
    mov rax,SYS_WRITE           ;syscall 'write'
    mov rdx,1           ;Указать длину строки вывода
    mov rdi,FD_STDOUT           ;Указать на stdout
    syscall
    ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rdi, 0xA        ;Указать на символ перевода строки
    push rcx
    call print_char     ;Вывести символ 0xA
    pop rcx
    ret

; Выводит беззнаковое 8-байтовое число в десятичном формате
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
    xor rax, rax
    mov r8, 10          ;Делимое
    mov r9, rsp
    mov rax, rdi
    push 0
    .loop:
        xor rdx, rdx
        div r8          ;Получить последнее число
        add rdx, 48     ;Перевод в ASCII
        dec rsp
        mov byte[rsp], dl   ;Записать остаток деления
        test rax,rax       ;Проверить последнее ли число
        je .end
        jmp .loop
    .end:
        mov rdi, rsp    ;Записать результат в rdi
        push r9
        call print_string ;Ввести результат
        pop r9
        mov rsp, r9
        ret

; Выводит знаковое 8-байтовое число в десятичном формате
print_int:
    xor rax, rax
    mov rax,rdi
    cmp rax,0           ;Если число > 0, сразу ввести
    jl .print
    jmp print_uint
    .print:
        push rdi
        mov rdi, '-'
        call print_char
        pop rdi
        neg rdi
        jmp print_uint
    ret

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    mov rax, 1
    mov r8, rdi             ;Указатель на первую строку
    mov r9, rsi             ;Указатель на вторую строку
    xor rdi, rdi
    xor rsi, rsi
    xor rcx, rcx
    .loop:
        mov dil, [r8+rcx]
        mov sil, [r9+rcx]
        cmp sil, dil
        jne .not_equal
        cmp byte dil, 0     ;Если оба символа равно 0, то оставить
        je .end
        inc rcx
        jmp .loop
    .not_equal:
        mov rax,0
    .end:
        ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    mov rdi, FD_STDIN          ; Указать на stdin
    mov rdx, 1          ; Указать на длину строки ввода
    mov rax, SYS_READ          ; 'read' syscall
    xor rax, rax
    dec rsp
    mov rsi, rsp
    syscall
    cmp rax, 0
    jz .zero
    mov rax, [rsp]
    inc rsp
    ret 
    .zero:
        xor rax,rax
        mov rax, 0
        inc rsp
        ret


; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор

read_word:
    mov r8, rdi
    mov r9, rsi

    .skip_whitespace:           ;Удаление пробелов
        call read_char
        cmp al, 0x20
        je .skip_whitespace
        cmp al, 0x9
        je .skip_whitespace
        cmp al, 0xA
    xor rdx,rdx
    jmp .write
    .loop:                      ;Ввести символ
        push rdx
        call read_char
        pop rdx
    .write:                     ;Проверить конец строки, если нет вызывать цикл ввода символа
        cmp al, NEW_STRING
        je .end
        cmp al, SPACE
        je .end
        cmp al, 4
        je .end
        cmp al, TAB
        je .end
        cmp al, 0
        je .end
        inc rdx
        cmp rdx, r9
        jge .overflow
        dec rdx
        mov [r8+rdx], al
        inc rdx
        jmp .loop
    .end:                   ;Сохранить результат
        mov byte[r8+rdx],0
        mov rax, r8
        ret
    .overflow:              ;Если своло слишком большой для буфера, то прекращаем работу
        xor rax, rax
        ret



; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    xor rax, rax
    xor r8, r8
    xor r9, r9
    mov r10, 10
    .loop: 
        mov r8b, [rdi + r9]
        cmp r8b, '0'
        jl .end
        cmp r8b, '9'
        jg .end                     ; Проверить число ли аргумент
        sub r8b, '0'                ; Перевод из ASCII в число
        mul r10                     ; Умножаем на основу системы счисления
        add rax, r8                 ; добавляем цифру
        inc r9                      ; инкрементируем длину числа
        jmp .loop
    .end:
        mov rdx, r9
        ret
    ret




; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
    cmp byte[rdi], '-'      ; Проверяем отрицательное ли число
    jne parse_uint          ; Если нет то просто идем к фукцию parse_uint
    inc rdi                 
    call parse_uint         ; Если отрицателен то парсим положительное число
    neg rax                 ; и сделаем его отрицательным
    test rdx, rdx              
    je .end
    inc rdx                 ; Добавляем минус в длину строки
    .end:
        ret 


; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
    xor rax, rax
    xor rcx, rcx
    xor r9, r9
    push rdi
    call string_length      ;Узнать длину строки
    pop rdi
    cmp rax, rdx  
    jle .loop          ;Если длина строки меньше чем длины буфера то идем в цикл
    mov rax,0
    ret
    .loop:
        mov r9b,[rdi+rcx]
        mov [rsi+rcx], r9b
        inc rcx
        cmp byte[rcx+rsi],0 ;Если равно 0, остановить работу
        jnz .loop
    mov rax, rdx
    ret
