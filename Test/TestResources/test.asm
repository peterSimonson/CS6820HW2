global _main
extern _printf
extern _scanf

section .data
	formatOutStr:
	default rel
	  db  "%s", 10, 0
	formatOutInt:
	default rel
	  db  "%d", 10, 0
	formatOutIsh:
	default rel
	  db  "%f", 10, 0
	formatInNum:
	default rel
	  db  "%d", 0
	var1: dq 0
	result1: dq 5
	result3: dq 6
	var2: dq 11

section .bss
	result: resb 8
	result2: resb 8

section .text
	_main:
	push rbx
	mov [result], rcx
	lea rdi, [formatInNum]
	lea rsi, [var1]
	xor rax, rax
	call _scanf
	lea rdi, [formatOutInt]
	mov rsi, [result1]
	xor rax, rax
	call _printf
	mov [result2], rcx
	lea rdi, [formatOutInt]
	mov rsi, [result2]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result3]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result2]
	xor rax, rax
	call _printf
	pop rbx
	ret
	add:
	push rbp
	mov rbp, rsp
	mov rcx, [a]
	mov rax, [b]
	add rcx, rax
	mov rax, [result]
	mov rsp, rbp
	pop rbp
	ret

