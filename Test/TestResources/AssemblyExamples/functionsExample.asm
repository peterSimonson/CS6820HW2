
  global _main
  extern _printf

  section .text
_main:
  push    rbx

  mov rdi, 10
  mov rsi, 5

  call multiply

  lea rdi, [formatInt]
  mov rsi, rax
  xor rax, rax
  call _printf

  pop     rbx
  ret

  multiply:
    push rbp
    mov  rbp, rsp

    mov rax, rdi

    mul rsi

    mov rsp, rbp
    pop rbp

    ret

section .data

formatInt:
default rel
  db    "%d", 10, 0
