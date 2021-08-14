;;	readchrt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 readchrt.asm

section .text

default rel

EXTERN	KOLIBA_ScanChrtFormat, KOLIBA_ResetChromat
EXTERN	KOLIBA_ReadDoublesFromOpenFile, fopen, fclose

GLOBAL	KOLIBA_ReadChrtFromOpenFile, KOLIBA_ReadChrtFromNamedFile

KOLIBA_ReadChrtFromOpenFile:

	; On Entry:
	;
	;	RCX = address of output KOLIBA_CHROMAT
	;	RDX = handle of FILE to read from
	;
	; On Exit:
	;
	;	RAX = KOLIBA_CHROMAT on success, NULL on failure

	mov	r8d, 8
	lea	r9, [KOLIBA_ScanChrtFormat]
	lea	r10, [KOLIBA_ResetChromat]
	jmp	KOLIBA_ReadDoublesFromOpenFile

align 16, int3

KOLIBA_ReadChrtFromNamedFile:

	; On Entry:
	;
	;	RCX = address of KOLIBA_CHROMAT to read to
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
	call	KOLIBA_ReadChrtFromOpenFile

	mov	rcx, rbx
	mov	rbx, rax
	call	fclose

	mov	rax, rbx

.done:

	add	rsp, 6*8
	pop	rbx
	ret

section .drectve	info

	db	'-export:KOLIBA_ReadChrtFromOpenFile '
	db	'-export:KOLIBA_ReadChrtFromNamedFile '

