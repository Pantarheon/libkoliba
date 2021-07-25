/*

	readcflt.c

	Copyright 2019 G. Adam Stanislav
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

static KOLIBA_CFLT * invalid(KOLIBA_CFLT *cFlt) {
	memset(cFlt, 0, sizeof(KOLIBA_CFLT));
	return NULL;
}

// Read a Color Filter from an open .cflt file. It needs to be open
// for reading binary data. It remains open upon return, so
// the caller needs to close it. Returns matrix on success, NULL
// on failure. If, however, m3x4 is not NULL, its contents
// will be filled with zeros on failure.

KLBDC KOLIBA_CFLT * KOLIBA_ReadColorFilterFromOpenFile(KOLIBA_CFLT *cFlt, FILE *f) {
	KOLIBA_CFLT2 Flt;
	unsigned char header[SLTCFILEHEADERBYTES];

	if (cFlt == NULL) return NULL;
	if (f == NULL) return invalid(cFlt);

	if (fread(header, 1, SLTCFILEHEADERBYTES, f) != SLTCFILEHEADERBYTES) return invalid(cFlt);
	if (memcmp(header, &KOLIBA_cFltHeader, SLTCFILEHEADERBYTES) != 0) return invalid(cFlt);
	if (fread(&Flt, 1, sizeof(KOLIBA_CFLT2), f) != sizeof(KOLIBA_CFLT2)) return invalid(cFlt);
	KOLIBA_FixDoubles((double *)&Flt, sizeof(KOLIBA_CFLT2) / sizeof(double));
	if (KOLIBA_CheckCflt(&Flt.cFlt, Flt.checksum) == 0) return invalid(cFlt);
	return memcpy(cFlt, &Flt.cFlt, sizeof(KOLIBA_CFLT));
}

// Read a Color Filter from a named file. Returns Color Filter on success,
// NULL on failure. If, however, cFlt is not NULL, its
// contents will be filled with zeros on failure.

KLBDC KOLIBA_CFLT * KOLIBA_ReadColorFilterFromNamedFile(KOLIBA_CFLT *cFlt, char *fname) {
	FILE *f;
	KOLIBA_CFLT *retval;

	if (fname == NULL) return (cFlt == NULL) ? NULL : invalid(cFlt);
	retval = KOLIBA_ReadColorFilterFromOpenFile(cFlt, f = fopen(fname, "rb"));
	if (f != NULL) fclose(f);
	return retval;
}
