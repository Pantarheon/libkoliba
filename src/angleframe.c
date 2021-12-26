/*

	angleframe.c

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
#include <math.h>

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

// Convert a frame/frames into turns of a circular angle.
// The result is not normalized, so it can be negative
// or exceed one turn. However, "frames", though signed,
// must be a positive integer. It is declared signed
// only because at least some microprocessors assume
// an integer is signed before it is converted to double.
KLBDC KOLIBA_ANGLE * KOLIBA_AngleFromFrame(KOLIBA_ANGLE * kAng, int frame, int frames) {
	if ((frames <= 0) || (kAng == NULL)) return NULL;

	kAng->angle = (double)frame / (double)frames;
	kAng->units = KAU_turns;
	return kAng;
}

KLBDC KOLIBA_ANGLE * KOLIBA_AngleFromFrameWithShift(KOLIBA_ANGLE * kAng, int frame, int frames, double shift) {
	if ((frames <= 0) || (kAng == NULL)) return NULL;

	kAng->angle = (frame <= 0) ? 0.0 : (frame >= frames) ? 1.0 : pow((double)frame / (double)frames, shift);
	kAng->units = KAU_turns;
	return kAng;
}
