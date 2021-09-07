;;
;;
;;	pal8rgba.asm
;;
;;	Copyright 2021 G. Adam Stanislav
;;	All rights reserved
;;
;;	nasm -fwin64 pal8rgba.asm

section	.text

GLOBAL	KOLIBA_PaletteToRgba8, KOLIBA_PaletteToRgba8Alpha

KOLIBA_PaletteToRgba8:

	; On Entry:
	;
	;	RCX = output pixels
	;	RDX = input  pixels (const)
	;	R8  = palette (const)
	;	R9  = number of input/output pixels
	;
	; On Exit:
	;
	;	RAX = output pixels or NULL

	; It is an error if any of the first three arguments is 0.
	; And there is nothing to do if the fourth one is, but that
	; is not an error. We test for the errors first.

	sub	eax, eax
	test	rdx, rdx
	jrcxz	.done
	je		.done

	test	r8, r8
	mov		r10, rcx	; R10 = output pixels.
	mov		ecx, r9d	; ECX = pixel count.
	je		.done
	jecxz	.finished	; Nothing to do, but not an error.

	jmp		.loop

align 16
.loop:

	; Does this clear the high 32 bits of RAX? After all,
	; there is a movzx rax, ... op code. Either way, we
	; do not need the longer op code because the top 32
	; bits have already been cleared in the first line
	; of this procedure (sub eax, eax). So, no need
	; for the longer op code here (or in the alpha
	; version of this routine).
	movzx 	eax, word [rdx+4*rcx-4]	; AL = red, AH = green
	mov		r9b, [rdx+4*rcx-2]		; R9B = blue
	shr		ah, 3
	shr		r9b, 6
	and		ax, 01CE0h
	or		al, r9b
	or		al, ah
	mov		ah, 0
	mov		eax, [r8+rax*4]		; Palette entry
	mov		[r10+4*rcx-4], eax	; Output pixel

	loop	.loop

.finished:

	mov		rax, r10

.done:

	ret


align 16, int3
KOLIBA_PaletteToRgba8Alpha:

	; Same as above, except we also copy the Alpha byte(s)
	; from the input to the output.

	sub	eax, eax
	test	rdx, rdx
	jrcxz	.done
	je		.done

	test	r8, r8
	mov		r10, rcx	; R10 = output pixels.
	mov		ecx, r9d
	je		.done
	sub		r9d, r9d	; Should not be needed, but better safe.
	jecxz	.finished	; Nothing to do, but not an error.
	mov		r11d, 00FFFFFFh

;	jmp		.loop

align 16
.loop:

	movzx 	eax, word [rdx+4*rcx-4]	; AL = red, AH = green
	movzx	r9d, word [rdx+4*rcx-2]	; R9L = blue, R9H = alpha
	shr		ah, 3
	shr		r9b, 6
	and		ax, 01CE0h
	or		al, r9b
	mov		r9b, 0
	or		al, ah
	mov		ah, 0
	shl		r9d, 16				; Input Alpha
	mov		eax, [r8+rax*4]		; Palette entry
	and		eax, r11d			; Remove Alpha copied from palette ...
	or		eax, r9d			; ... and replace it with input Alpha.
	mov		[r10+4*rcx-4], eax	; Output pixel

	loop	.loop

.finished:

	mov		rax, r10

.done:

	ret

section	.drectve	info

	db	'-export:KOLIBA_PaletteToRgba8 '
	db	'-export:KOLIBA_PaletteToRgba8Alpha '


