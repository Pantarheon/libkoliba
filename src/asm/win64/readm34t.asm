;;	readm34t.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 readm34t.asm

section .text

default rel

EXTERN	KOLIBA_ScanM34tFormat, KOLIBA_ResetMatrix
EXTERN	KOLIBA_ReadDoublesFromOpenFile, fopen, fclose

GLOBAL	KOLIBA_ReadM34tFromOpenFile, KOLIBA_ReadM34tFromNamedFile

KOLIBA_ReadM34tFromOpenFile:

	; On Entry:
	;
	;	RCX = address of output KOLIBA_MATRIX
	;	RDX = handle of FILE to read from
	;
	; On Exit:
	;
	;	RAX = KOLIBA_MATRIX on success, NULL on failure

	mov	r8d, 12
	lea	r9, [KOLIBA_ScanM34tFormat]
	lea	r10, [KOLIBA_ResetMatrix]
	jmp	KOLIBA_ReadDoublesFromOpenFile

align 16, int3

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

section .drectve	info

	db	'-export:KOLIBA_ReadM34tFromOpenFile '
	db	'-export:KOLIBA_ReadM34tFromNamedFile '

