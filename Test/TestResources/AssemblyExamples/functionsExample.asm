
  global _main
  extern _printf

  section .text
_main:
  push    rbx

  mov rcx, 10
  mov rdx, 5

  call multiply

  mov rsi, rax
  lea rdi, [formatInt]
  xor rax, rax
  call _printf

  pop     rbx
  ret

  multiply:
    push rbp
    mov  rbp, rsp

    mov rax, rcx

    mul rdx

    mov rsp, rbp
    pop rbp

    ret

section .data

formatInt:
default rel
  db    "%d", 10, 0
