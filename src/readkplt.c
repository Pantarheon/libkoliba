/*

	readkplt.c

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

static KOLIBA_PALETTE * invalid(KOLIBA_PALETTE *kPlt);

// Read a palette from an open .kPlt file. It needs to be open
// for reading binary data. It remains open upon return, so
// the caller needs to close it. Returns palette on success, NULL
// on failure. If, however, kPlt is not NULL, its contents
// will be filled with the identity palette on failure.

KLBDC KOLIBA_PALETTE * KOLIBA_ReadPaletteFromOpenFile(KOLIBA_PALETTE *kPlt, FILE *f) {
	union {
		KOLIBA_PALETTE p;
		KOLIBA_PALETTE2 p2;
	} plt;
	unsigned char header[SLTCFILEHEADERBYTES];
	bool ery;

	if (kPlt == NULL) return NULL;
	if (f == NULL) return invalid(kPlt);

	if (fread(header, 1, SLTCFILEHEADERBYTES, f) != SLTCFILEHEADERBYTES)
		return invalid(kPlt);
	if (memcmp(header, &KOLIBA_kPltHeader00, SLTCFILEHEADERBYTES) == 0)
		ery = false;
	else if (memcmp(header, &KOLIBA_kPltHeader01, SLTCFILEHEADERBYTES) == 0)
		ery = true;
	else return invalid(kPlt);

	if (fread(&plt.p2, 1, sizeof(KOLIBA_PALETTE2), f) != sizeof(KOLIBA_PALETTE2)) return invalid(kPlt);
	KOLIBA_FixDoubles((double *)&plt.p2, sizeof(KOLIBA_PALETTE2) / sizeof(double));
	if (KOLIBA_CheckKplt(&plt.p2, plt.p2.checksum) == 0) return invalid(kPlt);
	plt.p.erythropy = ery;
	return (KOLIBA_IsPaletteValid(&plt.p)) ?
		memcpy(kPlt, &plt.p, sizeof(KOLIBA_PALETTE)) :
		invalid(kPlt);
}

// Read a palette from a named file. Returns palette on success,
// NULL on failure. If, however, kPlt is not NULL, its
// contents will be filled with the identity palette on failure.

KLBDC KOLIBA_PALETTE * KOLIBA_ReadPaletteFromNamedFile(KOLIBA_PALETTE *kPlt, char *fname) {
	FILE *f;
	KOLIBA_PALETTE *retval;

	if (fname == NULL) return (kPlt == NULL) ? NULL : invalid(kPlt);
	retval = KOLIBA_ReadPaletteFromOpenFile(kPlt, f = fopen(fname, "rb"));
	if (f != NULL) fclose(f);
	return retval;
}

static KOLIBA_PALETTE * invalid(KOLIBA_PALETTE *kPlt) {
	memcpy(kPlt, &KOLIBA_IdentityPalette, sizeof(KOLIBA_PALETTE));
	return NULL;
}
