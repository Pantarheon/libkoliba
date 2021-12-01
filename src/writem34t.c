/*

	writem34t.c

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


// Write a KOLIBA_MATRIX to an open .m34t file. It remains open
// upon return, so the caller needs to close it. Returns 0 on
// success, non-0 on failure.


KLBDC int KOLIBA_WriteM34tToOpenFile(const KOLIBA_MATRIX *m3x4, FILE *f) {
	if ((m3x4 == NULL) || (f == NULL)) return 1;
	return fprintf(
		f,
		KOLIBA_PrintM34tFormat,
		m3x4->Red.r,
		m3x4->Red.g,
		m3x4->Red.b,
		m3x4->Red.o,
		m3x4->Green.r,
		m3x4->Green.g,
		m3x4->Green.b,
		m3x4->Green.o,
		m3x4->Blue.r,
		m3x4->Blue.g,
		m3x4->Blue.b,
		m3x4->Blue.o
	) - (MATAMINCHARS-1);
}

// Write a KOLIBA_MATRIX to a named .m34t file.
// Returns 0 on success, non-0 on failure.

KLBDC int KOLIBA_WriteM34tToNamedFile(const KOLIBA_MATRIX *m3x4, const char *fname) {
	FILE *f;
	int retval;

	if ((m3x4 == NULL) || (fname == NULL) || ((f = fopen(fname, "wb")) == NULL)) return -1;
	retval = KOLIBA_WriteM34tToOpenFile(m3x4, f);
	fclose(f);
	return retval;
}

