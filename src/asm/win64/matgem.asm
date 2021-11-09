;;	matgem.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 mulgems.asm

section .text

default rel

EXTERN	KOLIBA_MultiplyGeminices, KOLIBA_FixGeminix

GLOBAL	KOLIBA_MatrixGeminixProduct

KOLIBA_MatrixGeminixProduct:

	; On Entry:
	;
	;	RCX = address of output GEMINIX
	;	RDX = GEMINIX (const)
	;	R8  = MATRIX (const)
	;	R8B = MatrixIsMultiplier (boolean)
	;
	; On Exit:
	;
	;	RAX = GEMINIX on success, NULL on failure
	;
	; Local:
	;	[RSP+20h] = temporary GEMINIX

	push	rsi
	push	rdi
	push	rbp
	mov		rbp, rsp
	sub		rsp, (24+4)*8

	sub		eax, eax
	test	rdx, rdx
	mov		r10, rcx
	je		.done			; No input GEMINIX
	test	r8, r8
	mov		rsi, r8
	jrcxz	.done			; No output to write to
	je		.done			; No input MATRIX
	lea		rdi, [rsp+20h]
	mov		ecx, 12			; Number of doubles in a MATRIX

rep	movsq

	mov		rsi, r8
	mov		cl, 12

rep	movsq

	lea		rdi, [rsp+20h]
	test	r9b, r9b
	mov		rcx, r10
	cmovne	r8, rdx
	cmove	r8, rdi
	cmovne	rdx, rdi

	call	KOLIBA_MultiplyGeminices
	mov		rcx, rax
	jrcxz	.done
	call	KOLIBA_FixGeminix

.done:

	leave
	pop		rdi
	pop		rsi

	ret

section .drectve	info

	db	'-export:KOLIBA_MatrixGeminixProduct '
