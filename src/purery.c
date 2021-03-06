/*

	purery.c

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

// Apply pure erythropy to a FLUT. It is "pure" because the svit is at its
// defaults and has no effect on the result.
KLBDC KOLIBA_FLUT * KOLIBA_ApplyPureErythropy(KOLIBA_FLUT * output, const KOLIBA_VERTEX * const red) {
	double r, g, b, s, q, w;

	if ((red == NULL) || (output == NULL)) return NULL;

	r = red->r;
	g = red->g;
	b = red->b;

	output->Black.r = 0.0;
	output->Black.g = 0.0;
	output->Black.b = 0.0;

	output->Red.r = r;
	output->Red.g = g;
	output->Red.b = b;

	s = r + g + b;

	output->Green.r = b;
	output->Green.g = r;
	output->Green.b = g;

	q = 1.0 - s;

	output->Blue.r = g;
	output->Blue.g = b;
	output->Blue.b = r;

	output->Cyan.r = q;
	output->Cyan.g = q;
	output->Cyan.b = q;
	
	output->Magenta.r = q;
	output->Magenta.g = q;
	output->Magenta.b = q;

	w = 2.0 * (s - 1.0);

	output->Yellow.r = q;
	output->Yellow.g = q;
	output->Yellow.b = q;

	output->White.r = w;
	output->White.g = w;
	output->White.b = w;

	return output;
}
