;;	msltslt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 msltslt.asm

section .text

default rel

EXTERN	KOLIBA_ConvertSlutToGeminix, KOLIBA_ConvertGeminixToSlut
EXTERN	KOLIBA_MultiplyGeminixBySlut

GLOBAL	KOLIBA_MultiplySlutBySlut

KOLIBA_MultiplySlutBySlut:

	; On Entry:
	;
	;	RCX = address of output SLUT
	;	RDX = address of multiplicand SLUT (const)
	;	R8  = address of multiplier SLUT (const)
	;
	; On Exit:
	;
	;	RAX = address of output SLUT on success, NULL on failure
	;
	; Local:
	;	[RSP+20h] = address of temporary GEMINIX

	push	rbp
	mov		rbp, rsp
	push	rcx				; [RBP-8]
	push	r8				; [RBP-16]
	sub		rsp, (24+4)*8

	lea		rcx, [rbp-(24+2)*8]	; local geminix
	call	KOLIBA_ConvertSlutToGeminix
	mov		rcx, rax
	mov		rdx, rax
	mov		r8, [rbp-16]

	call	KOLIBA_MultiplyGeminixBySlut

	mov		rdx, rax
	mov		rcx, [rbp-8]
	call	KOLIBA_ConvertGeminixToSlut

	leave

	ret

section .drectve	info

	db	'-export:KOLIBA_MultiplySlutBySlut '
