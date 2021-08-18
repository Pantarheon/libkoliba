/*

	getdtafmt.c

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

#define	USECLIB
#include "koliba.h"
#include <string.h>

// Get the data type of a Koliba data file header.

KLBDC KOLIBA_ftype KOLIBA_GetFileDataFormat(const unsigned char * const header) {
	if (header == NULL)
		return KOLIBA_ftnoslut;

	if (memcmp(header, KOLIBA_sLutHeader, SLTCFILEHEADERBYTES) == 0)
		return KOLIBA_ftslut;
	else if (memcmp(header, KOLIBA_m3x4Header, SLTCFILEHEADERBYTES) == 0)
		return KOLIBA_ftmatrix;
	else if (memcmp(header, KOLIBA_chrmHeader, SLTCFILEHEADERBYTES) == 0)
		return KOLIBA_ftchrm;
	else if (memcmp(header+1, KOLIBA_dicrHeader+1, SLTCFILEHEADERBYTES-1) == 0)
		return KOLIBA_ftdicr;
	else if (memcmp(header, KOLIBA_cFltHeader, SLTCFILEHEADERBYTES) == 0)
		return KOLIBA_ftcflt;
	else return KOLIBA_GetStringDataFormat(header);
}
