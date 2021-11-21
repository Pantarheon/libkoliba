/*

	strutring.c

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

// Apply a ring to a SLUT. Apply strut to the ring color.

KLBDC KOLIBA_SLUT * KOLIBA_ApplyStrutRing(KOLIBA_SLUT *sLut, const KOLIBA_VERTEX * const ring, KOLIBA_Pluts plut, double strut) {
	double r, g, b, c, m, y;

	if ((sLut == NULL) || (ring == NULL)) return NULL;

	switch (plut) {
		case KOLIBA_PlutRed:
			r        = ring->r;
			g        = ring->g;
			b        = ring->b;
			break;
		case KOLIBA_PlutGreen:
			b        = ring->r;
			r        = ring->g;
			g        = ring->b;
			break;
		case KOLIBA_PlutBlue:
			g        = ring->r;
			b        = ring->g;
			r        = ring->b;
			break;
		case KOLIBA_PlutCyan:
			r        = 1.0 - ring->r;
			g        = 1.0 - ring->g;
			b        = 1.0 - ring->b;
			break;
		case KOLIBA_PlutMagenta:
			b        = 1.0 - ring->r;
			r        = 1.0 - ring->g;
			g        = 1.0 - ring->b;
			break;
		case KOLIBA_PlutYellow:
			g        = 1.0 - ring->r;
			b        = 1.0 - ring->g;
			r        = 1.0 - ring->b;
			break;
		default:
			return NULL;
			break;
	}

	c = 1.0 - r;
	m = 1.0 - g;
	y = 1.0 - b;

	memcpy(&sLut->Black, &KOLIBA_IdentitySlut.Black, sizeof(KOLIBA_VERTEX));
	memcpy(&sLut->White, &KOLIBA_IdentitySlut.White, sizeof(KOLIBA_VERTEX));

	sLut->Red.r            = r;
	sLut->Red.g            = g;
	sLut->Red.b            = b;

	sLut->Green.r          = b;
	sLut->Green.g          = r;
	sLut->Green.b          = g;

	sLut->Blue.r           = g;
	sLut->Blue.g           = b;
	sLut->Blue.b           = r;

	sLut->Cyan.r           = c;
	sLut->Cyan.g           = m;
	sLut->Cyan.b           = y;

	sLut->Magenta.r        = y;
	sLut->Magenta.g        = c;
	sLut->Magenta.b        = m;

	sLut->Yellow.r         = m;
	sLut->Yellow.g         = y;
	sLut->Yellow.b         = c;

	if (strut != 1.0) switch (plut) {
		case KOLIBA_PlutRed:
			KOLIBA_Interpolate((double *)&sLut->Red, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.Red, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutGreen:
			KOLIBA_Interpolate((double *)&sLut->Green, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.Green, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutBlue:
			KOLIBA_Interpolate((double *)&sLut->Blue, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.Blue, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutCyan:
			KOLIBA_Interpolate((double *)&sLut->Cyan, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.Cyan, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutMagenta:
			KOLIBA_Interpolate((double *)&sLut->Magenta, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.Magenta, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutYellow:
			KOLIBA_Interpolate((double *)&sLut->Yellow, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.Yellow, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
	}

	return sLut;
}
