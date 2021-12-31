;;	anglecos.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 anglecos.asm

section .text

default rel

EXTERN	KOLIBA_AngleRadians

GLOBAL	KOLIBA_AngleCosine, KOLIBA_AngleFactorCosine, KOLIBA_AngleCosineSquared
GLOBAL	KOLIBA_AngleNormalizedCosine, KOLIBA_AngleFactorNormalizedCosine

KOLIBA_AngleFactorCosine:

	; On Entry:
	;
	;	RCX  = address of ANGLE structure
	;	XMM1 = factor
	;
	; On Exit:
	;
	;	XMM0 = cosine of angle*factor
	;
	sub		rsp, 5*8

	movq	[rsp+4*8], xmm1

	call	KOLIBA_AngleRadians
	movq	[rsp+8], xmm0
	fld		qword [rsp+4*8]
	fmul	qword [rsp+8]
	fcos
	fstp	qword [rsp+16]
	fwait
	movq	xmm0, [rsp+16]

	add		rsp, 5*8
	ret

align 16, int3
KOLIBA_AngleNormalizedCosine:

	; On Entry:
	;
	;	RCX = address of ANGLE structure
	;
	; On Exit:
	;
	;	XMM0 = cosine of normalized angle
	;
	sub		rsp, 5*8

	call	KOLIBA_AngleRadians
	movq	[rsp+8], xmm0
	fldpi
	fadd	st0, st0
	fld		qword [rsp+8]

align 8
.loop:

	fprem1
	fstsw	ax
	test	ah, 100b
	jne		.loop
	fadd	st0, st1
	fprem1

	fcos
	fstp	qword [rsp+16]
	fwait
	fstp	st0
	movq	xmm0, [rsp+16]

	add		rsp, 5*8
	ret

align 16, int3
KOLIBA_AngleCosineSquared:

	; On Entry:
	;
	;	RCX  = address of ANGLE structure
	;
	; On Exit:
	;
	;	XMM0 = square of cosine of angle
	;
	sub		rsp, 5*8

	call	KOLIBA_AngleRadians
	movq	[rsp+8], xmm0
	fld		qword [rsp+8]
	fcos
	fmul	st0, st0
	fstp	qword [rsp+16]
	fwait
	movq	xmm0, [rsp+16]

	add		rsp, 5*8
	ret

align 8, int3
KOLIBA_AngleCosine:

	; On Entry:
	;
	;	RCX = address of ANGLE structure
	;
	; On Exit:
	;
	;	XMM0 = cosine of angle
	;
	sub		rsp, 5*8

	call	KOLIBA_AngleRadians
	movq	[rsp+8], xmm0
	fld		qword [rsp+8]
	fcos
	fstp	qword [rsp+16]
	fwait
	movq	xmm0, [rsp+16]

	add		rsp, 5*8
	ret

align 16, int3
KOLIBA_AngleFactorNormalizedCosine:

	; On Entry:
	;
	;	RCX  = address of ANGLE structure
	;	XMM1 = factor
	;
	; On Exit:
	;
	;	XMM0 = cosine of normalized angle*factor
	;
	sub		rsp, 5*8

	movq	[rsp+4*8], xmm1

	call	KOLIBA_AngleRadians
	movq	[rsp+8], xmm0
	fldpi
	fadd	st0, st0
	fld		qword [rsp+8]

align 8
.loop:

	fprem1
	fstsw	ax
	test	ah, 100b
	jne		.loop
	fadd	st0, st1
	fprem1

	fmul	qword [rsp+4*8]
	fcos
	fstp	qword [rsp+16]
	fwait
	fstp	st0
	movq	xmm0, [rsp+16]

	add		rsp, 5*8
	ret

section .drectve	info

	db	'-export:KOLIBA_AngleCosine '
	db	'-export:KOLIBA_AngleCosineSquared '
	db	'-export:KOLIBA_AngleNormalizedCosine '
	db	'-export:KOLIBA_AngleFactorNormalizedCosine '
	db	'-export:KOLIBA_AngleFactorCosine '
