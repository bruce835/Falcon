section .text
  global _start

_start:
  call main

  mov rax, 0x2000001
  xor rdi, rdi
  syscall

main:
 push rbp
 mov rbp, rsp
 lea rsi, [rel+litString_0]
 mov rdx, 17
 mov rdi, 1
 mov rax, 0x2000004
 syscall
 mov rax, 0
 pop rbp
 ret
litString_0: db "HEY THIS IS GREAT", 0
