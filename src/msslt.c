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
		mat->Red.r   = sLut->White.r - sLut->Cyan.r;
		mat->Red.g   = sLut->White.r - sLut->Magenta.r;
		mat->Red.b   = sLut->White.r - sLut->Yellow.r;
		mat->Red.o   = sLut->Cyan.r  - mat->Red.g - mat->Red.b;

		mat->Green.r = sLut->White.g - sLut->Cyan.g;
		mat->Green.g = sLut->White.g - sLut->Magenta.g;
		mat->Green.b = sLut->White.g - sLut->Yellow.g;
		mat->Green.o = sLut->Cyan.g  - mat->Green.g - mat->Green.b;

		mat->Blue.r  = sLut->White.b - sLut->Cyan.b;
		mat->Blue.g  = sLut->White.b - sLut->Magenta.b;
		mat->Blue.b  = sLut->White.b - sLut->Yellow.b;
		mat->Blue.o  = sLut->Cyan.b  - mat->Blue.g - mat->Blue.b;
	}
	else {
		mat->Blue.o  = sLut->Black.b;
		mat->Blue.b  = sLut->Blue.b - sLut->Black.b;
		mat->Blue.g  = sLut->Green.b - sLut->Black.b;
		mat->Blue.r  = sLut->Red.b - sLut->Black.b;

		mat->Green.o = sLut->Black.g;
		mat->Green.b = sLut->Blue.g - sLut->Black.g;
		mat->Green.g = sLut->Green.g - sLut->Black.g;
		mat->Green.r = sLut->Red.g - sLut->Black.g;

		mat->Red.o   = sLut->Black.r;
		mat->Red.b   = sLut->Blue.r - sLut->Black.r;
		mat->Red.g   = sLut->Green.r - sLut->Black.r;
		mat->Red.r   = sLut->Red.r - sLut->Black.r;
	}

	return mat;
}
