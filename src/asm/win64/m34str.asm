;;	m34str.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 m34str.asm

section .text

default rel

EXTERN	KOLIBA_PrintM34tFormat, KOLIBA_ScanM34tFormat, sprintf, sscanf

GLOBAL	KOLIBA_MatrixToString, KOLIBA_StringToMatrix

KOLIBA_MatrixToString:

	; On Entry:
	;
	;	RCX = address of string to write to
	;	RDX = address of input MATRIX, constant
	;	R8D = bytes in string, must be 210 or more.
	;
	; On Exit:
	;
	;	RAX = address of string from RCX, or NULL.

%define	STACKBYTES	(8*(10+4))

	push	rbx
	push	rdi
	push	rsi
	sub	rsp, STACKBYTES

	lea	rsi, [rdx+16]
	lea	rdi, [rsp+32]

	sub	eax, eax
	mov	rbx, rcx
	test	rdx, rdx
	jrcxz	.done
	je	.done
	movsd	xmm2, [rdx]
	movsd	xmm3, [rdx+8]
	cmp	r8d, 210
	mov	ecx, 10
	jb	.done

rep	movsq

	mov	rcx, rbx
	lea	rdx, [KOLIBA_PrintM34tFormat]
	movq	r8, xmm2
	movq	r9, xmm3
	call	sprintf
	mov	rax, rbx

.done:

	add	rsp, STACKBYTES
	pop	rsi
	pop	rdi
	pop	rbx
	ret

align 16, int3
KOLIBA_StringToMatrix:

	; On Entry:
	;
	;	RCX = address of MATRIX to fill out
	;	RDX = address of a M34T string
	;
	; On Exit:
	;
	;	RAX = address of the MATRIX, or NULL

	push	rbx
	sub	rsp, STACKBYTES

	jrcxz	.done
	mov	rbx, rcx
	sub	ecx, ecx
	test	rdx, rdx
	mov	cl, 10
	je	.done

.loop:

	lea	r8, [rbx+16+8*(rcx-1)]
	mov	[rsp+32+8*(rcx-1)], r8
	loop	.loop

	mov	rcx, rdx
	lea	rdx, [KOLIBA_ScanM34tFormat]
	mov	r8, rbx
	lea	r9, [rbx+8]
	call	sscanf

	sub	ecx, ecx
	cmp	eax, 12
	cmovne	rbx, rcx
	mov	rax, rbx

.done:

	add	rsp, STACKBYTES
	pop	rbx
	ret


section .drectve	info

	db	'-export:KOLIBA_MatrixToString '
	db	'-export:KOLIBA_StringToMatrix '

