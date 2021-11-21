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

	sLut->Black.r   =   primary->Red.o;
	sLut->Black.g   =   primary->Green.o;
	sLut->Black.b   =   primary->Blue.o;
	sLut->Blue.r    =   primary->Red.b  +  primary->Red.o;
	sLut->Blue.g    =   primary->Green.b+  primary->Green.o;
	sLut->Blue.b    =   primary->Blue.b +  primary->Blue.o;
	sLut->Green.r   =   primary->Red.g  +  primary->Red.o;
	sLut->Green.g   =   primary->Green.g+  primary->Green.o;
	sLut->Green.b   =   primary->Blue.g +  primary->Blue.o;
	sLut->Cyan.r    = secondary->Red.b  +secondary->Red.g  +secondary->Red.o;
	sLut->Cyan.g    = secondary->Green.b+secondary->Green.g+secondary->Green.o;
	sLut->Cyan.b    = secondary->Blue.b +secondary->Blue.g +secondary->Blue.o;
	sLut->Red.r     =   primary->Red.r  +  primary->Red.o;
	sLut->Red.g     =   primary->Green.r+  primary->Green.o;
	sLut->Red.b     =   primary->Blue.r +  primary->Blue.o;
	sLut->Magenta.r = secondary->Red.r  +secondary->Red.b  +secondary->Red.o;
	sLut->Magenta.g = secondary->Green.r+secondary->Green.b+secondary->Green.o;
	sLut->Magenta.b = secondary->Blue.r +secondary->Blue.b +secondary->Blue.o;
	sLut->Yellow.r  = secondary->Red.r  +secondary->Red.g  +secondary->Red.o;
	sLut->Yellow.g  = secondary->Green.r+secondary->Green.g+secondary->Green.o;
	sLut->Yellow.b  = secondary->Blue.r +secondary->Blue.g +secondary->Blue.o;
	sLut->White.r   = secondary->Red.b  +secondary->Red.g  +secondary->Red.r  +secondary->Red.o;
	sLut->White.g   = secondary->Green.b+secondary->Green.g+secondary->Green.r+secondary->Green.o;
	sLut->White.b   = secondary->Blue.b +secondary->Blue.g +secondary->Blue.r +secondary->Blue.o;

	return sLut;
}
