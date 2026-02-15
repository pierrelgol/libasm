BITS 64
default rel

section .text
global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

; char *ft_strdup(const char *source_pointer)
ft_strdup:
    push rbx                        ; preserve callee-saved register, align stack for calls
    mov rbx, rdi                    ; keep source pointer across calls

    call ft_strlen wrt ..plt        ; rax = source length
    inc rax                         ; include null terminator

    mov rdi, rax                    ; malloc(size)
    call malloc wrt ..plt
    test rax, rax
    je ft_strdup_malloc_failed

    mov rdi, rax                    ; destination
    mov rsi, rbx                    ; source
    call ft_strcpy wrt ..plt        ; returns destination in rax

    pop rbx
    ret

ft_strdup_malloc_failed:
    pop rbx
    ret
