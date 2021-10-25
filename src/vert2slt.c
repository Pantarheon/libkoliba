/*

	vert2slt.c

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

// Copy a KOLIBA_VERTICES structure into a
// KOLIBA_SLUT structure. If some or all
// vertices are null, copy defaults to the
// corresponding fields of the SLUT.
KLBDC KOLIBA_SLUT *KOLIBA_VerticesToSlut(KOLIBA_SLUT *sLut, KOLIBA_VERTICES * const v) {
	if (sLut != NULL) {
		if (v == NULL)
			memcpy(sLut, &KOLIBA_IdentitySlut, sizeof(KOLIBA_SLUT));
		else {
			memcpy(&sLut->black,   (v->black   != NULL) ? v->black   : &KOLIBA_IdentitySlut.black, sizeof(KOLIBA_VERTEX));
			memcpy(&sLut->blue,    (v->blue    != NULL) ? v->blue    : &KOLIBA_IdentitySlut.blue, sizeof(KOLIBA_VERTEX));
			memcpy(&sLut->green,   (v->green   != NULL) ? v->green   : &KOLIBA_IdentitySlut.green, sizeof(KOLIBA_VERTEX));
			memcpy(&sLut->cyan,    (v->cyan    != NULL) ? v->cyan    : &KOLIBA_IdentitySlut.cyan, sizeof(KOLIBA_VERTEX));
			memcpy(&sLut->red,     (v->red     != NULL) ? v->red     : &KOLIBA_IdentitySlut.red, sizeof(KOLIBA_VERTEX));
			memcpy(&sLut->magenta, (v->magenta != NULL) ? v->magenta : &KOLIBA_IdentitySlut.magenta, sizeof(KOLIBA_VERTEX));
			memcpy(&sLut->yellow,  (v->yellow  != NULL) ? v->yellow  : &KOLIBA_IdentitySlut.yellow, sizeof(KOLIBA_VERTEX));
			memcpy(&sLut->white,   (v->white   != NULL) ? v->white   : &KOLIBA_IdentitySlut.white, sizeof(KOLIBA_VERTEX));
		}
	}

	return sLut;
}

