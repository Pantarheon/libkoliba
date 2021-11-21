/*

	farbsity.c

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

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

// Set the farbosity of a sLut without changing its svit.
// It is defined by its center and its width and is applied
// to all six farba vertices.
//
// Default center is 0.5, default width is 1.0.
KLBDC KOLIBA_SLUT * KOLIBA_SetFarbosity(KOLIBA_SLUT *sLut, double center, double width) {
	double l, h, m, v;

	if (sLut != NULL) {
		l = center - width / 2.0;
		h = l + width;
		v = 1.0 - l;
		m = 1.0 - h;

		sLut->Blue.r    = l;
		sLut->Blue.g    = l;
		sLut->Blue.b    = h;

		sLut->Green.r   = l;
		sLut->Green.g   = h;
		sLut->Green.b   = l;

		sLut->Cyan.r    = m;
		sLut->Cyan.g    = v;
		sLut->Cyan.b    = v;

		sLut->Red.r     = h;
		sLut->Red.g     = l;
		sLut->Red.b     = l;

		sLut->Magenta.r = v;
		sLut->Magenta.g = m;
		sLut->Magenta.b = v;

		sLut->Yellow.r  = v;
		sLut->Yellow.g  = v;
		sLut->Yellow.b  = m;
	}

	return sLut;
}
