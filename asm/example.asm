section .text
  global _start

_start:
  call main

  mov rax, 60
  xor rdi, rdi
  syscall

main:
 push rbp
 mov rbp, rsp
 lea rsi, [rel+litString]
 mov rdx, 24
 mov rdi, 1
 mov rax, 1
 syscall
 mov rax, 1
 pop rbp
 ret
litString: db "My first Falcon program!", 0
