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

	memcpy(&sLut->black, &KOLIBA_IdentitySlut.black, sizeof(KOLIBA_VERTEX));
	memcpy(&sLut->white, &KOLIBA_IdentitySlut.white, sizeof(KOLIBA_VERTEX));

	sLut->red.r            = r;
	sLut->red.g            = g;
	sLut->red.b            = b;

	sLut->green.r          = b;
	sLut->green.g          = r;
	sLut->green.b          = g;

	sLut->blue.r           = g;
	sLut->blue.g           = b;
	sLut->blue.b           = r;

	sLut->cyan.r           = c;
	sLut->cyan.g           = m;
	sLut->cyan.b           = y;

	sLut->magenta.r        = y;
	sLut->magenta.g        = c;
	sLut->magenta.b        = m;

	sLut->yellow.r         = m;
	sLut->yellow.g         = y;
	sLut->yellow.b         = c;

	if (strut != 1.0) switch (plut) {
		case KOLIBA_PlutRed:
			KOLIBA_Interpolate((double *)&sLut->red, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.red, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutGreen:
			KOLIBA_Interpolate((double *)&sLut->green, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.green, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutBlue:
			KOLIBA_Interpolate((double *)&sLut->blue, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.blue, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutCyan:
			KOLIBA_Interpolate((double *)&sLut->cyan, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.cyan, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutMagenta:
			KOLIBA_Interpolate((double *)&sLut->magenta, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.magenta, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
		case KOLIBA_PlutYellow:
			KOLIBA_Interpolate((double *)&sLut->yellow, (double *)ring, strut, (double *)&KOLIBA_IdentitySlut.yellow, sizeof(KOLIBA_VERTEX)/sizeof(double));
			break;
	}

	return sLut;
}
