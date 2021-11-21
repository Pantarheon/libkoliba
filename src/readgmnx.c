/*

	readgmnx.c

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

static KOLIBA_GEMINIX * invalid(KOLIBA_GEMINIX *gem) {
	memcpy(&gem->p, &KOLIBA_IdentityMatrix, sizeof(KOLIBA_MATRIX));
	memcpy(&gem->s, &KOLIBA_IdentityMatrix, sizeof(KOLIBA_MATRIX));
	return NULL;
}

// Read a GEMINIX from an open .gmnx file. It may to be open
// for reading binary or text data. It remains open upon return,
// so the caller needs to close it. Returns gem on success, NULL
// on failure. If, however, gem is not NULL, its contents
// will be filled with the identity gem on failure.

KLBDC KOLIBA_GEMINIX * KOLIBA_ReadGmnxFromOpenFile(KOLIBA_GEMINIX *geminix, FILE *f) {
	KOLIBA_GEMINIX gem;

	if (geminix == NULL) return NULL;
	if (f == NULL) return invalid(geminix);

	return (fscanf(
		f,
		KOLIBA_ScanGmnxFormat,
		&gem.p.Red.r,
		&gem.p.Red.g,
		&gem.p.Red.b,
		&gem.p.Red.o,
		&gem.p.Green.r,
		&gem.p.Green.g,
		&gem.p.Green.b,
		&gem.p.Green.o,
		&gem.p.Blue.r,
		&gem.p.Blue.g,
		&gem.p.Blue.b,
		&gem.p.Blue.o,
		&gem.s.Red.r,
		&gem.s.Red.g,
		&gem.s.Red.b,
		&gem.s.Red.o,
		&gem.s.Green.r,
		&gem.s.Green.g,
		&gem.s.Green.b,
		&gem.s.Green.o,
		&gem.s.Blue.r,
		&gem.s.Blue.g,
		&gem.s.Blue.b,
		&gem.s.Blue.o
	) == 24) ? memcpy(geminix, &gem, sizeof(KOLIBA_GEMINIX)) : invalid(geminix);
}

// Read a Gemi from a named .gmnx file. Returns Gemi on success,
// NULL on failure. If, however, Gemi is not NULL, its
// contents will be filled with the identity Gemi on failure.

KLBDC KOLIBA_GEMINIX * KOLIBA_ReadGmnxFromNamedFile(KOLIBA_GEMINIX *Gemi, char *fname) {
	FILE *f;
	KOLIBA_GEMINIX *retval;

	if (fname == NULL) return (Gemi == NULL) ? NULL : invalid(Gemi);
	retval = KOLIBA_ReadGmnxFromOpenFile(Gemi, f = fopen(fname, "rb"));
	if (f != NULL) fclose(f);
	return retval;
}
