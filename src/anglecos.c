/*

	anglecos.c

	Copyright 2021-2022 G. Adam Stanislav
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

KLBDC double KOLIBA_AngleCosine(const KOLIBA_ANGLE * const angle) {
	return cos(KOLIBA_AngleRadians(angle));
}

KLBDC double KOLIBA_AngleFactorCosine(const KOLIBA_ANGLE * const angle, double factor) {
	return cos(KOLIBA_AngleRadians(angle)*factor);
}

KLBDC double KOLIBA_AngleNormalizedCosine(const KOLIBA_ANGLE * const angle) {
	return cos(fmod(KOLIBA_2Pi+fmod(KOLIBA_AngleRadians(angle), KOLIBA_2Pi), KOLIBA_2Pi));
}

KLBDC double KOLIBA_AngleFactorNormalizedCosine(const KOLIBA_ANGLE * const angle, double factor) {
	return cos(fmod(KOLIBA_2Pi+fmod(KOLIBA_AngleRadians(angle), KOLIBA_2Pi), KOLIBA_2Pi)*factor);
}

KLBDC double KOLIBA_AngleMonocycleCosine(const KOLIBA_ANGLE * const angle) {
	return cos(KOLIBA_MonocyclicalAngle(angle));
}

KLBDC double KOLIBA_AngleFactorMonocycleCosine(const KOLIBA_ANGLE * const angle, double factor) {
	return cos(KOLIBA_MonocyclicalAngle(angle)*factor);
}

KLBDC double KOLIBA_AngleCosineSquared(const KOLIBA_ANGLE * const angle) {
	double c = cos(KOLIBA_AngleRadians(angle));
	return c*c;
}
