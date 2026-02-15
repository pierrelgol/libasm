BITS 64
default rel

section .text
global ft_strcpy

; char *ft_strcpy(char *destination_pointer, const char *source_pointer)
ft_strcpy:
    mov rax, rdi                    ; keep original destination for return

ft_strcpy_copy_loop:
    mov dl, [rsi]                   ; read source byte
    mov [rdi], dl                   ; write destination byte
    inc rsi                         ; advance source pointer
    inc rdi                         ; advance destination pointer
    test dl, dl                     ; copied null terminator?
    jne ft_strcpy_copy_loop

    ret
