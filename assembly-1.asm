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
	var1: dq 12
	var2: dq 2
	var3: dq 2
	var4: dq 17
	var5: dq 1542
	var6: dq 0
	var7: dq 29
	var8: dq 42
	var9: dq 42
	var10: dq 42
	var11: dq 42
	var12: dq 7006652
	var13: dq 1
	var14: dq 10
	var15: dq 9
	var16: dq 31
	var17: dq 1337
	var18: dq -42
	var19: dq -42
	var20: dq -42
	var21: dq -42
	var22: dq 8
	var23: dq -1
	var24: dq -1
	var25: dq 5
	var26: dq 5
	var27: dq -5
	var28: dq 1
	var29: dq 1
	var30: dq 1
	var31: dq 1
	var32: dq 1
	var33: dq 1
	var34: dq 1
	var35: dq 5
	var36: dq 5
	var37: dq -3
	var38: dq -4
	var39: dq -4
	var40: dq 33
	var41: dq 27
	var42: dq 256
	var43: dq 19683
	var44: dq 2147483647
	var45: dq 41
	float1: dq 3.500000
	float2: dq 3.500000
	float3: dq 3.550000
	float4: dq 5.859808
	issue1: dq 5
	issue2: dq 7
	orig: dq 6
	copy: dq 6
	var49: dq 14
	var50: dq 10
	var51: dq -10
	var52: dq 144
	var53: dq 29336
	writeConstant70:
	default rel
	  db  "This begins the user input section", 0
	writeConstant73:
	default rel
	  db  "Supply data and hit enter", 0
	writeConstant76:
	default rel
	  db  "Enter a number: ", 0
	user1: dq 0
	writeConstant80:
	default rel
	  db  "Enter a number: ", 0
	user2: dq 0
	writeConstant84:
	default rel
	  db  "Enter a number: ", 0
	user3: dq 0
	writeConstant88:
	default rel
	  db  "Enter a number: ", 0
	user4: dq 0
	result1: dq 5
	a: dq 2
	b: dq 3
	result2: dq 5
	result3: dq 6
	result4: dq 4
	result5: dq 9
	result7: dq -1
	result8: dq 58
	result9: dq 18
	writeConstant102:
	default rel
	  db  "Result of adding first and second user inputs: ", 0
	writeConstant105:
	default rel
	  db  "Result of multiplying third and fourth user inputs: ", 0
	writeConstant108:
	default rel
	  db  "Enter a radius: ", 0
	userRadius: dq 0
	writeConstant112:
	default rel
	  db  "The volume is: ", 0
	writeConstant115:
	default rel
	  db  "Congratulations on the great semester!", 0

section .bss
	userResult1: resb 8
	userResult2: resb 8
	userResult3: resb 8
	userResult4: resb 8
	userResult5: resb 8
	userResult6: resb 8
	volume: resb 8

section .text
	_main:
	push rbx
	lea rdi, [formatOutInt]
	mov rsi, [var1]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var2]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var3]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var4]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var5]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var6]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var7]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var8]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var9]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var10]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var11]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var12]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var13]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var14]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var15]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var16]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var17]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var18]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var19]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var20]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var21]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var22]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var23]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var24]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var25]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var26]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var27]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var28]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var29]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var30]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var31]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var32]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var33]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var34]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var35]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var36]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var37]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var38]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var39]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var40]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var41]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var42]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var43]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var44]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var45]
	xor rax, rax
	call _printf
	sub rsp, 8
	lea rdi, [formatOutIsh]
	movq xmm0, qword [float1]
	mov rax, 1
	call _printf
	add rsp, 8
	sub rsp, 8
	lea rdi, [formatOutIsh]
	movq xmm0, qword [float2]
	mov rax, 1
	call _printf
	add rsp, 8
	sub rsp, 8
	lea rdi, [formatOutIsh]
	movq xmm0, qword [float3]
	mov rax, 1
	call _printf
	add rsp, 8
	sub rsp, 8
	lea rdi, [formatOutIsh]
	movq xmm0, qword [float4]
	mov rax, 1
	call _printf
	add rsp, 8
	lea rdi, [formatOutInt]
	mov rsi, [orig]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [copy]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var49]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var50]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var51]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var52]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [var53]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant70]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant73]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant76]
	xor rax, rax
	call _printf
	lea rdi, [formatInNum]
	lea rsi, [user1]
	xor rax, rax
	call _scanf
	lea rdi, [formatOutInt]
	mov rsi, [user1]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant80]
	xor rax, rax
	call _printf
	lea rdi, [formatInNum]
	lea rsi, [user2]
	xor rax, rax
	call _scanf
	lea rdi, [formatOutInt]
	mov rsi, [user2]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant84]
	xor rax, rax
	call _printf
	lea rdi, [formatInNum]
	lea rsi, [user3]
	xor rax, rax
	call _scanf
	lea rdi, [formatOutInt]
	mov rsi, [user3]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant88]
	xor rax, rax
	call _printf
	lea rdi, [formatInNum]
	lea rsi, [user4]
	xor rax, rax
	call _scanf
	lea rdi, [formatOutInt]
	mov rsi, [user4]
	xor rax, rax
	call _printf
	mov rcx, [user1]
	mov rax, [user2]
	add rcx, rax
	mov [userResult1], rcx
	lea rdi, [formatOutInt]
	mov rsi, [userResult1]
	xor rax, rax
	call _printf
	mov rcx, [user3]
	mov rax, [user4]
	sub rcx, rax
	mov [userResult2], rcx
	lea rdi, [formatOutInt]
	mov rsi, [userResult2]
	xor rax, rax
	call _printf
	mov rcx, [user1]
	mov rbx, [user2]
	mov rbx, rbx
	mov rax, rcx
	mul rbx
	mov rcx, rax
	mov [userResult3], rcx
	lea rdi, [formatOutInt]
	mov rsi, [userResult3]
	xor rax, rax
	call _printf
	mov rcx, [user3]
	mov rbx, [user4]
	mov rbx, rbx
	mov rax, rcx
	push rdx
	xor rdx, rdx
	div rbx
	mov rcx, rax
	pop rdx
	mov [userResult4], rcx
	lea rdi, [formatOutInt]
	mov rsi, [userResult4]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result1]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result2]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result3]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result4]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result5]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result7]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result8]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [result9]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant102]
	xor rax, rax
	call _printf
	mov rdi, [user1]
	mov rsi, [user2]
	call add
	mov rcx,rax
	mov [userResult5], rcx
	lea rdi, [formatOutInt]
	mov rsi, [userResult5]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant105]
	xor rax, rax
	call _printf
	mov rdi, [user3]
	mov rsi, [user4]
	call mult
	mov rcx,rax
	mov [userResult6], rcx
	lea rdi, [formatOutInt]
	mov rsi, [userResult6]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant108]
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
	lea rsi, [writeConstant112]
	xor rax, rax
	call _printf
	lea rdi, [formatOutInt]
	mov rsi, [volume]
	xor rax, rax
	call _printf
	lea rdi, [formatOutStr]
	lea rsi, [writeConstant115]
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
	again108:
	cmp rdi, rsi
	jge done108
	mul rbx
	inc rdi
	jmp again108
	done108:
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
	mov rax,rcx
	mov rsp, rbp
	pop rbp
	ret

