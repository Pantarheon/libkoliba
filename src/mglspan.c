/*

	mglspan.c

	Copyright 2021 G. Adam Stanislav
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

// Create a matrix to control top and bottom values,
// roughly corresponding to gain and lift.

KLBDC KOLIBA_MATRIX * KOLIBA_MatrixSpan(KOLIBA_MATRIX *mat, KOLIBA_RGB *top, KOLIBA_RGB *bottom) {
	KOLIBA_RGB a, b;

	if (mat == NULL) return NULL;

	if (top == NULL) {
		a.r = 1.0;
		a.g = 1.0;
		a.b = 1.0;
	}
	else memcpy(&a, top, sizeof(KOLIBA_RGB));

	if (bottom == NULL) {
		b.r = 0.0;
		b.g = 0.0;
		b.b = 0.0;
	}
	else memcpy(&b, bottom, sizeof(KOLIBA_RGB));

	memset(mat, 0, sizeof(KOLIBA_MATRIX));
	mat->Red.r   = a.r - b.r;
	mat->Red.o   = b.r;

	mat->Green.g = a.g - b.g;
	mat->Green.o = b.g;

	mat->Blue.b  = a.b - b.b;
	mat->Blue.o  = b.b;

	return mat;
}

