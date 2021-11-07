;;	mulgems.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 mulgems.asm

section .text

default rel

EXTERN	KOLIBA_MultiplyMatrices

GLOBAL	KOLIBA_MultiplyGeminices

KOLIBA_MultiplyGeminices:

	; On Entry:
	;
	;	RCX = address of output GEMINIX
	;	RDX = multiplicand GEMINIX (const)
	;	R8  = multiplier GEMINIX (const)
	;
	; On Exit:
	;
	;	RAX = GEMINIX on success, NULL on failure
	;
	; Local:
	;	[RSP+20h] = temporary GEMINIX

	push	rbx
	push	rsi
	push	rdi
	push	r12
	push	rbp
	mov		rbp, rsp
	sub		rsp, (24+4)*8

	sub		eax, eax
	jrcxz	.done			; No output to write to
	mov		rdi, rcx
	lea		rsi, [rsp+20h]
	lea		rbx, [rdx+12*8]	; size of KOLIBA_MATRIX
	lea		r12, [r8+12*8]
	mov		rcx, rsi
	call	KOLIBA_MultiplyMatrices
	test	rax, rax
	lea		rcx, [rdi+12*8]
	mov		rdx, rbx
	mov		r8, r12
	je		.done

	call	KOLIBA_MultiplyMatrices
	test	rax, rax
	mov		ecx, 24
	je		.done
	mov		rax, rdi

rep	movsq

align 16
.done:

	leave
	pop		r12
	pop		rdi
	pop		rsi
	pop		rbx

	ret

section .drectve	info

	db	'-export:KOLIBA_MultiplyGeminices '
