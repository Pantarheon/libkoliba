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
			r        = input->Black.rp;
			g        = input->Black.gp;
			b        = input->Black.bp;
			efficacy = input->Black.efficacy;
			break;
		case KOLIBA_PlutWhite:
			r        = input->White.rp;
			g        = input->White.gp;
			b        = input->White.bp;
			efficacy = input->White.efficacy;
			break;
		case KOLIBA_PlutRed:
			r        = input->Red.rp;
			g        = input->Red.gp;
			b        = input->Red.bp;
			efficacy = input->Red.efficacy;
			break;
		case KOLIBA_PlutGreen:
			b        = input->Green.rp;
			r        = input->Green.gp;
			g        = input->Green.bp;
			efficacy = input->Green.efficacy;
			break;
		case KOLIBA_PlutBlue:
			g        = input->Blue.rp;
			b        = input->Blue.gp;
			r        = input->Blue.bp;
			efficacy = input->Blue.efficacy;
			break;
		case KOLIBA_PlutCyan:
			r        = 1.0 - input->Cyan.rp;
			g        = 1.0 - input->Cyan.gp;
			b        = 1.0 - input->Cyan.bp;
			efficacy = input->Cyan.efficacy;
			break;
		case KOLIBA_PlutMagenta:
			b        = 1.0 - input->Magenta.rp;
			r        = 1.0 - input->Magenta.gp;
			g        = 1.0 - input->Magenta.bp;
			efficacy = input->Magenta.efficacy;
			break;
		case KOLIBA_PlutYellow:
			g        = 1.0 - input->Yellow.rp;
			b        = 1.0 - input->Yellow.gp;
			r        = 1.0 - input->Yellow.bp;
			efficacy = input->Yellow.efficacy;
			break;
		default:
			return NULL;
			break;
	}

	c = 1.0 - r;
	m = 1.0 - g;
	y = 1.0 - b;

	if (output != input) memcpy(output, input, sizeof(KOLIBA_PALETTE));

	output->Red.rp            = r;
	output->Red.gp            = g;
	output->Red.bp            = b;
	output->Red.efficacy     = efficacy;

	output->Green.rp          = b;
	output->Green.gp          = r;
	output->Green.bp          = g;
	output->Green.efficacy   = efficacy;

	output->Blue.rp           = g;
	output->Blue.gp           = b;
	output->Blue.bp           = r;
	output->Blue.efficacy    = efficacy;

	output->Cyan.rp           = c;
	output->Cyan.gp           = m;
	output->Cyan.bp           = y;
	output->Cyan.efficacy    = efficacy;

	output->Magenta.rp        = y;
	output->Magenta.gp        = c;
	output->Magenta.bp        = m;
	output->Magenta.efficacy = efficacy;

	output->Yellow.rp         = m;
	output->Yellow.gp         = y;
	output->Yellow.bp         = c;
	output->Yellow.efficacy  = efficacy;

	output->erythropy        = false;

	return output;
}
