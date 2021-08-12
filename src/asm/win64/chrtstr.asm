;;	chrtstr.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 chrtstr.asm

section .text

default rel


EXTERN	KOLIBA_PrintChrtFormat, KOLIBA_ScanChrtFormat
EXTERN	KOLIBA_DoublesToString, KOLIBA_StringToDoubles

GLOBAL	KOLIBA_ChromatToString, KOLIBA_StringToChromat

KOLIBA_ChromatToString:

	; On Entry:
	;
	;	RCX = address of string to write to
	;	RDX = address of input SLUT, constant
	;	R8D = bytes in string, must be 8*17+6 or more.
	;
	; On Exit:
	;
	
	mov	r9d, 8
	lea	r10, [KOLIBA_PrintChrtFormat]
	jmp	KOLIBA_DoublesToString

align 16, int3
KOLIBA_StringToChromat:

	; On Entry:
	;
	;	RCX = address of SLUT to fill out
	;	RDX = address of a SLTT string
	;
	; On Exit:
	;
	;	RAX = address of the SLUT, or NULL

	mov	r8d, 8
	lea	r9, [KOLIBA_ScanChrtFormat]
	jmp	KOLIBA_StringToDoubles


section .drectve	info

	db	'-export:KOLIBA_ChromatToString '
	db	'-export:KOLIBA_StringToChromat '

