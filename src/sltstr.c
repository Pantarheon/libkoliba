/*

	sltstr.c

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

KLBDC char * KOLIBA_SlutToString(char * string, const KOLIBA_SLUT * const sLut, unsigned int strsize) {
	if ((string == NULL) || (sLut == NULL) || (strsize < SLTAMINCHARS)) return NULL;

	sprintf(
		string,
		pfmt,
		sLut->black.r,
		sLut->black.g,
		sLut->black.b,
		sLut->blue.r,
		sLut->blue.g,
		sLut->blue.b,
		sLut->green.r,
		sLut->green.g,
		sLut->green.b,
		sLut->cyan.r,
		sLut->cyan.g,
		sLut->cyan.b,
		sLut->red.r,
		sLut->red.g,
		sLut->red.b,
		sLut->magenta.r,
		sLut->magenta.g,
		sLut->magenta.b,
		sLut->yellow.r,
		sLut->yellow.g,
		sLut->yellow.b,
		sLut->white.r,
		sLut->white.g,
		sLut->white.b
	);
	return string;
}

KLBDC KOLIBA_SLUT * KOLIBA_StringToSlut(KOLIBA_SLUT * sLut, const char * const string) {
	if ((string == NULL) || (sLut == NULL)) return NULL;

	return (sscanf(
		string,
		KOLIBA_ScanSlttFormat,
		&sLut->black.r,
		&sLut->black.g,
		&sLut->black.b,
		&sLut->blue.r,
		&sLut->blue.g,
		&sLut->blue.b,
		&sLut->green.r,
		&sLut->green.g,
		&sLut->green.b,
		&sLut->cyan.r,
		&sLut->cyan.g,
		&sLut->cyan.b,
		&sLut->red.r,
		&sLut->red.g,
		&sLut->red.b,
		&sLut->magenta.r,
		&sLut->magenta.g,
		&sLut->magenta.b,
		&sLut->yellow.r,
		&sLut->yellow.g,
		&sLut->yellow.b,
		&sLut->white.r,
		&sLut->white.g,
		&sLut->white.b
	) != 24) ? NULL : sLut;
}
