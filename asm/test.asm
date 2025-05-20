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
 mov rdx, 4
 mov rdi, 1
 mov rax, 0x2000004
 syscall
 lea rsi, [rel+litString_1]
 mov rdx, 6
 mov rdi, 1
 mov rax, 0x2000004
 syscall
 lea rsi, [rel+litString_2]
 mov rdx, 6
 mov rdi, 1
 mov rax, 0x2000004
 syscall
 lea rsi, [rel+litString_3]
 mov rdx, 7
 mov rdi, 1
 mov rax, 0x2000004
 syscall
 mov rax, 1
 pop rbp
 ret
 lea rsi, [rel+litString_4]
 mov rdx, 13
 mov rdi, 1
 mov rax, 0x2000004
 syscall
 mov rax, 0
 pop rbp
 ret
litString_0: db "This", 0
litString_1: db " Still", 0
litString_2: db " Works", 0
litString_3: db " Great!", 0
litString_4: db "dontprintthis", 0
