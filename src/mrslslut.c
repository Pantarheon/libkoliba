/*

	mrslslut.c

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

#define	USECLIB
#include "koliba.h"
#include <stdio.h>
#include <string.h>

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

static KOLIBA_SLUT * invalid(KOLIBA_SLUT *sLut, KOLIBA_ftype *ft, KOLIBA_ftype err) {
	memcpy(sLut, &KOLIBA_IdentitySlut, sizeof(KOLIBA_SLUT));
	if (ft) *ft = err;
	return NULL;
}

KLBDC KOLIBA_SLUT * KOLIBA_MarshalSlutFromCompatibleString(KOLIBA_SLUT *sLut, const unsigned char * const string, KOLIBA_ftype *ft) {
	KOLIBA_ftype ftype;

	if (sLut == NULL) {
		if (ft) *ft = KOLIBA_ftnoslut;
		return NULL;
	}
	if (string == NULL) return invalid(sLut, ft, KOLIBA_ftnofile);

	switch(ftype = KOLIBA_GetStringDataFormat(string)) {
		case KOLIBA_ftsltt:
			if (KOLIBA_StringToSlut(sLut, string)) {
				if (ft) *ft = ftype;
				return sLut;
			}
			else return invalid(sLut, ft, KOLIBA_ftunknown);
			break;
		default:
			if (ft) *ft = KOLIBA_ftunknown;
			return NULL;
			break;
	}
}
