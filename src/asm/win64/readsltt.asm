;;	readsltt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 readsltt.asm

section .text

default rel

EXTERN	KOLIBA_ScanSlttFormat, KOLIBA_ResetSlut
EXTERN	KOLIBA_ReadDoublesFromOpenFile, fopen, fclose

GLOBAL	KOLIBA_ReadSlttFromOpenFile, KOLIBA_ReadSlttFromNamedFile

KOLIBA_ReadSlttFromOpenFile:

	; On Entry:
	;
	;	RCX = address of output SLUT
	;	RDX = handle of FILE to read from
	;
	; On Exit:
	;
	;	RAX = SLUT on success, NULL on failure

	mov	r8d, 24
	lea	r9, [KOLIBA_ScanSlttFormat]
	lea	r10, [KOLIBA_ResetSlut]
	jmp	KOLIBA_ReadDoublesFromOpenFile

align 16, int3

KOLIBA_ReadSlttFromNamedFile:

	; On Entry:
	;
	;	RCX = address of SLUT to read to
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
	call	KOLIBA_ReadSlttFromOpenFile

	mov	rcx, rbx
	mov	rbx, rax
	call	fclose

	mov	rax, rbx

.done:

	add	rsp, 6*8
	pop	rbx
	ret

section .drectve	info

	db	'-export:KOLIBA_ReadSlttFromOpenFile '
	db	'-export:KOLIBA_ReadSlttFromNamedFile '

