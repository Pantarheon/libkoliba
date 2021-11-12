/*

	gmnxstr.c

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

#include "koliba.h"
#include <stdio.h>
#include <string.h>

KLBDC char * KOLIBA_GeminixToString(char * string, const KOLIBA_GEMINIX * const gem, unsigned int strsize) {
	if ((string == NULL) || (gem == NULL) || (strsize < GMXAMINCHARS)) return NULL;

	sprintf(
		string,
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
	);
	return string;
}

KLBDC KOLIBA_GEMINIX * KOLIBA_StringToGeminix(KOLIBA_GEMINIX * gem, const char * const string) {
	if ((string == NULL) || (gem == NULL)) return NULL;

	return (sscanf(
		string,
		KOLIBA_ScanGmnxFormat,
		&gem->p.red.r,
		&gem->p.red.g,
		&gem->p.red.b,
		&gem->p.red.o,
		&gem->p.green.r,
		&gem->p.green.g,
		&gem->p.green.b,
		&gem->p.green.o,
		&gem->p.blue.r,
		&gem->p.blue.g,
		&gem->p.blue.b,
		&gem->p.blue.o,
		&gem->s.red.r,
		&gem->s.red.g,
		&gem->s.red.b,
		&gem->s.red.o,
		&gem->s.green.r,
		&gem->s.green.g,
		&gem->s.green.b,
		&gem->s.green.o,
		&gem->s.blue.r,
		&gem->s.blue.g,
		&gem->s.blue.b,
		&gem->s.blue.o
	) != 24) ? NULL : gem;
}
