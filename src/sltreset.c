/*

	sltreset.c

	Copyright 2019-2021 G. Adam Stanislav
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
#include <string.h>

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

// Reset a sLut to default contents.

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlut(KOLIBA_SLUT *sLut) {
	return (sLut == NULL) ? sLut : memcpy(sLut, &KOLIBA_IdentitySlut, sizeof(KOLIBA_SLUT));
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutBlack(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->Black, &KOLIBA_IdentitySlut.Black, sizeof(KOLIBA_VERTEX));
	return sLut;
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutBlue(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->Blue, &KOLIBA_IdentitySlut.Blue, sizeof(KOLIBA_VERTEX));
	return sLut;
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutGreen(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->Green, &KOLIBA_IdentitySlut.Green, sizeof(KOLIBA_VERTEX));
	return sLut;
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutCyan(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->Cyan, &KOLIBA_IdentitySlut.Cyan, sizeof(KOLIBA_VERTEX));
	return sLut;
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutRed(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->Red, &KOLIBA_IdentitySlut.Red, sizeof(KOLIBA_VERTEX));
	return sLut;
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutMagenta(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->Magenta, &KOLIBA_IdentitySlut.Magenta, sizeof(KOLIBA_VERTEX));
	return sLut;
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutYellow(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->Yellow, &KOLIBA_IdentitySlut.Yellow, sizeof(KOLIBA_VERTEX));
	return sLut;
}

KLBDC KOLIBA_SLUT * KOLIBA_ResetSlutWhite(KOLIBA_SLUT *sLut) {
	if (sLut != NULL)
		memcpy(&sLut->White, &KOLIBA_IdentitySlut.White, sizeof(KOLIBA_VERTEX));
	return sLut;
}

