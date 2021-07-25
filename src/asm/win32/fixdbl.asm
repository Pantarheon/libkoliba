;;
;;
;;	fixdbl.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -fwin32 fixdbl.asm
;;
;;	This is needed because MSC produces
;;	a truly ridiculously slow result when
;;	compiling fixdbl.c. It is deceptively
;;	simple in assembly language, at least
;;	when it comes to Intel processors and
;;	compatibles.

section	.text

GLOBAL	_KOLIBA_FixDoubles, _KOLIBA_NetDoubles

_KOLIBA_NetDoubles:
_KOLIBA_FixDoubles:
;
;	On Entry:
;
;		[ESP+4] = address of array of MSB(LSB)-first doubles
;		[ESP+8] = number of said doubles
;
;	On Exit:
;
;		EAX = address of converted doubles or NULL

	mov	eax, [esp+4]
	mov	ecx, [esp+8]
	test	eax, eax
	jecxz	.done
	jne	.loop

.done:

	ret

align 16, int3
.loop:

	; A double is just a 64-bit value. We can
	; swap it from MSB first to LSB first pretending
	; it is just a generic 64-bit 8-byte value.
	;
	; Of course, in the 32-bit mode we need to do it
	; separately for the two 32-bit halves, and then
	; swap them as well.

	mov	edx, [eax+(ecx-1)*8]
	bswap	edx
	xchg	edx, [eax+4+(ecx-1)*8]
	bswap	edx
	mov	[eax+(ecx-1)*8], edx
	loop	.loop

	ret

section	.drectve	info

	db	'-export:_KOLIBA_FixDoubles '
	db	'-export:_KOLIBA_NetDoubles '
