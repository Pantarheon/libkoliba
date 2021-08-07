;;	writesltt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 writesltt.asm

section .text

default rel

EXTERN	KOLIBA_PrintSlttFormat, fprintf, fopen, fclose

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
	;	RAX = 0 on success, non-0 on failure

%define	STACKBYTES	(8*(22+5))

	push	rdi
	push	rsi
	sub	rsp, STACKBYTES

	lea	rsi, [rcx+16]
	sub	eax, eax
	lea	rdi, [rsp+32]

	mov	al, 1
	test	rdx, rdx
	mov	r8, rcx
	jrcxz	.done
	mov	ecx, 22
	je	.done
	movsd	xmm2, [r8]
	movsd	xmm3, [r8+8]

rep	movsq

	mov	rcx, rdx
	lea	rdx, [KOLIBA_PrintSlttFormat]
	movq	r8, xmm2
	movq	r9, xmm3
	call	fprintf
	sub	eax, 413

.done:

	add	rsp, STACKBYTES
	pop	rsi
	pop	rdi
	ret

section .drectve	info

	db	'-export:KOLIBA_WriteSlttToOpenFile '
	db	'-export:KOLIBA_WriteSlttToNamedFile '

