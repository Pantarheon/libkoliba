/*

	rdcmpmtx.c

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

static KOLIBA_MATRIX * invalid(KOLIBA_MATRIX *mat, KOLIBA_ftype *ft, KOLIBA_ftype err) {
	memcpy(mat, &KOLIBA_IdentityMatrix, sizeof(KOLIBA_MATRIX));
	if (ft) *ft = err;
	return NULL;
}

// Read a matrix from an open compatible file. It needs to be open
// for reading binary data. It remains open upon return, so
// the caller needs to close it. Returns mat on success, NULL
// on failure. If, however, mat is not NULL, its contents
// will be filled with the identity mat on failure.

KLBDC KOLIBA_MATRIX * KOLIBA_ReadMatrixFromCompatibleOpenFile(KOLIBA_MATRIX *mat, FILE *f, KOLIBA_ftype *ft) {
	KOLIBA_CHROMAT chrm;
	KOLIBA_DICHROMA dicr;
	unsigned char header[SLTCFILEHEADERBYTES+1];
	double d;
	unsigned int normalize, channel;

	if (mat == NULL) {
		if (ft) *ft = KOLIBA_ftnoslut;
		return NULL;
	}
	if (f == NULL) return invalid(mat, ft, KOLIBA_ftnofile);

	if (fread(header, 1, SLTCFILEHEADERBYTES, f) != SLTCFILEHEADERBYTES)
		return invalid(mat, ft, KOLIBA_ftunknown);
	if (fseek(f, -(SLTCFILEHEADERBYTES), SEEK_CUR) != 0)
		return invalid(mat, ft, KOLIBA_ftunknown);

	// This should limit sscanf input to the bytes read into the header.
	header[SLTCFILEHEADERBYTES] = '\0';

	switch(KOLIBA_GetFileDataFormat(header)) {
		case KOLIBA_ftmatrix:
			if (KOLIBA_ReadMatrixFromOpenFile(mat, f) == NULL)
				return invalid(mat, ft, KOLIBA_ftmatrix);
			else if (ft) *ft = KOLIBA_ftmatrix;
			break;
		case KOLIBA_ftm34t:
			if (KOLIBA_ReadM34tFromOpenFile(mat, f) == NULL)
				return invalid(mat, ft, KOLIBA_ftm34t);
			else if (ft) *ft = KOLIBA_ftm34t;
			break;
		case KOLIBA_ftchrm:
			if (KOLIBA_ChromaticMatrix(mat, KOLIBA_ReadChromaticMatrixFromOpenFile(&chrm, f)) == NULL)
				return invalid(mat, ft, KOLIBA_ftchrm);
			else if (ft) *ft = KOLIBA_ftchrm;
			break;
		case KOLIBA_ftchrt:
			if (KOLIBA_ChromaticMatrix(mat, KOLIBA_ReadChrtFromOpenFile(&chrm, f)) == NULL)
				return invalid(mat, ft, KOLIBA_ftchrt);
			else if (ft) *ft = KOLIBA_ftchrt;
			break;
		case KOLIBA_ftdicr:
			if ((KOLIBA_ReadDichromaticMatrixFromOpenFile(&dicr, f, &normalize, &channel) == NULL) ||
			(KOLIBA_DichromaticMatrix(mat, &dicr, normalize, channel) == NULL))
				return invalid(mat, ft, KOLIBA_ftdicr);
			else if (ft) *ft = KOLIBA_ftdicr;
			break;
		default:
			return invalid(mat, ft, KOLIBA_ftunknown);
			break;
	}

	return mat;
}

// Read a matrix from a named compatible file. Returns mat on success,
// NULL on failure. If, however, mat is not NULL, its
// contents will be filled with the identity mat on failure.

KLBDC KOLIBA_MATRIX * KOLIBA_ReadMatrixFromCompatibleNamedFile(KOLIBA_MATRIX *mat, char *fname, KOLIBA_ftype *ft) {
	FILE *f;
	KOLIBA_MATRIX *retval;

	if (fname == NULL) return (mat == NULL) ? NULL : invalid(mat, ft, KOLIBA_ftnofile);
	retval = KOLIBA_ReadMatrixFromCompatibleOpenFile(mat, f = fopen(fname, "rb"), ft);
	if (f != NULL) fclose(f);
	return retval;
}
