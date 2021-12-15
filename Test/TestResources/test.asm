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
	writeConstant12:
	default rel
	  db  "Enter a radius: ", 0
	userRadius: dq 0
	writeConstant16:
	default rel
	  db  "The volume is: ", 0

section .bss
	volume: resb 8

section .text
	_main:
	push rbx
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant12]
	xor rax, rax
	call _printf
	lea rdi, [formatInNum]
	lea rsi, [userRadius]
	xor rax, rax
	call _scanf
	mov rdi, [userRadius]
	call computeApproxSphereVolume
	mov rcx,rax
	mov [volume], rcx
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant16]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [volume]
	xor rax, rax
	call _printf
	pop rbx
	ret
	computeApproxSphereVolume:
	push rbp
	mov rbp, rsp
	mov rcx,rdi
	mov rsi,3
	push rax
	push rbx
	push rdi
	mov rax, rcx
	mov rbx, rcx
	mov rdi, 1
	again12:
	cmp rdi, rsi
	jge done12
	mul rbx
	inc rdi
	jmp again12
	done12:
	mov rcx, rax
	pop rdi
	pop rbx
	pop rax
	mov rbx,4
	mov rbx, rbx
	mov rax, rcx
	mul rbx
	mov rcx, rax
	mov rbx,31416
	mov rbx, rbx
	mov rax, rcx
	mul rbx
	mov rcx, rax
	mov rbx,10000
	mov rbx, rbx
	mov rax, rcx
	push rdx
	xor rdx, rdx
	div rbx
	mov rcx, rax
	pop rdx
	mov rbx,3
	mov rbx, rbx
	mov rax, rcx
	push rdx
	xor rdx, rdx
	div rbx
	mov rcx, rax
	pop rdx
	mov rax,rdx
	mov rsp, rbp
	pop rbp
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

