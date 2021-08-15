;;	writesltt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 writesltt.asm

section .text

default rel

EXTERN	KOLIBA_PrintSlttFormat, fopen, fclose
EXTERN	KOLIBA_WriteDoublesToOpenFile

GLOBAL	KOLIBA_WriteSlttToOpenFile, KOLIBA_WriteSlttToNamedFile

KOLIBA_WriteSlttToNamedFile:

	; On Entry:
	;
	;	RCX = address of SLUT to convert and save
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
	call	KOLIBA_WriteSlttToOpenFile

	mov	rcx, rbx
	mov	rbx, rax
	call	fclose

	mov	rax, rbx

.done:

	add	rsp, 6*8
	pop	rbx
	ret

align 16, int3

KOLIBA_WriteSlttToOpenFile:

	; On Entry:
	;
	;	RCX = address of input SLUT, constant
	;	RDX = handle of FILE to write to
	;
	; On Exit:
	;
	;	EAX = 0 on success, non-0 on failure

	mov	r8d, 24
	lea	r9, [KOLIBA_PrintSlttFormat]
	jmp	KOLIBA_WriteDoublesToOpenFile

section .drectve	info

	db	'-export:KOLIBA_WriteSlttToOpenFile '
	db	'-export:KOLIBA_WriteSlttToNamedFile '

