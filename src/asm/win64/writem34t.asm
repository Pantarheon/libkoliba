;;	writem34t.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 writem34t.asm

section .text

default rel

EXTERN	KOLIBA_PrintM34tFormat, fopen, fclose
EXTERN	KOLIBA_WriteDoublesToOpenFile

GLOBAL	KOLIBA_WriteM34tToOpenFile, KOLIBA_WriteM34tToNamedFile

KOLIBA_WriteM34tToNamedFile:

	; On Entry:
	;
	;	RCX = address of KOLIBA_MATRIX to convert and save
	;	RDX = file name to save to.

	push	rbx
	sub	rsp, 6*8

	mov	eax, -1
	mov	rbx, rcx
	jrcxz	.done
	mov	rcx, rdx
	lea	rdx, [rsp+40]
	jrcxz	.done
	mov	dword [rdx], 'wb'
	call	fopen

	test	rax, rax
	mov	rcx, rbx
	mov	rdx, rax
	mov	eax, -1
	je	.done
	mov	rbx, rdx
	call	KOLIBA_WriteM34tToOpenFile

	mov	rcx, rbx
	mov	rbx, rax
	call	fclose

	mov	rax, rbx

.done:

	add	rsp, 6*8
	pop	rbx
	ret

align 16, int3

KOLIBA_WriteM34tToOpenFile:

	; On Entry:
	;
	;	RCX = address of input KOLIBA_MATRIX, constant
	;	RDX = handle of FILE to write to
	;
	; On Exit:
	;
	;	EAX = 0 on success, non-0 on failure

	mov	r8d, 12
	lea	r9, [KOLIBA_PrintM34tFormat]
	jmp	KOLIBA_WriteDoublesToOpenFile

section .drectve	info

	db	'-export:KOLIBA_WriteM34tToOpenFile '
	db	'-export:KOLIBA_WriteM34tToNamedFile '

