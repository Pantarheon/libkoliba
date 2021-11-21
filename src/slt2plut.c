/*

	slt2plut.c

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

// Convert a sLut to a pLut.

KLBDC KOLIBA_PLUT * KOLIBA_ConvertSlutToPlut(KOLIBA_PLUT *plut, const KOLIBA_SLUT * const slut) {
	KOLIBA_PLUT p;

	if ((plut == NULL) || (slut == NULL)) return NULL;

	memcpy(&p.Black,   &slut->Black, sizeof(KOLIBA_VERTEX));
	memcpy(&p.White,   &slut->White, sizeof(KOLIBA_VERTEX));
	memcpy(&p.Red,     &slut->Red, sizeof(KOLIBA_VERTEX));
	memcpy(&p.Green,   &slut->Green, sizeof(KOLIBA_VERTEX));
	memcpy(&p.Blue,    &slut->Blue, sizeof(KOLIBA_VERTEX));
	memcpy(&p.Cyan,    &slut->Cyan, sizeof(KOLIBA_VERTEX));
	memcpy(&p.Magenta, &slut->Magenta, sizeof(KOLIBA_VERTEX));
	memcpy(&p.Yellow,  &slut->Yellow, sizeof(KOLIBA_VERTEX));
	p.divisor = 1.0;
	p.efficacy = 1.0;
	return memcpy(plut, &p, sizeof(KOLIBA_PLUT));
}
