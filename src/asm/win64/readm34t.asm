;;	readm34t.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 readm34t.asm

section .text

default rel

EXTERN	KOLIBA_ScanM34tFormat, fscanf, fopen, fclose, KOLIBA_ResetMatrix

GLOBAL	KOLIBA_ReadM34tFromOpenFile, KOLIBA_ReadM34tFromNamedFile

KOLIBA_ReadM34tFromNamedFile:

	; On Entry:
	;
	;	RCX = address of KOLIBA_MATRIX to read to
	;	RDX = file name to read from.

	push	rbx
	sub	rsp, 6*8

	sub	eax, eax
	mov	rbx, rcx
	jrcxz	.done
	mov	rcx, rdx
	lea	rdx, [rsp+40]
	jrcxz	.done
	mov	dword [rdx], 'rb'
	call	fopen

	test	rax, rax
	mov	rcx, rbx
	mov	rdx, rax
	je	.done
	mov	rbx, rdx
	call	KOLIBA_ReadM34tFromOpenFile

	mov	rcx, rbx
	mov	rbx, rax
	call	fclose

	mov	rax, rbx

.done:

	add	rsp, 6*8
	pop	rbx
	ret

align 16, int3

KOLIBA_ReadM34tFromOpenFile:

	; On Entry:
	;
	;	RCX = address of output KOLIBA_MATRIX
	;	RDX = handle of FILE to read from
	;
	; On Exit:
	;
	;	RAX = KOLIBA_MATRIX on success, NULL on failure

%define	STACKBYTES	(8*(10+4+12))

	push	rdi
	push	rsi
	sub	rsp, STACKBYTES

	mov	rdi, rcx
	sub	eax, eax

	test	rdx, rdx
	jrcxz	.done

	mov	ecx, 10
	lea	r8, [rsp+STACKBYTES-(8*12)]
	lea	r9, [rsp+STACKBYTES-(8*11)]
	jne	.loop

.rst:

	mov	rcx, rdi
	call	KOLIBA_ResetMatrix
	sub	eax, eax
	jmp	.done

.loop:

	lea	rax, [rsp+STACKBYTES-(8*10)+8*(rcx-1)]
	mov	[rsp+32+8*(rcx-1)], rax
	loop	.loop

	mov	rcx, rdx
	lea	rdx, [KOLIBA_ScanM34tFormat]
	call	fscanf
	cmp	eax, 12
	mov	ecx, eax
	mov	rax, rdi
	lea	rsi, [rsp+STACKBYTES-(8*12)]
	jne	.rst

rep	movsq

.done:

	add	rsp, STACKBYTES
	pop	rsi
	pop	rdi
	ret

section .drectve	info

	db	'-export:KOLIBA_ReadM34tFromOpenFile '
	db	'-export:KOLIBA_ReadM34tFromNamedFile '

