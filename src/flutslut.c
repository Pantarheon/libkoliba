/*

	flutslut.c

	Copyright 2019 G. Adam Stanislav
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

// Convert fLut factors, to KOLIBA_SLUT.

KLBDC KOLIBA_SLUT * KOLIBA_ConvertFlutToSlut(KOLIBA_SLUT *sLut, const KOLIBA_FLUT * const f) {
	KOLIBA_SLUT sl;

	if ((f == NULL) || (sLut == NULL)) return NULL;

	sl.Black.r		= f->Black.r;
	sl.Black.g		= f->Black.g;
	sl.Black.b		= f->Black.b;

	sl.Blue.r		= f->Black.r  + f->Blue.r;
	sl.Blue.g		= f->Black.g  + f->Blue.g;
	sl.Blue.b		= f->Black.b  + f->Blue.b;

	sl.Green.r		= f->Black.r  + f->Green.r;
	sl.Green.g		= f->Black.g  + f->Green.g;
	sl.Green.b		= f->Black.b  + f->Green.b;

	sl.Cyan.r		= sl.Green.r  + f->Blue.r  + f->Cyan.r;
	sl.Cyan.g		= sl.Green.g  + f->Blue.g  + f->Cyan.g;
	sl.Cyan.b		= sl.Green.b  + f->Blue.b  + f->Cyan.b;

	sl.Red.r		= f->Black.r  + f->Red.r;
	sl.Red.g		= f->Black.g  + f->Red.g;
	sl.Red.b		= f->Black.b  + f->Red.b;

	sl.Magenta.r	= sl.Red.r    + f->Blue.r  + f->Magenta.r;
	sl.Magenta.g	= sl.Red.g    + f->Blue.g  + f->Magenta.g;
	sl.Magenta.b	= sl.Red.b    + f->Blue.b  + f->Magenta.b;

	sl.Yellow.r		= sl.Red.r    + f->Green.r + f->Yellow.r;
	sl.Yellow.g		= sl.Red.g    + f->Green.g + f->Yellow.g;
	sl.Yellow.b		= sl.Red.b    + f->Green.b + f->Yellow.b;

	sl.White.r		= sl.Yellow.r + f->Blue.r  + f->Cyan.r + f->Magenta.r + f->White.r;
	sl.White.g		= sl.Yellow.g + f->Blue.g  + f->Cyan.g + f->Magenta.g + f->White.g;
	sl.White.b		= sl.Yellow.b + f->Blue.b  + f->Cyan.b + f->Magenta.b + f->White.b;

	return (KOLIBA_SLUT *)memcpy(sLut, KOLIBA_FixSlut((KOLIBA_SLUT *)&sl), sizeof(KOLIBA_SLUT));
}



