/*

	pal8rgba.c

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

// Apply a 256-member RGBA8 palette to a number
// of RGBA8 pixels discarding their Alpha channel.
KLBDC KOLIBA_RGBA8PIXEL * KOLIBA_PaletteToRgba8(KOLIBA_RGBA8PIXEL * outframe, const KOLIBA_RGBA8PIXEL * const inframe, const KOLIBA_RGBA8PIXEL * const palette, unsigned int count) {
	if ((outframe == NULL) || (inframe == NULL) || (palette == NULL))
		return NULL;

	for (; count; count--) {
		outframe[count-1].px = palette[(inframe[count-1].r & 0xE0) | ((inframe[count-1].g >> 3) & 0x1C) | ((inframe[count-1].b >> 6) & 3)].px;
	}
	return outframe;
}

// Apply a 256-member RGBA8 palette to a number
// of RGBA8 pixels preserving their Alpha channel.
KLBDC KOLIBA_RGBA8PIXEL * KOLIBA_PaletteToRgba8Alpha(KOLIBA_RGBA8PIXEL * outframe, const KOLIBA_RGBA8PIXEL * const inframe, const KOLIBA_RGBA8PIXEL * const palette, unsigned int count) {

	if ((outframe == NULL) || (inframe == NULL) || (palette == NULL))
		return NULL;

	for (; count; count--) {
		outframe[count-1].px = palette[(inframe[count-1].r & 0xE0) | ((inframe[count-1].g >> 3) & 0x1C) | ((inframe[count-1].b >> 6) & 3)].px;
		outframe[count-1].a  = inframe[count-1].a;
	}
	return outframe;
}
