/*

	readdicr.c

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

static KOLIBA_DICHROMA * invalid(KOLIBA_DICHROMA *dicr) {
	KOLIBA_ResetDichromaticMatrix(dicr);
	return NULL;
}

// Read a dichromatic matrix from an open .dicr file. It needs
// to be open for reading binary data. It remains open upon
// return, so the caller needs to close it. Returns dichromatic
// matrix on success, NULL on failure. If, however, dicr is
// not NULL, its contents will be filled with the identity
// dichromatic matrix, using the Rec. 2020 model, on failure.

KLBDC KOLIBA_DICHROMA * KOLIBA_ReadDichromaticMatrixFromOpenFile(KOLIBA_DICHROMA *dicr, FILE *f, unsigned int *normalize, unsigned int *channel) {
	KOLIBA_DICHROMA2 mat;
	unsigned char header[SLTCFILEHEADERBYTES];

	if (dicr == NULL) return NULL;
	if (f == NULL) return invalid(dicr);

	if (fread(header, 1, SLTCFILEHEADERBYTES, f) != SLTCFILEHEADERBYTES) return invalid(dicr);
	if (((header[0] & 0xF4) != 0xA0) || ((header[0] & 0x03) == 3) ||
	(memcmp(header+1, &KOLIBA_dicrHeader[1], SLTCFILEHEADERBYTES-1) != 0))
		return invalid(dicr);
	if (fread(&mat, 1, sizeof(KOLIBA_DICHROMA2), f) != sizeof(KOLIBA_DICHROMA2)) return invalid(dicr);
	KOLIBA_FixDoubles((double *)&mat, sizeof(KOLIBA_DICHROMA2) / sizeof(double));
	if (KOLIBA_CheckDicr(&mat.dichroma, mat.checksum) == 0) return invalid(dicr);
	if (normalize) *normalize = (header[0] & 0x08) >> 3;
	if (channel)   *channel   =  header[0] & 0x03;
	return memcpy(dicr, &mat.dichroma, sizeof(KOLIBA_DICHROMA));
}

// Read a dichromatic matrix from a named file. Returns the
// matrix on success, NULL on failure. If, however, dicr is
// not NULL, its contents will be filled with the identity
// dichromatic matrix, using the Rec. 2020 model, on failure.

KLBDC KOLIBA_DICHROMA * KOLIBA_ReadDichromaticMatrixFromNamedFile(KOLIBA_DICHROMA *dicr, char *fname, unsigned int *normalize, unsigned int *channel) {
	FILE *f;
	KOLIBA_DICHROMA *retval;

	if (fname == NULL) return (dicr == NULL) ? NULL : invalid(dicr);
	retval = KOLIBA_ReadDichromaticMatrixFromOpenFile(dicr, f = fopen(fname, "rb"), normalize, channel);
	if (f != NULL) fclose(f);
	return retval;
}
