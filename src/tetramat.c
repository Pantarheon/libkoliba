/*

	tetramat.c

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

// Apply four matrices, one (Y) to all channels,
// then three (R,G,B) to individual channels.
KLBDC KOLIBA_MATRIX * KOLIBA_TetraMatrix(KOLIBA_MATRIX * output, const KOLIBA_MATRIX * const Y, const KOLIBA_MATRIX * const R, const KOLIBA_MATRIX * const G, const KOLIBA_MATRIX * const B) {
	KOLIBA_MATRIX m;

	if ((R == NULL) || (G == NULL) || (B == NULL)) return NULL;
	memcpy(&m.Red,   &(R->Red),   sizeof(KOLIBA_ROW));
	memcpy(&m.Green, &(G->Green), sizeof(KOLIBA_ROW));
	memcpy(&m.Blue,  &(B->Blue),  sizeof(KOLIBA_ROW));

	return KOLIBA_MultiplyMatrices(output, Y, &m);
}
