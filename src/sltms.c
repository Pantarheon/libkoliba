/*

	sltms.c

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

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

KLBDC KOLIBA_SLUT * KOLIBA_ConvertMatrixToSlut(KOLIBA_SLUT * sLut, const KOLIBA_MATRIX * const mat) {
	if ((sLut == NULL) || (mat == NULL)) return NULL;

	sLut->Black.r   = mat->Red.o;
	sLut->Black.g   = mat->Green.o;
	sLut->Black.b   = mat->Blue.o;
	sLut->Blue.r    = mat->Red.b   + mat->Red.o;
	sLut->Blue.g    = mat->Green.b + mat->Green.o;
	sLut->Blue.b    = mat->Blue.b  + mat->Blue.o;
	sLut->Green.r   = mat->Red.g   + mat->Red.o;
	sLut->Green.g   = mat->Green.g + mat->Green.o;
	sLut->Green.b   = mat->Blue.g  + mat->Blue.o;
	sLut->Cyan.r    = mat->Red.b   + mat->Red.g   + mat->Red.o;
	sLut->Cyan.g    = mat->Green.b + mat->Green.g + mat->Green.o;
	sLut->Cyan.b    = mat->Blue.b  + mat->Blue.g  + mat->Blue.o;
	sLut->Red.r     = mat->Red.r   + mat->Red.o;
	sLut->Red.g     = mat->Green.r + mat->Green.o;
	sLut->Red.b     = mat->Blue.r  + mat->Blue.o;
	sLut->Magenta.r = mat->Red.r   + mat->Red.b   + mat->Red.o;
	sLut->Magenta.g = mat->Green.r + mat->Green.b + mat->Green.o;
	sLut->Magenta.b = mat->Blue.r  + mat->Blue.b  + mat->Blue.o;
	sLut->Yellow.r  = mat->Red.r   + mat->Red.g   + mat->Red.o;
	sLut->Yellow.g  = mat->Green.r + mat->Green.g + mat->Green.o;
	sLut->Yellow.b  = mat->Blue.r  + mat->Blue.g  + mat->Blue.o;
	sLut->White.r   = mat->Red.b   + mat->Red.g   + mat->Red.r   + mat->Red.o;
	sLut->White.g   = mat->Green.b + mat->Green.g + mat->Green.r + mat->Green.o;
	sLut->White.b   = mat->Blue.b  + mat->Blue.g  + mat->Blue.r  + mat->Blue.o;

	return sLut;
}
