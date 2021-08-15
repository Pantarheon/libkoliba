/*

	writechrt.c

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


// Write a KOLIBA_CHROMAT to an open .chrt file. It remains open
// upon return, so the caller needs to close it. Returns 0 on
// success, non-0 on failure.

KLBDC int KOLIBA_WriteChrtToOpenFile(const KOLIBA_CHROMAT *chrt, FILE *f) {
	if ((chrt == NULL) || (f == NULL)) return 1;
	return fprintf(
		f,
		KOLIBA_PrintChrtFormat,
		chrt->model.r,
		chrt->model.g,
		chrt->model.b,
		chrt->chroma.angle,
		chrt->chroma.magnitude,
		chrt->chroma.saturation,
		chrt->chroma.black,
		chrt->chroma.white
	) - (CHRAMINCHARS-1);
}

// Write a KOLIBA_CHROMAT to a named .chrt file.
// Returns 0 on success, non-0 on failure.

KLBDC int KOLIBA_WriteChrtToNamedFile(const KOLIBA_CHROMAT *chrt, const char *fname) {
	FILE *f;
	int retval;

	if ((chrt == NULL) || (fname == NULL) || ((f = fopen(fname, "wb")) == NULL)) return -1;
	retval = KOLIBA_WriteChrtToOpenFile(chrt, f);
	fclose(f);
	return retval;
}

