global _main
  extern _printf

  section .text
_main:
  push    rbx

  mov     rax, 2
  mov     rbx, rax
  mov     rdi, 1
  mov     rsi, 3
  
  again12:
  cmp rdi, rsi
  jge done12
  mul rbx
  inc rdi

  jmp again12

  done12:
  mov     [num1], rax

  lea     rdi, [formatInt]
  mov     rsi, [num1]
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

section .bss

num1: resb 8