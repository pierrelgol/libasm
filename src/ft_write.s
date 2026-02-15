BITS 64
default rel

section .text
global ft_write
extern __errno_location

; ssize_t ft_write(int file_descriptor, const void *buffer_pointer, size_t byte_count)
ft_write:
    mov rax, 1                      ; SYS_write
    syscall
    test rax, rax
    js ft_write_error
    ret

ft_write_error:
    neg rax                         ; convert -errno to errno
    mov edi, eax                    ; keep errno value for store

    sub rsp, 8                      ; align stack before external call
    call __errno_location
    add rsp, 8

    mov dword [rax], edi            ; *errno = errno_value
    mov rax, -1                     ; POSIX error return
    ret
