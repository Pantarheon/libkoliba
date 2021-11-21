/*

	nofarba.c

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

// Discard the farba from a sLut

KLBDC KOLIBA_SLUT * KOLIBA_DiscardSlutFarba(KOLIBA_SLUT * output, const KOLIBA_SLUT * const input) {
	if ((input == NULL) || (output == NULL)) return NULL;

	if (output != input) {
		memmove(&output->Black, &input->Black, sizeof(KOLIBA_VERTEX));
		memmove(&output->White, &input->White, sizeof(KOLIBA_VERTEX));
	}

	output->Red.r     = input->White.r;
	output->Red.g     = input->Black.g;
	output->Red.b     = input->Black.b;
	output->Green.r   = input->Black.r;
	output->Green.g   = input->White.g;
	output->Green.b   = input->Black.b;
	output->Blue.r    = input->Black.r;
	output->Blue.g    = input->Black.g;
	output->Blue.b    = input->White.b;
	output->Cyan.r    = input->Black.r;
	output->Cyan.g    = input->White.g;
	output->Cyan.b    = input->White.b;
	output->Magenta.r = input->White.r;
	output->Magenta.g = input->Black.g;
	output->Magenta.b = input->White.b;
	output->Yellow.r  = input->White.r;
	output->Yellow.g  = input->White.g;
	output->Yellow.b  = input->Black.b;

	return output;
}
