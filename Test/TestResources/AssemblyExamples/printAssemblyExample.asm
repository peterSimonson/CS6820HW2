
  global _main
  extern _printf

  section .text
_main:
  push    rbx


  lea     rdi, [formatInt]
  mov     rsi, 1
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