
  global _main
  extern _printf

  section .text
_main:
  push    rbx


  lea     rdi, [formatInt]
  mov     rsi, [num1]
  xor     rax, rax

  call    _printf

  push rax
  mov     rax, 2
  mov     [num1], rax
  pop rax

  lea     rdi, [formatInt]
  mov     rsi, [num1]
  xor     rax, rax

  call    _printf

  lea     rdi, [formatStr]
  lea     rsi, [msg]
  xor     rax, rax

  call    _printf


  pop     rbx
  ret

section .data

formatInt:
default rel
  db    "%d", 10, 0

formatStr:
default rel
  db    "%s", 10, 0

msg:
default rel
  db    "Hello, world", 10, 0

num1: dq 1