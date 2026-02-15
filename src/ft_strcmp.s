BITS 64
default rel

section .text
global ft_strcmp

; int ft_strcmp(const char *left_string_pointer, const char *right_string_pointer)
ft_strcmp:
ft_strcmp_loop:
    movzx eax, byte [rdi]           ; left unsigned char
    movzx edx, byte [rsi]           ; right unsigned char
    cmp eax, edx
    jne ft_strcmp_diff

    test eax, eax                   ; both bytes are equal: check for terminator
    je ft_strcmp_equal

    inc rdi
    inc rsi
    jmp ft_strcmp_loop

ft_strcmp_diff:
    sub eax, edx                    ; strcmp result
    ret

ft_strcmp_equal:
    xor eax, eax                    ; identical strings
    ret
