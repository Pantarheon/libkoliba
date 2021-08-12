/*

	rdcmpslut.c

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

// Read a sLut from an open compatible file. It needs to be open
// for reading binary data. It remains open upon return, so
// the caller needs to close it. Returns sLut on success, NULL
// on failure. If, however, sLut is not NULL, its contents
// will be filled with the identity sLut on failure.

KLBDC KOLIBA_SLUT * KOLIBA_ReadSlutFromCompatibleOpenFile(KOLIBA_SLUT *sLut, FILE *f, KOLIBA_ftype *ft) {
	KOLIBA_SLUT Lut;
	unsigned char header[SLTCFILEHEADERBYTES+1];
	double d;

	if (sLut == NULL) {
		if (ft) *ft = KOLIBA_ftnoslut;
		return NULL;
	}
	if (f == NULL) return invalid(sLut, ft, KOLIBA_ftnofile);

	if (fread(header, 1, SLTCFILEHEADERBYTES, f) != SLTCFILEHEADERBYTES)
		return invalid(sLut, ft, KOLIBA_ftunknown);
	if (fseek(f, -(SLTCFILEHEADERBYTES), SEEK_CUR) != 0)
		return invalid(sLut, ft, KOLIBA_ftunknown);

	// This should limit sscanf input to the bytes read into the header.
	header[SLTCFILEHEADERBYTES] = '\0';

	if (memcmp(header, KOLIBA_sLutHeader, SLTCFILEHEADERBYTES) == 0) {
		if (ft) *ft = KOLIBA_ftslut;
		return KOLIBA_ReadSlutFromOpenFile(sLut, f);
	}
	else if (sscanf(header, KOLIBA_ScanSlttHeaderFormat, &d) == 1) {
		if (ft) *ft = KOLIBA_ftsltt;
		return KOLIBA_ReadSlttFromOpenFile(sLut, f);
	}
	else if (memcmp(header, KOLIBA_m3x4Header, SLTCFILEHEADERBYTES) == 0) {
		KOLIBA_MATRIX m3x4;

		if (KOLIBA_ConvertMatrixToSlut(sLut, KOLIBA_ReadMatrixFromOpenFile(&m3x4, f)) == NULL)
			return invalid(sLut, ft, KOLIBA_ftmatrix);
		else if (ft) *ft = KOLIBA_ftmatrix;
	}
	else if (sscanf(header, KOLIBA_ScanM34tHeaderFormat, &d) == 1) {
		KOLIBA_MATRIX m3x4;

		if (KOLIBA_ConvertMatrixToSlut(sLut, KOLIBA_ReadM34tFromOpenFile(&m3x4, f)) == NULL)
			return invalid(sLut, ft, KOLIBA_ftm34t);
		else if (ft) *ft = KOLIBA_ftm34t;
	}
	else if (memcmp(header, KOLIBA_chrmHeader, SLTCFILEHEADERBYTES) == 0) {
		KOLIBA_MATRIX m3x4;
		KOLIBA_CHROMAT chrm;

		if (KOLIBA_ConvertMatrixToSlut(sLut, KOLIBA_ChromaticMatrix(&m3x4, KOLIBA_ReadChromaticMatrixFromOpenFile(&chrm, f))) == NULL)
			return invalid(sLut, ft, KOLIBA_ftchrm);
		else if (ft) *ft = KOLIBA_ftchrm;
	}
	else if (sscanf(header, KOLIBA_ScanChrtHeaderFormat, &d) == 1) {
		KOLIBA_MATRIX m3x4;
		KOLIBA_CHROMAT chrm;

		if (KOLIBA_ConvertMatrixToSlut(sLut, KOLIBA_ChromaticMatrix(&m3x4, KOLIBA_ReadChrtFromOpenFile(&chrm, f))) == NULL)
			return invalid(sLut, ft, KOLIBA_ftchrt);
		else if (ft) *ft = KOLIBA_ftchrt;
	}
	else if (memcmp(header, KOLIBA_cFltHeader, SLTCFILEHEADERBYTES) == 0) {
		KOLIBA_CFLT cFlt;

		if (KOLIBA_ConvertColorFilterToSlut(sLut, KOLIBA_ReadColorFilterFromOpenFile(&cFlt, f)) == NULL)
			return invalid(sLut, ft, KOLIBA_ftcflt);
		else if (ft) *ft = KOLIBA_ftcflt;
	}
	else return invalid(sLut, ft, KOLIBA_ftunknown);

	return sLut;
}

// Read a sLut from a named compatible file. Returns sLut on success,
// NULL on failure. If, however, sLut is not NULL, its
// contents will be filled with the identity sLut on failure.

KLBDC KOLIBA_SLUT * KOLIBA_ReadSlutFromCompatibleNamedFile(KOLIBA_SLUT *sLut, char *fname, KOLIBA_ftype *ft) {
	FILE *f;
	KOLIBA_SLUT *retval;

	if (fname == NULL) return (sLut == NULL) ? NULL : invalid(sLut, ft, KOLIBA_ftnofile);
	retval = KOLIBA_ReadSlutFromCompatibleOpenFile(sLut, f = fopen(fname, "rb"), ft);
	if (f != NULL) fclose(f);
	return retval;
}
