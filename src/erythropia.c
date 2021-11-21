/*

	erythropia.c

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

// Apply erythropy to a sLut

KLBDC KOLIBA_SLUT * KOLIBA_ApplyErythropy(KOLIBA_SLUT * output, const KOLIBA_SLUT * const input) {
	double r, g, b, c, m, y;

	if ((input == NULL) || (output == NULL)) return NULL;

	r = input->Red.r;
	g = input->Red.g;
	b = input->Red.b;

	if (output != input) {
		KOLIBA_VERTEX v;

		memmove(&v, &input->Black, sizeof(KOLIBA_VERTEX));
		memmove(&output->White, &input->White, sizeof(KOLIBA_VERTEX));
		memmove(&output->Black, &v, sizeof(KOLIBA_VERTEX));
		output->Red.r = r;
		output->Red.g = g;
		output->Red.b = b;
	}

	c = 1.0 - r;
	m = 1.0 - g;
	y = 1.0 - b;

	output->Green.r   = b;
	output->Green.g   = r;
	output->Green.b   = g;

	output->Blue.r    = g;
	output->Blue.g    = b;
	output->Blue.b    = r;

	output->Cyan.r    = c;
	output->Cyan.g    = m;
	output->Cyan.b    = y;
	
	output->Magenta.r = y;
	output->Magenta.g = c;
	output->Magenta.b = m;

	output->Yellow.r  = m;
	output->Yellow.g  = y;
	output->Yellow.b  = c;

	return output;
}
