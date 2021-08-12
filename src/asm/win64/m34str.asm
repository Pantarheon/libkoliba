;;	m34str.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 m34str.asm

section .text

default rel

EXTERN	KOLIBA_PrintM34tFormat, KOLIBA_ScanM34tFormat
EXTERN	KOLIBA_DoublesToString, KOLIBA_StringToDoubles

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

	mov	r9d, 12
	lea	r10, [KOLIBA_PrintM34tFormat]
	jmp	KOLIBA_DoublesToString

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

	mov	r8d, 12
	lea	r9, [KOLIBA_ScanM34tFormat]
	jmp	KOLIBA_StringToDoubles



section .drectve	info

	db	'-export:KOLIBA_MatrixToString '
	db	'-export:KOLIBA_StringToMatrix '

