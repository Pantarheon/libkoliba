/*

	readchrt.c

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

static KOLIBA_CHROMAT * invalid(KOLIBA_CHROMAT *chrm) {
	KOLIBA_ResetChromat(chrm);
	return NULL;
}

// Read a KOLIBA_CHROMAT from an open .chrt file. It may be open
// for reading binary or text data. It remains open upon return,
// so the caller needs to close it. Returns chrm on success, NULL
// on failure. If, however, chrm is not NULL, its contents
// will be reset on failure.

KLBDC KOLIBA_CHROMAT * KOLIBA_ReadChrtFromOpenFile(KOLIBA_CHROMAT *chrm, FILE *f) {
	KOLIBA_CHROMAT chrt;

	if (chrm == NULL) return NULL;
	if (f == NULL) return invalid(chrm);

	return (fscanf(
		f,
		KOLIBA_ScanChrtFormat,
		&chrt.model.r,
		&chrt.model.g,
		&chrt.model.b,
		&chrt.chroma.angle,
		&chrt.chroma.magnitude,
		&chrt.chroma.saturation,
		&chrt.chroma.black,
		&chrt.chroma.white
	) == (sizeof(KOLIBA_CHROMAT) / sizeof(double))) ? memcpy(chrm, &chrt, sizeof(KOLIBA_CHROMAT)) : invalid(chrm);
}

// Read a chrt from a named .chrt file. Returns chrt on success,
// NULL on failure. If, however, chrt is not NULL, its
// contents will be filled with the identity chrt on failure.

KLBDC KOLIBA_CHROMAT * KOLIBA_ReadChrtFromNamedFile(KOLIBA_CHROMAT *chrt, char *fname) {
	FILE *f;
	KOLIBA_CHROMAT *retval;

	if (fname == NULL) return (chrt == NULL) ? NULL : invalid(chrt);
	retval = KOLIBA_ReadChrtFromOpenFile(chrt, f = fopen(fname, "rb"));
	if (f != NULL) fclose(f);
	return retval;
}
