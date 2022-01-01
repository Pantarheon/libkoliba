;;	midpointshift.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 midpointshift.asm

section .text

default rel

EXTERN	KOLIBA_Ones

GLOBAL	KOLIBA_MidpointShift

KOLIBA_MidpointShift:

	; On Entry:
	;
	;	XMM0 = midpoint
	;
	; On Exit:
	;
	;	XMM0 = shift
	;
	lea		rax, [KOLIBA_Ones]
	subsd	xmm2, xmm2
	movq	[rsp+8], xmm0
	comisd	xmm0, xmm2
	movq	xmm0, [rax]
	jbe		.done

	comisd	xmm0, [rsp+8]
	jbe		.done

	fld1
	fchs
	fld		qword [rsp+8]
	fyl2x
	fstp	qword [rsp+8]
	fwait
	divsd	xmm0, [rsp+8]

.done:

	ret

section .drectve	info

	db	'-export:KOLIBA_MidpointShift '
