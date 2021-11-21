/*

	slt2vert.c

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

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

// Load a KOLIBA_VERTICES structure from a
// KOLIBA_SLUT structure.
KLBDC KOLIBA_VERTICES *KOLIBA_SlutToVertices(KOLIBA_VERTICES *v, KOLIBA_SLUT * const s) {
	if (v) {
		KOLIBA_SLUT *sLut = (s) ? (KOLIBA_SLUT *)s : (KOLIBA_SLUT *)&KOLIBA_IdentitySlut;

		v->black   = &sLut->Black;
		v->blue    = &sLut->Blue;
		v->green   = &sLut->Green;
		v->cyan    = &sLut->Cyan;
		v->red     = &sLut->Red;
		v->magenta = &sLut->Magenta;
		v->yellow  = &sLut->Yellow;
		v->white   = &sLut->White;
	}

	return v;
}
