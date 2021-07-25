;;
;;
;;	fixslut.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -fwin32 fixslut.asm

default	rel

section	.rdata

; We make this public in the hope the Microsoft linker will merge this
; with any identically named constants (the names are produced by MSC).

GLOBAL	__real@3df0000000000000

__real@3df0000000000000	dq	03df0000000000000h

section	.text

GLOBAL	_KOLIBA_FixSlut, _KOLIBA_FixFlut

_KOLIBA_FixFlut:
_KOLIBA_FixSlut:

	; On Entry:
	;
	;	[esp+4] = address of KOLIBA_SLUT or KOLIBA_FLUT
	;
	; On Exit:
	;
	;	eax = same as [esp+4] on entry

	mov		eax, [esp+4]
	sub		ecx, ecx
	test	eax, eax
	mov		cl, 24
	je		.done

	fld		qword [__real@3df0000000000000]
	fldz
	jmp		.loop

align 16, int3
.loop:

	fld		qword [eax+(ecx-1)*8]
	fabs
	fcomip	st2
	jae		.next
	fst		qword [eax+(ecx-1)*8]

.next:

	loop	.loop
	fcompp

.done:

	ret

section	.drectve	info

	db	'-export:_KOLIBA_FixSlut '
	db	'-export:_KOLIBA_FixFlut '
