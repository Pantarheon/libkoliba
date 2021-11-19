/*

	readcbln.c

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

static KOLIBA_CHANNELBLEND * invalid(KOLIBA_CHANNELBLEND *cb) {
	KOLIBA_ResetChannelBlend(cb);
	return NULL;
}

// Read a KOLIBA_CHANNELBLEND from an open .cBln file. It may be open
// for reading binary or text data. It remains open upon return,
// so the caller needs to close it. Returns blend on success, NULL
// on failure. If, however, blend is not NULL, its contents
// will be reset on failure.

KLBDC KOLIBA_CHANNELBLEND * KOLIBA_ReadCblnFromOpenFile(KOLIBA_CHANNELBLEND *blend, FILE *f) {
	KOLIBA_CHANNELBLEND cb;
	unsigned int b, args;

	if (blend == NULL) return NULL;
	if (f == NULL) return invalid(blend);

	args = fscanf(
		f,
		KOLIBA_ScanCblnFormat,
		&cb.mat.red.r,
		&cb.mat.red.g,
		&cb.mat.red.b,
		&cb.mat.red.o,
		&cb.mat.green.r,
		&cb.mat.green.g,
		&cb.mat.green.b,
		&cb.mat.green.o,
		&cb.mat.blue.r,
		&cb.mat.blue.g,
		&cb.mat.blue.b,
		&cb.mat.blue.o,
		&cb.efficacy,
		&b
	);

	if (args == 14) {
		cb.na = (bool)(b & 0xF000);
		cb.nr = (bool)(b & 0x0F00);
		cb.ng = (bool)(b & 0x00F0);
		cb.nb = (bool)(b & 0x000F);
		return memcpy(blend, &cb, sizeof(KOLIBA_CHANNELBLEND));
	}

	else return invalid(blend);
}

// Read a blend from a named .cBln file. Returns cb on success,
// NULL on failure. If, however, cb is not NULL, its
// contents will be filled with the identity cb on failure.

KLBDC KOLIBA_CHANNELBLEND * KOLIBA_ReadCblnFromNamedFile(KOLIBA_CHANNELBLEND *cb, char *fname) {
	FILE *f;
	KOLIBA_CHANNELBLEND *retval;

	if (fname == NULL) return (cb == NULL) ? NULL : invalid(cb);
	retval = KOLIBA_ReadCblnFromOpenFile(cb, f = fopen(fname, "rb"));
	if (f != NULL) fclose(f);
	return retval;
}
