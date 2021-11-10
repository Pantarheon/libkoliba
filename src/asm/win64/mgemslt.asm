;;	mgemslt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 mgemslt.asm

section .text

default rel

EXTERN	KOLIBA_ConvertSlutToGeminix

GLOBAL	KOLIBA_MultiplyGeminixBySlut

KOLIBA_MultiplyGeminixBySlut:

	; On Entry:
	;
	;	RCX = address of output GEMINIX
	;	RDX = multiplicand GEMINIX (const)
	;	R8  = multiplier SLUT (const)
	;
	; On Exit:
	;
	;	RAX = GEMINIX on success, NULL on failure
	;
	; Local:
	;	[RSP+20h] = temporary GEMINIX

	push	rbp
	mov		rbp, rsp
	push	rcx				; [RBP-8]
	push	rdx				; [RBP-16]
	sub		rsp, (24+4)*8

	sub		eax, eax
	test	rdx, rdx
	mov		rdx, r8
	je		.done
	test	rdx, rdx
	jrcxz	.done			; No output to write to
	lea		rcx, [rsp+20h]
	je		.done
	call	KOLIBA_ConvertSlutToGeminix
	test	rax, rax
	mov		rcx, [rbp-8]
	je		.done
	mov		rdx, [rbp-16]
	mov		r8, rax

	call	KOLIBA_ConvertSlutToGeminix

.done:

	leave

	ret

section .drectve	info

	db	'-export:KOLIBA_MultiplyGeminixBySlut '
