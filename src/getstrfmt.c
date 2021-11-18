/*

	getstrfmt.c

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

// Get the data type of a Koliba data string.
// The string mut be at least SLTCFILEHEADERBYTES
// bytes in size.

KLBDC KOLIBA_ftype KOLIBA_GetStringDataFormat(const unsigned char * const data) {
	double d;

	if (data == NULL)
		return KOLIBA_ftnoslut;

	if (sscanf(data, KOLIBA_ScanSlttHeaderFormat, &d) == 1)
		return KOLIBA_ftsltt;
	else if (sscanf(data, KOLIBA_ScanM34tHeaderFormat, &d) == 1)
		return KOLIBA_ftm34t;
	else if (sscanf(data, KOLIBA_ScanChrtHeaderFormat, &d) == 1)
		return KOLIBA_ftchrt;
	else if (sscanf(data, KOLIBA_ScanPlttHeaderFormat, &d) == 1)
		return KOLIBA_ftkptt;
	else if (sscanf(data, KOLIBA_ScanGmnxHeaderFormat, &d) == 1)
		return KOLIBA_ftgmnx;
	else if (sscanf(data, KOLIBA_ScanCblnHeaderFormat, &d) == 1)
		return KOLIBA_ftcbln;
	else return KOLIBA_ftunknown;
}
