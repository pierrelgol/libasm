BITS 64
default rel

section .text
global ft_read
extern __errno_location

; ssize_t ft_read(int file_descriptor, void *buffer_pointer, size_t byte_count)
ft_read:
    mov rax, 0                      ; SYS_read
    syscall
    test rax, rax
    js ft_read_error
    ret

ft_read_error:
    neg rax                         ; convert -errno to errno
    mov edi, eax                    ; keep errno value for store

    sub rsp, 8                      ; align stack before external call
    call __errno_location
    add rsp, 8

    mov dword [rax], edi            ; *errno = errno_value
    mov rax, -1                     ; POSIX error return
    ret
