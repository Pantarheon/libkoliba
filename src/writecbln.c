/*

	writecbln.c

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


// Write a KOLIBA_CHANNELBLEND to an open .cBln file. It remains
// open upon return, so the caller needs to close it. Returns 0
// on success, non-0 on failure.

KLBDC int KOLIBA_WriteCblnToOpenFile(const KOLIBA_CHANNELBLEND *cb, FILE *f) {
	unsigned int b;

	if ((cb == NULL) || (f == NULL)) return 1;

	b = (cb->na) ? 0x1000 : 0;
	if (cb->nr) b |= 0x0100;
	if (cb->ng) b |= 0x0010;
	if (cb->nb) b |= 0x0001;

	return fprintf(
		f,
		KOLIBA_PrintCblnFormat,
		cb->mat.red.r,
		cb->mat.red.g,
		cb->mat.red.b,
		cb->mat.red.o,
		cb->mat.green.r,
		cb->mat.green.g,
		cb->mat.green.b,
		cb->mat.green.o,
		cb->mat.blue.r,
		cb->mat.blue.g,
		cb->mat.blue.b,
		cb->mat.blue.o,
		cb->efficacy,
		b
	) - (CBLAMINCHARS-1);
}

// Write a KOLIBA_CHANNELBLEND to a named .cBln file.
// Returns 0 on success, non-0 on failure.

KLBDC int KOLIBA_WriteCblnToNamedFile(const KOLIBA_CHANNELBLEND *cb, const char *fname) {
	FILE *f;
	int retval;

	if ((cb == NULL) || (fname == NULL) || ((f = fopen(fname, "wb")) == NULL)) return -1;
	retval = KOLIBA_WriteCblnToOpenFile(cb, f);
	fclose(f);
	return retval;
}

