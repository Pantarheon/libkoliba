/*

	slt2pal.c

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

// These tables/arrays allow an easy expansion
// of 3-bit and 2-bit values into 8 bits,
// without the need for shifts and ors.
//
// The 3-bit values are repeated three
// times, but chopping off the lsb
// at the end to reduce the 9-bit result
// into an 8-bit value. This is easiest
// to do with octal notation because C
// does not officially support binary
// numbers.
static const uint8_t bin8[8] = {
	0000,	// 00 000 000 (0)
	0044,	// 00 100 100 (1)
	0111,	// 01 001 001 (0)
	0155,	// 01 101 101 (1)
	0222,	// 10 010 010 (0)
	0266,	// 10 110 110 (1)
	0333,	// 11 011 011 (0)
	0377	// 11 111 111 (1)
};

// The 2-bit values are repeated four times
// to create an 8-bit result. This time we
// use hexadecimal notation.
static const uint8_t bin4[4] = {
	0x00,	// 00 00 00 00
	0x55,	// 01 01 01 01
	0xAA,	// 10 10 10 10
	0xFF	// 11 11 11 11
};

// Convert KOLIBA_SLUT to a palette of 256 KOLIBA_RGBA8PIXEL
// values This can be used, among other things, for a low-quality
// but fast preview during editing. The alpha channels of all
// palette members are set to fully opaque (i.e., 255).

KLBDC KOLIBA_RGBA8PIXEL * KOLIBA_SlutToRgba8Palette(KOLIBA_RGBA8PIXEL *palette, KOLIBA_SLUT * const sLut, const double * const iconv, const unsigned char * const oconv) {
	unsigned int i, j, k, l;
	KOLIBA_VERTICES vertices;
	KOLIBA_FLUT fLut;
	KOLIBA_FLAGS flags;
	KOLIBA_XYZ px, xyz;
	const double *ic;

	ic = (iconv != NULL) ? iconv : KOLIBA_ByteDiv255;

	if (palette != NULL) {
		flags = KOLIBA_FlutFlags(KOLIBA_ConvertSlutToFlut(&fLut, KOLIBA_SlutToVertices(&vertices, (sLut != NULL) ? sLut : (KOLIBA_SLUT * const)&KOLIBA_IdentitySlut)));
		for (i = 0, l = 0; i < 8; i++) {
			px.x = ic[bin8[i]];
			for (j = 0; j < 8; j++) {
				px.y = ic[bin8[j]];
				for (k = 0; k < 4; k++, l++) {
					px.z = ic[bin4[k]];
					KOLIBA_XyzToRgba8Pixel(palette + l, KOLIBA_ApplyXyz(&xyz, &px, &fLut, flags), oconv)->a = 255;
				}
			}
		}
	}
	return palette;
}
