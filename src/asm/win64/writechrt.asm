;;	writechrt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 writechrt.asm

section .text

default rel

EXTERN	KOLIBA_PrintChrtFormat, fopen, fclose
EXTERN	KOLIBA_WriteDoublesToOpenFile

GLOBAL	KOLIBA_WriteChrtToOpenFile, KOLIBA_WriteChrtToNamedFile

KOLIBA_WriteChrtToNamedFile:

	; On Entry:
	;
	;	RCX = address of KOLIBA_CHROMAT to convert and save
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
	call	KOLIBA_WriteChrtToOpenFile

	mov	rcx, rbx
	mov	rbx, rax
	call	fclose

	mov	rax, rbx

.done:

	add	rsp, 6*8
	pop	rbx
	ret

align 16, int3

KOLIBA_WriteChrtToOpenFile:

	; On Entry:
	;
	;	RCX = address of input KOLIBA_CHROMAT, constant
	;	RDX = handle of FILE to write to
	;
	; On Exit:
	;
	;	EAX = 0 on success, non-0 on failure

	mov	r8d, 8
	lea	r9, [KOLIBA_PrintChrtFormat]
	jmp	KOLIBA_WriteDoublesToOpenFile

section .drectve	info

	db	'-export:KOLIBA_WriteChrtToOpenFile '
	db	'-export:KOLIBA_WriteChrtToNamedFile '

