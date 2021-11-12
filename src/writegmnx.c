/*

	writegmnx.c

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


// Write a GEMINIX to an open .gmnx file. It remains open upon
// return, so the caller needs to close it. Returns 0 on
// success, non-0 on failure.


KLBDC int KOLIBA_WriteGmnxToOpenFile(const KOLIBA_GEMINIX *gem, FILE *f) {
	if ((gem == NULL) || (f == NULL)) return 1;
	return fprintf(
		f,
		KOLIBA_PrintGmnxFormat,
		gem->p.red.r,
		gem->p.red.g,
		gem->p.red.b,
		gem->p.red.o,
		gem->p.green.r,
		gem->p.green.g,
		gem->p.green.b,
		gem->p.green.o,
		gem->p.blue.r,
		gem->p.blue.g,
		gem->p.blue.b,
		gem->p.blue.o,
		gem->s.red.r,
		gem->s.red.g,
		gem->s.red.b,
		gem->s.red.o,
		gem->s.green.r,
		gem->s.green.g,
		gem->s.green.b,
		gem->s.green.o,
		gem->s.blue.r,
		gem->s.blue.g,
		gem->s.blue.b,
		gem->s.blue.o
	) - (GMXAMINCHARS-1);
}

// Write a GEMINIX to a named .gmnx file. Returns 0 on success, non-0
// on failure.

KLBDC int KOLIBA_WriteGmnxToNamedFile(const KOLIBA_GEMINIX *gem, const char *fname) {
	FILE *f;
	int retval;

	if ((gem == NULL) || (fname == NULL) || ((f = fopen(fname, "wb")) == NULL)) return -1;
	retval = KOLIBA_WriteGmnxToOpenFile(gem, f);
	fclose(f);
	return retval;
}

