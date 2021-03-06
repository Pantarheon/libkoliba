;;
;;
;;	fixdbl.asm
;;
;;	Copyright 2019 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -fwin64 fixdbl.asm
;;
;;	This is needed because MSC produces
;;	a truly ridiculously slow result when
;;	compiling fixdbl.c. It is deceptively
;;	simple in assembly language, at least
;;	when it comes to Intel processors and
;;	compatibles.

section	.text

GLOBAL	KOLIBA_FixDoubles, KOLIBA_NetDoubles

KOLIBA_NetDoubles:
KOLIBA_FixDoubles:
;
;	On Entry:
;
;		RCX = address of array of MSB(LSB)-first doubles
;		EDX = number of said doubles
;
;	On Exit:
;
;		RAX = address of converted doubles or NULL

	mov	rax, rcx	; Do not change, it is the return value
	jrcxz	.done
	test	edx, edx
	mov	ecx, edx	; ECX = count, RAX = doubles
	jne	.loop

.done:

	ret

align 16, int3
.loop:

	; A double is just a 64-bit value. We can
	; swap it from MSB first to LSB first pretending
	; it is just a generic 64-bit 8-byte value.

	mov	rdx, [rax+(rcx-1)*8]
	bswap	rdx
	mov	[rax+(rcx-1)*8], rdx
	loop	.loop

	ret

section	.drectve	info

	db	'-export:KOLIBA_FixDoubles '
	db	'-export:KOLIBA_NetDoubles '
