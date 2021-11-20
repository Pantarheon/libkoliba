/*

	ring.c

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

// Apply a ring to a palette.
// Do not change red and black, or overall efficacy.

KLBDC KOLIBA_PALETTE * KOLIBA_ApplyPaletteRing(KOLIBA_PALETTE *output, const KOLIBA_PALETTE * const input, KOLIBA_Pluts plut) {
	double r, g, b, c, m, y, efficacy;

	if ((output == NULL) || (!KOLIBA_IsPaletteValid(input))) return NULL;

	switch (plut) {
		case KOLIBA_PlutBlack:
			r        = input->black.rp;
			g        = input->black.gp;
			b        = input->black.bp;
			efficacy = input->black.efficacy;
			break;
		case KOLIBA_PlutWhite:
			r        = input->white.rp;
			g        = input->white.gp;
			b        = input->white.bp;
			efficacy = input->white.efficacy;
			break;
		case KOLIBA_PlutRed:
			r        = input->red.rp;
			g        = input->red.gp;
			b        = input->red.bp;
			efficacy = input->red.efficacy;
			break;
		case KOLIBA_PlutGreen:
			b        = input->green.rp;
			r        = input->green.gp;
			g        = input->green.bp;
			efficacy = input->green.efficacy;
			break;
		case KOLIBA_PlutBlue:
			g        = input->blue.rp;
			b        = input->blue.gp;
			r        = input->blue.bp;
			efficacy = input->blue.efficacy;
			break;
		case KOLIBA_PlutCyan:
			r        = 1.0 - input->cyan.rp;
			g        = 1.0 - input->cyan.gp;
			b        = 1.0 - input->cyan.bp;
			efficacy = input->cyan.efficacy;
			break;
		case KOLIBA_PlutMagenta:
			b        = 1.0 - input->magenta.rp;
			r        = 1.0 - input->magenta.gp;
			g        = 1.0 - input->magenta.bp;
			efficacy = input->magenta.efficacy;
			break;
		case KOLIBA_PlutYellow:
			g        = 1.0 - input->yellow.rp;
			b        = 1.0 - input->yellow.gp;
			r        = 1.0 - input->yellow.bp;
			efficacy = input->yellow.efficacy;
			break;
		default:
			return NULL;
			break;
	}

	c = 1.0 - r;
	m = 1.0 - g;
	y = 1.0 - b;

	if (output != input) memcpy(output, input, sizeof(KOLIBA_PALETTE));

	output->red.rp            = r;
	output->red.gp            = g;
	output->red.bp            = b;
	output->red.efficacy     = efficacy;

	output->green.rp          = b;
	output->green.gp          = r;
	output->green.bp          = g;
	output->green.efficacy   = efficacy;

	output->blue.rp           = g;
	output->blue.gp           = b;
	output->blue.bp           = r;
	output->blue.efficacy    = efficacy;

	output->cyan.rp           = c;
	output->cyan.gp           = m;
	output->cyan.bp           = y;
	output->cyan.efficacy    = efficacy;

	output->magenta.rp        = y;
	output->magenta.gp        = c;
	output->magenta.bp        = m;
	output->magenta.efficacy = efficacy;

	output->yellow.rp         = m;
	output->yellow.gp         = y;
	output->yellow.bp         = c;
	output->yellow.efficacy  = efficacy;

	output->erythropy        = 0;

	return output;
}
