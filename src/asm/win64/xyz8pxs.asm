;;
;;
;;	xyz8pxs.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -fwin64 pal8rgba.asm

section	.text

GLOBAL	KOLIBA_ScaledXyzToRgba8Pixel

KOLIBA_ScaledXyzToRgba8Pixel:

	; On Entry:
	;
	;	RCX = address of output RGBA8 pixel
	;	RDX = address of input XYZ (const)
	;	R8  = address of output conversion table or NULL
	;
	; On Exit:
	;
	;	RAX = address of output RGBA8 pixel

	; Make R11D = 255, R10D = 0, R9D blue, ECX green, EDX red.
	sub			r11d, r11d
	cvtsd2si	r9d, [rdx+16]
	mov			rax, rcx
	cvtsd2si	ecx, [rdx+8]
	mov			r10d, r11d
	cvtsd2si	edx, [rdx]
	not			r11b

	; If any of them is negative, make it a zero.
	test		r9d, r9d
	cmovs		r9d, r10d
	js	.green

	cmp			r9d, r11d
	cmova		r9d, r11d

.green:

	test		ecx, ecx
	cmovs		ecx, r10d
	js	.red

	cmp			ecx, r11d
	cmova		ecx, r11d

.red:

	test		edx, edx
	cmovs		edx, r10d
	js	.conv

	cmp			edx, r11d
	cmova		edx, r11d

.conv:

	; Apply conversion table, if any
	test		r8, r8
	je	.finalize

	mov			r9b, [r8+r9]
	mov			cl, [r8+rcx]
	mov			dl, [r8+rdx]

.finalize:

	mov			dh, cl
	mov			[rax+2], r9b
	mov			[rax], dx

	ret

















section	.drectve	info

	db	'-export:KOLIBA_ScaledXyzToRgba8Pixel '

