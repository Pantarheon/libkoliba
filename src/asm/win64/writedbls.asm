;;	writedbls.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 writedbls.asm

section .text

default rel

EXTERN	fprintf

GLOBAL	KOLIBA_WriteDoublesToOpenFile

KOLIBA_WriteDoublesToOpenFile:

	; On Entry:
	;
	;	RCX = address of input DOUBLES, constant
	;	RDX = handle of FILE to write to
	;	R8D = number of DOUBLES (n)
	;	R9  = address of format string
	;
	; On Exit:
	;
	;	EAX = 0 on success, non-0 on failure

	push	rbp
	push	rdi
	push	rsi

	mov	eax, r8d
	mov	rbp, rsp
	neg	rax
	and	al, ~1
	lea	rsp, [rsp+8*(rax-2)]	; RSP += -8*((n-2)+4)

	lea	rsi, [rcx+16]
	sub	eax, eax
	lea	rdi, [rsp+32]

	mov	al, 1
	test	rdx, rdx
	jrcxz	.done
	movsd	xmm2, [rcx]
	movsd	xmm3, [rcx+8]
	lea	ecx, [r8d-2]
	je	.done

rep	movsq

	; We will write n lines of doubles,
	; each line consisting of 16 hex digits,
	; plus a new line, so 16 bytes per line.
	; Before that we write a 4-byte ID string,
	; plus a new line.
	;
	; So the total we will write is 17n+5,
	; where n is the number of doubles in R8D.
	mov	rcx, rdx
	lea	edi, [8*r8d]
	mov	rdx, r9
	lea	edi, [r8d+2*edi+5]	; edi = 17*n+5 = bytes to write
	movq	r8, xmm2
	movq	r9, xmm3
	call	fprintf
	sub	eax, edi	; EAX = 0 on success, something else on failure.

.done:

	mov	rsp, rbp
	pop	rsi
	pop	rdi
	pop	rbp
	ret


