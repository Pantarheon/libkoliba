/*

	msslt.c

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

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

// This is the inverse of KOLIBA_ConvertMatrixToSlut
// but only if the sLut really is a matrix.
//
// Otherwise, it extracts a matrix based on prime
// farba but ignoring secondary farba, which is not
// an inverse of KOLIBA_ConvertMatrixToSlut, but perhaps
// could be used as a special effect.
//
// Or, if the secondary flag is true, it extracts
// a matrix based on secondary farba but ignoring
// primary farba, which again is not an inverse
// of KOLIBA_ConvertMatrixToSlut unless the sLut
// really is a matrix.

KLBDC KOLIBA_MATRIX * KOLIBA_ConvertSlutToMatrix(KOLIBA_MATRIX * mat, const KOLIBA_SLUT * const sLut, bool secondary) {
	if ((sLut == NULL) || (mat == NULL)) return NULL;

	if (secondary) {
		mat->red.r   = sLut->white.r - sLut->cyan.r;
		mat->red.g   = sLut->white.r - sLut->magenta.r;
		mat->red.b   = sLut->white.r - sLut->yellow.r;
		mat->red.o   = sLut->cyan.r  - mat->red.g - mat->red.b;

		mat->green.r = sLut->white.g - sLut->cyan.g;
		mat->green.g = sLut->white.g - sLut->magenta.g;
		mat->green.b = sLut->white.g - sLut->yellow.g;
		mat->green.o = sLut->cyan.g  - mat->green.g - mat->green.b;

		mat->blue.r  = sLut->white.b - sLut->cyan.b;
		mat->blue.g  = sLut->white.b - sLut->magenta.b;
		mat->blue.b  = sLut->white.b - sLut->yellow.b;
		mat->blue.o  = sLut->cyan.b  - mat->blue.g - mat->blue.b;
	}
	else {
		mat->blue.o  = sLut->black.b;
		mat->blue.b  = sLut->blue.b - sLut->black.b;
		mat->blue.g  = sLut->green.b - sLut->black.b;
		mat->blue.r  = sLut->red.b - sLut->black.b;

		mat->green.o = sLut->black.g;
		mat->green.b = sLut->blue.g - sLut->black.g;
		mat->green.g = sLut->green.g - sLut->black.g;
		mat->green.r = sLut->red.g - sLut->black.g;

		mat->red.o   = sLut->black.r;
		mat->red.b   = sLut->blue.r - sLut->black.r;
		mat->red.g   = sLut->green.r - sLut->black.r;
		mat->red.r   = sLut->red.r - sLut->black.r;
	}

	return mat;
}
