/*

	readsltt.c

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

static KOLIBA_SLUT * invalid(KOLIBA_SLUT *sLut) {
	memcpy(sLut, &KOLIBA_IdentitySlut, sizeof(KOLIBA_SLUT));
	return NULL;
}

// Read a SLUT from an open .sltt file. It may to be open
// for reading binary or text data. It remains open upon return,
// so the caller needs to close it. Returns sLut on success, NULL
// on failure. If, however, sLut is not NULL, its contents
// will be filled with the identity sLut on failure.

KLBDC KOLIBA_SLUT * KOLIBA_ReadSlttFromOpenFile(KOLIBA_SLUT *sLut, FILE *f) {
	KOLIBA_SLUT Lut;

	if (sLut == NULL) return NULL;
	if (f == NULL) return invalid(sLut);

	return (fscanf(
		f,
		sfmt,
		&Lut.black.r,
		&Lut.black.g,
		&Lut.black.b,
		&Lut.blue.r,
		&Lut.blue.g,
		&Lut.blue.b,
		&Lut.green.r,
		&Lut.green.g,
		&Lut.green.b,
		&Lut.cyan.r,
		&Lut.cyan.g,
		&Lut.cyan.b,
		&Lut.red.r,
		&Lut.red.g,
		&Lut.red.b,
		&Lut.magenta.r,
		&Lut.magenta.g,
		&Lut.magenta.b,
		&Lut.yellow.r,
		&Lut.yellow.g,
		&Lut.yellow.b,
		&Lut.white.r,
		&Lut.white.g,
		&Lut.white.b
	) != 24) ? memcpy(sLut, &Lut, sizeof(KOLIBA_SLUT)) : invalid(sLut);
}

// Read a Lut from a named .sltt file. Returns Lut on success,
// NULL on failure. If, however, Lut is not NULL, its
// contents will be filled with the identity Lut on failure.

KLBDC KOLIBA_SLUT * KOLIBA_ReadSlttFromNamedFile(KOLIBA_SLUT *Lut, char *fname) {
	FILE *f;
	KOLIBA_SLUT *retval;

	if (fname == NULL) return (Lut == NULL) ? NULL : invalid(Lut);
	retval = KOLIBA_ReadSlttFromOpenFile(Lut, f = fopen(fname, "rb"));
	if (f != NULL) fclose(f);
	return retval;
}
