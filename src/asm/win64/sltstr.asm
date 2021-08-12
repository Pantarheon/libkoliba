;;	sltstr.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 sltstr.asm

section .text

default rel

EXTERN	KOLIBA_PrintSlttFormat, KOLIBA_ScanSlttFormat
EXTERN	KOLIBA_DoublesToString, KOLIBA_StringToDoubles

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
	
	mov	r9d, 24
	lea	r10, [KOLIBA_PrintSlttFormat]
	jmp	KOLIBA_DoublesToString

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

	mov	r8d, 24
	lea	r9, [KOLIBA_ScanSlttFormat]
	jmp	KOLIBA_StringToDoubles


section .drectve	info

	db	'-export:KOLIBA_SlutToString '
	db	'-export:KOLIBA_StringToSlut '

