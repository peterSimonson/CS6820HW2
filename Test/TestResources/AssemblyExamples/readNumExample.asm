
  global _main
  extern _printf
  extern _scanf

  section .text
_main:
  push    rbx

  lea     rdi, [formatStr]
  lea     rsi, [msg]
  xor     rax, rax
  call    _printf

  lea     rdi, [intIn]
  lea     rsi, [num1]
  xor     rax, rax
  call    _scanf

  lea     rdi, [formatInt]
  mov     rsi, [num1]
  xor     rax, rax

  call    _printf

  pop     rbx
  ret

section .data

formatInt:
default rel
  db    "%d", 0

intIn:
default rel
  db    "%d", 0

formatStr:
default rel
  db    "%s", 10, 0

msg:
default rel
  db    "Enter a num:", 0

num1: dq 1