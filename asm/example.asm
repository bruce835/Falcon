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
 lea rsi, [rel+litString]
 mov rdx, 13
 mov rdi, 1
 mov rax, 0x2000004
 syscall
 mov rax, 1
 pop rbp
 ret
litString: db "Yay!", 0
