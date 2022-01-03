/*

	anglet.c

	Copyright 2022 G. Adam Stanislav
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

// Convert a "t" into turns of a circular angle.
KLBDC KOLIBA_ANGLE * KOLIBA_AngleFromT(KOLIBA_ANGLE * kAng, double t, double exponent) {
	if (kAng != NULL) {
		double angle = fmod(1.0+fmod(t,1.0),1.0);

		if (exponent != 1.0) {
			angle = pow(angle,exponent);
		}
		kAng->angle = angle;
		kAng->units = KAU_turns;
	}
	return kAng;
}

KLBDC KOLIBA_ANGLE * KOLIBA_AngleMonocycleFromT(KOLIBA_ANGLE * kAng, double t, double exponent) {
	if (kAng != NULL) {
		kAng->angle = (t <= 0.0) ? 0.0 : (t >= 1.0) ? 1.0 : (exponent == 1.0) ? t : pow(t, exponent);
		kAng->units = KAU_turns;
	}
	return kAng;
}
