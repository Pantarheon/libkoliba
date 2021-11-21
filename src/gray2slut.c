/*

	gray2slut.c

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

// Convert grayscale factors to a sLut. If the factors are NULL,
// use Rec. 2020 instead. If the factors add up to 0, set them to 1/3.

KLBDC KOLIBA_SLUT * KOLIBA_ConvertGrayToSlut(KOLIBA_SLUT * sLut, const KOLIBA_RGB * const gray) {
	KOLIBA_RGB rec;
	double d;

	if (sLut != NULL) {
		if ((gray == NULL) || (gray == &KOLIBA_Rec2020))
			memcpy(sLut, &KOLIBA_Rec2020Slut, sizeof(KOLIBA_SLUT));
		else {
			if ((d = gray->r + gray->g + gray->b) == 0.0) {
				rec.r = 1.0 / 3.0;
				rec.g = 1.0 / 3.0;
			}
			else {
				rec.r = gray->r / d;
				rec.g = gray->g / d;
			}

			rec.b = 1.0 - (rec.r + rec.g);

			sLut->Black.r   = 0.0;
			sLut->Black.g   = 0.0;
			sLut->Black.b   = 0.0;

			sLut->Blue.r    = rec.b;
			sLut->Blue.g    = rec.b;
			sLut->Blue.b    = rec.b;

			sLut->Green.r   = rec.g;
			sLut->Green.g   = rec.g;
			sLut->Green.b   = rec.g;

			d               = rec.b + rec.g;
			sLut->Cyan.r    = d;
			sLut->Cyan.g    = d;
			sLut->Cyan.b    = d;

			sLut->Red.r     = rec.r;
			sLut->Red.g     = rec.r;
			sLut->Red.b     = rec.r;

			d               = rec.r + rec.b;
			sLut->Magenta.r = d;
			sLut->Magenta.g = d;
			sLut->Magenta.b = d;

			d               = rec.r + rec.g;
			sLut->Yellow.r  = d;
			sLut->Yellow.g  = d;
			sLut->Yellow.b  = d;

			sLut->White.r   = 1.0;
			sLut->White.g   = 1.0;
			sLut->White.b   = 1.0;
		}
	}

	return sLut;
}
