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

section .text
	_main:
	push rbx
	mov [result], rcx
	mov [result], rcx
	lea rdi, [formatInNum]
	lea rsi, [var1]
	xor rax, rax
	call _scanf
	lea rdi, [formatOutInt]
	mov rsi, [result1]
	xor rax, rax
	call _printf
	mov rdi, [var1]
	mov rsi,3
	call add
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
	mov rcx,rdi
	mov rax,rsi
	add rcx, rax
	mov rax,rcx
	mov rsp, rbp
	pop rbp
	ret
	mult:
	push rbp
	mov rbp, rsp
	mov rcx,rdi
	mov rbx,rsi
	mov rbx, rbx
	mov rax, rcx
	mul rbx
	mov rcx, rax
	mov rax,rcx
	mov rsp, rbp
	pop rbp
	ret

