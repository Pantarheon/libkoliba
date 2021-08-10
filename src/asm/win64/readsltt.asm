;;	readsltt.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -f win64 readsltt.asm

section .text

default rel

EXTERN	KOLIBA_ScanSlttFormat, fscanf, fopen, fclose, KOLIBA_IdentitySlut

GLOBAL	KOLIBA_ReadSlttFromOpenFile, KOLIBA_ReadSlttFromNamedFile

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

align 16, int3

KOLIBA_ReadSlttFromOpenFile:

	; On Entry:
	;
	;	RCX = address of output SLUT
	;	RDX = handle of FILE to read from
	;
	; On Exit:
	;
	;	RAX = 0 on success, non-0 on failure

%define	STACKBYTES	(8*(22+4+24))

	push	rdi
	push	rsi
	sub	rsp, STACKBYTES

	mov	rdi, rcx
	sub	eax, eax

	test	rdx, rdx
	jrcxz	.done
	lea	rsi, [KOLIBA_IdentitySlut]
	je	.copy

	mov	ecx, 22
	lea	r8, [rsp+STACKBYTES-(8*24)]
	lea	r9, [rsp+STACKBYTES-(8*23)]

.loop:

	lea	rax, [rsp+STACKBYTES-(8*22)+8*(rcx-1)]
	mov	[rsp+32+8*(rcx-1)], rax
	loop	.loop

	mov	rcx, rdx
	lea	rdx, [KOLIBA_ScanSlttFormat]
	call	fscanf
	sub	ecx, ecx
	cmp	eax, 24
	cmovne	rax, rcx
	jne	.copy
	mov	rax, rdi
	lea	rsi, [rsp+STACKBYTES-(8*24)]

.copy:

	mov	ecx, 24
rep	movsq

.done:

	add	rsp, STACKBYTES
	pop	rsi
	pop	rdi
	ret

section .drectve	info

	db	'-export:KOLIBA_ReadSlttFromOpenFile '
	db	'-export:KOLIBA_ReadSlttFromNamedFile '

