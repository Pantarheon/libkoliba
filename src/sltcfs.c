/*

	sltcfs.c

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


// Convert a color filter to a sLut.

KLBDC KOLIBA_SLUT * KOLIBA_ConvertColorFilterToSlut(KOLIBA_SLUT * sLut, const KOLIBA_CFLT * const cFlt) {
	double r,g,b,d, R, G, B;

	if ((sLut == NULL) || (cFlt == NULL)) return NULL;

	d = cFlt->d;
	r = cFlt->r * d;
	g = cFlt->g * d;
	b = cFlt->b * d;
	d = 1.0 - d;
	R = r + d;
	G = g + d;
	B = b + d;

	sLut->Black.r   = 0.0;
	sLut->Black.g   = 0.0;
	sLut->Black.b   = 0.0;
	sLut->Blue.r    = r;
	sLut->Blue.g    = g;
	sLut->Blue.b    = B;
	sLut->Green.r   = r;
	sLut->Green.g   = G;
	sLut->Green.b   = b;
	sLut->Cyan.r    = r;
	sLut->Cyan.g    = G;
	sLut->Cyan.b    = B;
	sLut->Red.r     = R;
	sLut->Red.g     = g;
	sLut->Red.b     = b;
	sLut->Magenta.r = R;
	sLut->Magenta.g = g;
	sLut->Magenta.b = B;
	sLut->Yellow.r  = R;
	sLut->Yellow.g  = G;
	sLut->Yellow.b  = b;
	sLut->White.r   = 1.0;
	sLut->White.g   = 1.0;
	sLut->White.b   = 1.0;

	return sLut;
}
