/*

	sltfactors.c

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

// Precalculate sLut factors, store them in KOLIBA_FLUT.
// Replace any missing vertices by default values.

KLBDC KOLIBA_FLUT * KOLIBA_ConvertSlutToFlut(KOLIBA_FLUT *f, const KOLIBA_VERTICES * const v) {
	KOLIBA_FLUT sf;
	KOLIBA_VERTICES s;

	if (f == NULL) return NULL;

	if (v == NULL) {
		s.black   = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Black);
		s.blue    = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Blue);
		s.green   = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Green);
		s.cyan    = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Cyan);
		s.red     = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Red);
		s.magenta = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Magenta);
		s.yellow  = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Yellow);
		s.white   = (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.White);
	}
	else {
		s.black   = (v->black   != NULL) ? v->black   : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Black);
		s.blue    = (v->blue    != NULL) ? v->blue    : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Blue);
		s.green   = (v->green   != NULL) ? v->green   : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Green);
		s.cyan    = (v->cyan    != NULL) ? v->cyan    : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Cyan);
		s.red     = (v->red     != NULL) ? v->red     : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Red);
		s.magenta = (v->magenta != NULL) ? v->magenta : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Magenta);
		s.yellow  = (v->yellow  != NULL) ? v->yellow  : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.Yellow);
		s.white   = (v->white   != NULL) ? v->white   : (KOLIBA_VERTEX *)&(KOLIBA_IdentitySlut.White);
	}

	sf.Black.r		= s.black->r;
	sf.Black.g		= s.black->g;
	sf.Black.b		= s.black->b;
	sf.Red.r		= s.red->r - s.black->r;
	sf.Red.g		= s.red->g - s.black->g;
	sf.Red.b		= s.red->b - s.black->b;
	sf.Green.r		= s.green->r - s.black->r;
	sf.Green.g		= s.green->g - s.black->g;
	sf.Green.b		= s.green->b - s.black->b;
	sf.Blue.r		= s.blue->r - s.black->r;
	sf.Blue.g		= s.blue->g - s.black->g;
	sf.Blue.b		= s.blue->b - s.black->b;
	sf.Yellow.r		= s.black->r + s.yellow->r - s.green->r - s.red->r;
	sf.Yellow.g		= s.black->g + s.yellow->g - s.green->g - s.red->g;
	sf.Yellow.b		= s.black->b + s.yellow->b - s.green->b - s.red->b;
	sf.Magenta.r	= s.black->r + s.magenta->r - s.blue->r - s.red->r;
	sf.Magenta.g	= s.black->g + s.magenta->g - s.blue->g - s.red->g;
	sf.Magenta.b	= s.black->b + s.magenta->b - s.blue->b - s.red->b;
	sf.Cyan.r		= s.black->r + s.cyan->r - s.blue->r - s.green->r;
	sf.Cyan.g		= s.black->g + s.cyan->g - s.blue->g - s.green->g;
	sf.Cyan.b		= s.black->b + s.cyan->b - s.blue->b - s.green->b;
	sf.White.r		= s.blue->r + s.green->r + s.red->r + s.white->r - s.black->r - s.cyan->r - s.magenta->r - s.yellow->r;
	sf.White.g		= s.blue->g + s.green->g + s.red->g + s.white->g - s.black->g - s.cyan->g - s.magenta->g - s.yellow->g;
	sf.White.b		= s.blue->b + s.green->b + s.red->b + s.white->b - s.black->b - s.cyan->b - s.magenta->b - s.yellow->b;

	return memcpy(f, KOLIBA_FixFlut(&sf), sizeof(KOLIBA_FLUT));
}



