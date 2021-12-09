global _main
extern _printf

section .data
	formatStr:
	default rel
	  db  "%s", 10, 0
	formatInt:
	default rel
	  db  "%d", 10, 0
	formatIsh:
	default rel
	  db  "%f", 10, 0

section .bss
	var1: resb 8

section .text
	lea rdi, [formatInt]
	mov rsi, [var1]
	xor rax, rax
	call _printf

