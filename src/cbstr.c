/*

	cbstr.c

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

KLBDC char * KOLIBA_ChannelBlendToString(char * string, const KOLIBA_CHANNELBLEND * const cb, unsigned int strsize) {
	unsigned int b;

	if ((string == NULL) || (cb == NULL) || (strsize < CBLAMINCHARS)) return NULL;

	b = (cb->na) ? 0x1000 : 0;
	if (cb->nr) b |= 0x0100;
	if (cb->ng) b |= 0x0010;
	if (cb->nb) b |= 0x0001;

	sprintf(
		string,
		KOLIBA_PrintCblnFormat,
		cb->mat.Red.r,
		cb->mat.Red.g,
		cb->mat.Red.b,
		cb->mat.Red.o,
		cb->mat.Green.r,
		cb->mat.Green.g,
		cb->mat.Green.b,
		cb->mat.Green.o,
		cb->mat.Blue.r,
		cb->mat.Blue.g,
		cb->mat.Blue.b,
		cb->mat.Blue.o,
		cb->efficacy,
		b
	);
	return string;
}

KLBDC KOLIBA_CHANNELBLEND * KOLIBA_StringToChannelBlend(KOLIBA_CHANNELBLEND * cb, const char * const string) {
	unsigned int b, bytes;

	if ((string == NULL) || (cb == NULL)) return NULL;

	bytes = sscanf(
		string,
		KOLIBA_ScanCblnFormat,
		&cb->mat.Red.r,
		&cb->mat.Red.g,
		&cb->mat.Red.b,
		&cb->mat.Red.o,
		&cb->mat.Green.r,
		&cb->mat.Green.g,
		&cb->mat.Green.b,
		&cb->mat.Green.o,
		&cb->mat.Blue.r,
		&cb->mat.Blue.g,
		&cb->mat.Blue.b,
		&cb->mat.Blue.o,
		&cb->efficacy,
		&b
	);

	if (bytes == 14) {
		cb->na = (bool)(b & 0xF000);
		cb->nr = (bool)(b & 0x0F00);
		cb->ng = (bool)(b & 0x00F0);
		cb->nb = (bool)(b & 0x000F);
		return cb;
	}

	else return NULL;
}
