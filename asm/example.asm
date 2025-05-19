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
 lea rsi, [rel+litString_0]
 mov rdx, 4
 mov rdi, 1
 mov rax, 1
 syscall
 pop rbp
 ret
 lea rsi, [rel+litString_1]
 mov rdx, 10
 mov rdi, 1
 mov rax, 1
 syscall
 mov rax, 1
 pop rbp
 ret
litString_0: db "Yay!", 0
litString_1: db "pleasework", 0
