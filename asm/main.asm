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
 mov rdx, 7
 mov rdi, 1
 mov rax, 1
 syscall
 mov rax, 0
 pop rbp
 ret
 lea rsi, [rel+litString_1]
 mov rdx, 26
 mov rdi, 1
 mov rax, 1
 syscall
 mov rax, 0
 pop rbp
 ret
litString_0: db "testing", 0
litString_1: db "this line should not print", 0
