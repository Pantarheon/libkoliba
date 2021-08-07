;;	sltstr.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 sltstr.asm

section .text

default rel

EXTERN	KOLIBA_PrintSlttFormat, KOLIBA_ScanSlttFormat, sprintf, sscanf

GLOBAL	KOLIBA_SlutToString, KOLIBA_StringToSlut

KOLIBA_SlutToString:

	; On Entry:
	;
	;	RCX = address of string to write to
	;	RDX = address of input SLUT, constant
	;	R8D = bytes in string, must be 414 or more.
	;
	; On Exit:
	;
	;	RAX = address of string from RCX, or NULL.

%define	STACKBYTES	(8*(22+4))

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
	cmp	r8d, 414
	mov	ecx, 22
	jb	.done

rep	movsq

	mov	rcx, rbx
	lea	rdx, [KOLIBA_PrintSlttFormat]
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
KOLIBA_StringToSlut:

	; On Entry:
	;
	;	RCX = address of SLUT to fill out
	;	RDX = address of a SLTT string
	;
	; On Exit:
	;
	;	RAX = address of the SLUT, or NULL

	push	rbx
	sub	rsp, STACKBYTES

	jrcxz	.done
	mov	rbx, rcx
	sub	ecx, ecx
	test	rdx, rdx
	mov	cl, 22
	je	.done

.loop:

	lea	r8, [rbx+16+8*(rcx-1)]
	mov	[rsp+32+8*(rcx-1)], r8
	loop	.loop

	mov	rcx, rdx
	lea	rdx, [KOLIBA_ScanSlttFormat]
	mov	r8, rbx
	lea	r9, [rbx+8]
	call	sscanf

	sub	ecx, ecx
	cmp	eax, 24
	cmovne	rbx, rcx
	mov	rax, rbx

.done:

	add	rsp, STACKBYTES
	pop	rbx
	ret


section .drectve	info

	db	'-export:KOLIBA_SlutToString '
	db	'-export:KOLIBA_StringToSlut '

