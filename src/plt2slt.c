/*

	plt2slt.c

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

// Convert a palette to a sLut

KLBDC KOLIBA_SLUT * KOLIBA_ConvertPaletteToSlut(KOLIBA_SLUT * sLut, const KOLIBA_PALETTE * const plt) {
	double effi;

	if ((sLut == NULL) || (plt == NULL)) return NULL;

	effi = plt->efficacy;

	KOLIBA_Interpolate((double *)&sLut->Black, (double *)&plt->Black, plt->Black.efficacy * effi, (double *)&KOLIBA_IdentitySlut.Black, 3);
	KOLIBA_Interpolate((double *)&sLut->White, (double *)&plt->White, plt->White.efficacy * effi, (double *)&KOLIBA_IdentitySlut.White, 3);
	KOLIBA_Interpolate((double *)&sLut->Red, (double *)&plt->Red, plt->Red.efficacy * effi, (double *)&KOLIBA_IdentitySlut.Red, 3);

	if (plt->erythropy) return KOLIBA_ApplyErythropy(sLut, sLut);

	KOLIBA_Interpolate((double *)&sLut->Green, (double *)&plt->Green, plt->Green.efficacy * effi, (double *)&KOLIBA_IdentitySlut.Green, 3);
	KOLIBA_Interpolate((double *)&sLut->Blue, (double *)&plt->Blue, plt->Blue.efficacy * effi, (double *)&KOLIBA_IdentitySlut.Blue, 3);
	KOLIBA_Interpolate((double *)&sLut->Cyan, (double *)&plt->Cyan, plt->Cyan.efficacy * effi, (double *)&KOLIBA_IdentitySlut.Cyan, 3);
	KOLIBA_Interpolate((double *)&sLut->Magenta, (double *)&plt->Magenta, plt->Magenta.efficacy * effi, (double *)&KOLIBA_IdentitySlut.Magenta, 3);
	KOLIBA_Interpolate((double *)&sLut->Yellow, (double *)&plt->Yellow, plt->Yellow.efficacy * effi, (double *)&KOLIBA_IdentitySlut.Yellow, 3);

	return sLut;
}
