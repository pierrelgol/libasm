BITS 64
default rel

section .text
global ft_strlen

; size_t ft_strlen(const char *string_pointer)
ft_strlen:
    xor rcx, rcx                    ; length counter = 0

ft_strlen_loop:
    cmp byte [rdi + rcx], 0         ; end of string?
    je ft_strlen_done
    inc rcx                         ; advance length
    jmp ft_strlen_loop

ft_strlen_done:
    mov rax, rcx                    ; return length
    ret
