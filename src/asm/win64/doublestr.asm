;;	doublestr.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 doublestr.asm

section .text

default rel

EXTERN	sprintf, sscanf

GLOBAL	KOLIBA_DoublesToString, KOLIBA_StringToDoubles

; Since this is for internal use only,
; and only called from asm code,
; we can accept an argument in R10.
KOLIBA_DoublesToString:

	; On Entry:
	;
	;	RCX = address of string to write to
	;	RDX = address of input doubles, constant
	;	R8D = bytes in string, must be at least 17*R9D+6
	;	R9D = number of doubles, must be no less than 3
	;	R10 = format string
	;
	; On Exit:
	;
	;	RAX = address of string from RCX, or NULL.

	push	rbp
	push	rbx
	push	rdi
	push	rsi
	mov	eax, r9d
	mov	rbp, rsp
	neg	rax
	and	al, ~1	; Make it a negative even number
	lea	rsp, [rbp+8*rax-3*8]	; Just -3*8 because RAX has an extra -2*8

	lea	rsi, [rdx+16]
	lea	rdi, [rsp+32]

	sub	eax, eax
	mov	rbx, rcx
	test	rdx, rdx
	jrcxz	.done
	je	.done
	lea	r11d, [eax+r9d*8]	; Using the EAX (=0) reduces the size
	movsd	xmm2, [rdx]
	lea	r11d, [r9d+r11d*2+6]	; doubles*17+6 = minimum string size (including final NUL)
	movsd	xmm3, [rdx+8]
	cmp	r8d, r11d
	lea	ecx, [r9d-2]
	jb	.done

rep	movsq

	mov	rcx, rbx
	mov	rdx, r10
	movq	r8, xmm2
	movq	r9, xmm3
	call	sprintf
	mov	rax, rbx

.done:

	mov	rsp, rbp
	pop	rsi
	pop	rdi
	pop	rbx
	pop	rbp
	ret

align 16, int3
KOLIBA_StringToDoubles:

	; On Entry:
	;
	;	RCX = address of DOUBLES to load
	;	RDX = address of a string
	;	R8D = number of doubles, must be at least 3
	;	R9  = address of format string
	;
	; On Exit:
	;
	;	RAX = address of the DOUBLES, or NULL

	push	rbp
	push	rbx
	push	r12
	mov	eax, r8d
	mov	rbp, rsp
	neg	rax
	and	al, ~1	; Make it a negative even number
	lea	rsp, [rbp+8*rax-2*8]	; Just -2*8 because RAX has the extra -2*8

	sub	eax, eax	; Return NULL if need be.
	jrcxz	.done
	mov	rbx, rcx
	test	rdx, rdx
	lea	ecx, [r8d-2]
	je	.done

.loop:

	lea	rax, [rbx+16+8*(rcx-1)]
	mov	[rsp+32+8*(rcx-1)], rax
	loop	.loop

	mov	r12d, r8d
	mov	rcx, rdx
	mov	rdx, r9
	mov	r8, rbx
	lea	r9, [rbx+8]
	call	sscanf

	sub	ecx, ecx
	cmp	eax, r12d
	cmovne	rbx, rcx
	mov	rax, rbx

.done:

	mov	rsp, rbp
	pop	r12
	pop	rbx
	pop	rbp
	ret



