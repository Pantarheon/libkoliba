/*

	flutms.c

	Copyright 2019-2021 G. Adam Stanislav
	All rights reserved

	Redistribution and use in source and binary forms,
	with or without modification, are permitted provided
	that the following conditions are met:

	1. Redistributions of source code must retain the
	above copyright notice, this list of conditions
	and the following disclaimer.

	2. Redistributions in binary form must reproduce the
	above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or
	other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the
	names of its contributors may be used to endorse or
	promote products derived from this software without
	specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS
	AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
	SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
	OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
	PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "koliba.h"
#include <string.h>

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

KLBHID extern const KOLIBA_SLUT KOLIBA_Zeroes;

KLBDC KOLIBA_FLUT * KOLIBA_ConvertMatrixToFlut(KOLIBA_FLUT * fLut, const KOLIBA_MATRIX * const mat) {
	if ((fLut == NULL) || (mat == NULL)) return NULL;

	memcpy	(fLut, &KOLIBA_Zeroes, sizeof(KOLIBA_FLUT));
	fLut->Black.r = mat->red.o;
	fLut->Black.g = mat->green.o;
	fLut->Black.b = mat->blue.o;
	fLut->Red.r   = mat->red.r;
	fLut->Red.g   = mat->green.r;
	fLut->Red.b   = mat->blue.r;
	fLut->Green.r = mat->red.g;
	fLut->Green.g = mat->green.g;
	fLut->Green.b = mat->blue.g;
	fLut->Blue.r  = mat->red.b;
	fLut->Blue.g  = mat->green.b;
	fLut->Blue.b  = mat->blue.b;

	return fLut;
}
