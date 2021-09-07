/*

	fltscale.c

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

// Scale the sLut factors in a FLUT so that the results
// of applying them does not have to be scaled up for
// every channel of every pixel.
//
// While the input of the respective KOLIBA_ApplyXyz()
// still expects the values in the nominal 0-1 range,
// the output of a scaled FLUT will be in the 0-n range,
// where n is the scale factor applied here.
//
// This saves processing time because with the most common
// pixel size of using 8-bit integer bytes for the channels
// converting them to the 0-1 range is a matter of a small
// lookup table, but we avoid multiplying them back by 255
// (or whatever factor we use) and only need to convert them
// back to integers, which modern processors do fast.
//
// The scaling should normally be the last step before
// pixel processing because it breaks such things as
// checking for an identity FLUT, it makes interpolating
// FLUTS harder, etc.

KLBDC KOLIBA_FLUT * KOLIBA_ScaleFlut(KOLIBA_FLUT *scaled, const KOLIBA_FLUT * const fLut, double factor) {
	double *output = (double *)scaled;
	const double * const input = (double *)fLut;
	unsigned int i;

	if ((scaled == NULL) || (fLut == NULL)) return NULL;

	for (i = 0; i < (sizeof(KOLIBA_FLUT) / sizeof(double)); i++ )
		output[i] = factor * input[i];
	return scaled;
}
