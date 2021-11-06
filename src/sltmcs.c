/*

	sltmcs.c

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

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

KLBDC KOLIBA_SLUT * KOLIBA_ConvertMatricesToSlut(KOLIBA_SLUT * sLut, const KOLIBA_MATRIX * const primary,  const KOLIBA_MATRIX * const secondary) {
	if ((sLut == NULL) || (primary == NULL) || (secondary == NULL)) return NULL;

	sLut->black.r = primary->red.o;
	sLut->black.g = primary->green.o;
	sLut->black.b = primary->blue.o;
	sLut->blue.r = primary->red.b+primary->red.o;
	sLut->blue.g = primary->green.b+primary->green.o;
	sLut->blue.b = primary->blue.b+primary->blue.o;
	sLut->green.r = primary->red.g+primary->red.o;
	sLut->green.g = primary->green.g+primary->green.o;
	sLut->green.b = primary->blue.g+primary->blue.o;
	sLut->cyan.r = secondary->red.b+secondary->red.g+secondary->red.o;
	sLut->cyan.g = secondary->green.b+secondary->green.g+secondary->green.o;
	sLut->cyan.b = secondary->blue.b+secondary->blue.g+secondary->blue.o;
	sLut->red.r = primary->red.r+primary->red.o;
	sLut->red.g = primary->green.r+primary->green.o;
	sLut->red.b = primary->blue.r+primary->blue.o;
	sLut->magenta.r = secondary->red.r+secondary->red.b+secondary->red.o;
	sLut->magenta.g = secondary->green.r+secondary->green.b+secondary->green.o;
	sLut->magenta.b = secondary->blue.r+secondary->blue.b+secondary->blue.o;
	sLut->yellow.r = secondary->red.r+secondary->red.g+secondary->red.o;
	sLut->yellow.g = secondary->green.r+secondary->green.g+secondary->green.o;
	sLut->yellow.b = secondary->blue.r+secondary->blue.g+secondary->blue.o;
	sLut->white.r = secondary->red.b+secondary->red.g+secondary->red.r+secondary->red.o;
	sLut->white.g = secondary->green.b+secondary->green.g+secondary->green.r+secondary->green.o;
	sLut->white.b = secondary->blue.b+secondary->blue.g+secondary->blue.r+secondary->blue.o;

	return sLut;
}
