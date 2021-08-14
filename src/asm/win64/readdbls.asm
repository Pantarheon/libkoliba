;;	readdbls.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 readdbls.asm

section .text

default rel

EXTERN	KOLIBA_ScanM34tFormat, fscanf, fopen, fclose, KOLIBA_ResetMatrix

GLOBAL	KOLIBA_ReadDoublesFromOpenFile

KOLIBA_ReadDoublesFromOpenFile:

	; Since we use this only internally, and only from asm routines,
	; we can use R10 to accept an extra parameter.
	;	
	; On Entry:
	;
	;	RCX = address of output DOUBLES
	;	RDX = handle of FILE to read from
	;	R8D = number of doubles to scan
	;	R9  = address of scan format string
	;	R10 = function to call on failure (or NULL)
	;
	; On Exit:
	;
	;	RAX = DOUBLES on success, NULL on failure

	push	rbp
	push	rbx
	push	rdi
	push	rsi
	push	r12

	; We have to reserve 4 quads at the bottom of the stack.
	; Above that, we need (R8D-2) quads to pass args to fscanf.
	; Above that we need R8D quads for fscanf to write to.
	; But if R8D happens to be an odd number, we must round it
	; up to the nearest even number (or round down its negative).
	; Plus we need an extra quad just so RSP is 16-byte aligned.
	lea	eax, [2*r8d]
	mov	rbp, rsp
	neg	rax
	and	al, ~3	; ~2 would be enough but ~3 does not hurt.
	lea	rsp, [rsp+8*(rax-3)]	; = sub RSP, 8*((R8D-2)+R8D+4+1)

	mov	rdi, rcx
	mov	rbx, r10
	mov	r12d, r8d
	sub	eax, eax

	test	rdx, rdx
	jrcxz	.done

	lea	rsi, [rsp+8*(r8+2)]
	lea	ecx, [r8d-2]
	jne	.loop

.rst:

	test	rbx, rbx
	mov	rcx, rdi
	mov	eax, ebx
	je	.done
	call	rbx
	sub	eax, eax
	jmp	.done

.loop:

	lea	rax, [rsi+8*(rcx+1)]
	mov	[rsp+32+8*(rcx-1)], rax
	loop	.loop

	mov	rcx, rdx
	mov	rdx, r9
	mov	r8, rsi
	lea	r9, [rsi+8]
	call	fscanf
	cmp	eax, r12d
	mov	ecx, eax
	mov	rax, rdi
	jne	.rst

rep	movsq

.done:

	mov	rsp, rbp
	pop	r12
	pop	rsi
	pop	rdi
	pop	rbx
	pop	rbp
	ret


