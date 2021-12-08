
  global _main
  extern _printf

  section .text
_main:
  push    rbx

  sub rsp, 8
  movq xmm0, qword [ish1]
  lea rdi, [formatIsh]
  mov rax, 1
  call _printf
  add rsp, 8

  pop     rbx
  ret

section .data

formatIsh:
default rel
  db    "%f", 10, 0

ish1: dq 1.5