/*

	quintary.c

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

KLBDC const KOLIBA_EFFILUT KOLIBA_QuintaryColorsF[KQC_COUNT] = {
	{	// red
		1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0
	},
	{	// scarlet
		1.0, 0.0, 0.125, 0.0, 1.0, 0.875, 1.0, 1.0
	},
	{	// vermilion
		1.0, 0.0, 0.25, 0.0, 1.0, 0.75, 1.0, 1.0
	},
	{	// persimmon
		1.0, 0.0, 0.375, 0.0, 1.0, 0.625, 1.0, 1.0
	},
	{	// orange
		1.0, 0.0, 0.5, 0.0, 1.0, 0.5, 1.0, 1.0
	},
	{	// orangepeel
		1.0, 0.0, 0.625, 0.0, 1.0, 0.375, 1.0, 1.0
	},
	{	// amber
		1.0, 0.0, 0.75, 0.0, 1.0, 0.25, 1.0, 1.0
	},
	{	// goldenyellow
		1.0, 0.0, 0.875, 0.0, 1.0, 0.125, 1.0, 1.0
	},
	{	// yellow
		1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0
	},
	{	// lemon
		1.0, 0.0, 1.0, 0.125, 0.875, 0.0, 1.0, 1.0
	},
	{	// lime
		1.0, 0.0, 1.0, 0.25, 0.75, 0.0, 1.0, 1.0
	},
	{	// springbud
		1.0, 0.0, 1.0, 0.375, 0.625, 0.0, 1.0, 1.0
	},
	{	// chartreuse
		1.0, 0.0, 1.0, 0.5, 0.5, 0.0, 1.0, 1.0
	},
	{	// brightgreen
		1.0, 0.0, 1.0, 0.625, 0.375, 0.0, 1.0, 1.0
	},
	{	// harlequin
		1.0, 0.0, 1.0, 0.75, 0.25, 0.0, 1.0, 1.0
	},
	{	// neongreen
		1.0, 0.0, 1.0, 0.875, 0.125, 0.0, 1.0, 1.0
	},
	{	// green
		1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0
	},
	{	// jade
		1.0, 0.125, 1.0, 1.0, 0.0, 0.0, 0.875, 1.0
	},
	{	// erin
		1.0, 0.25, 1.0, 1.0, 0.0, 0.0, 0.75, 1.0
	},
	{	// emerald
		1.0, 0.375, 1.0, 1.0, 0.0, 0.0, 0.625, 1.0
	},
	{	// springgreen
		1.0, 0.5, 1.0, 1.0, 0.0, 0.0, 0.5, 1.0
	},
	{	// mint
		1.0, 0.625, 1.0, 1.0, 0.0, 0.0, 0.375, 1.0
	},
	{	// aquamarine
		1.0, 0.75, 1.0, 1.0, 0.0, 0.0, 0.25, 1.0
	},
	{	// turquoise
		1.0, 0.875, 1.0, 1.0, 0.0, 0.0, 0.125, 1.0
	},
	{	// cyan
		1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0
	},
	{	// skyblue
		1.0, 1.0, 0.875, 1.0, 0.0, 0.125, 0.0, 1.0
	},
	{	// capri
		1.0, 1.0, 0.75, 1.0, 0.0, 0.25, 0.0, 1.0
	},
	{	// cornflower
		1.0, 1.0, 0.625, 1.0, 0.0, 0.375, 0.0, 1.0
	},
	{	// azure
		1.0, 1.0, 0.5, 1.0, 0.0, 0.5, 0.0, 1.0
	},
	{	// cobalt
		1.0, 1.0, 0.375, 1.0, 0.0, 0.625, 0.0, 1.0
	},
	{	// cerulean
		1.0, 1.0, 0.25, 1.0, 0.0, 0.75, 0.0, 1.0
	},
	{	// sapphire
		1.0, 1.0, 0.125, 1.0, 0.0, 0.875, 0.0, 1.0
	},
	{	// blue
		1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0
	},
	{	// iris
		1.0, 1.0, 0.0, 0.875, 0.125, 1.0, 0.0, 1.0
	},
	{	// indigo
		1.0, 1.0, 0.0, 0.75, 0.25, 1.0, 0.0, 1.0
	},
	{	// veronica
		1.0, 1.0, 0.0, 0.625, 0.375, 1.0, 0.0, 1.0
	},
	{	// violet
		1.0, 1.0, 0.0, 0.5, 0.5, 1.0, 0.0, 1.0
	},
	{	// amethyst
		1.0, 1.0, 0.0, 0.375, 0.625, 1.0, 0.0, 1.0
	},
	{	// purple
		1.0, 1.0, 0.0, 0.25, 0.75, 1.0, 0.0, 1.0
	},
	{	// phlox
		1.0, 1.0, 0.0, 0.125, 0.875, 1.0, 0.0, 1.0
	},
	{	// magenta
		1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0
	},
	{	// fuchsia
		1.0, 0.875, 0.0, 0.0, 1.0, 1.0, 0.125, 1.0
	},
	{	// cerise
		1.0, 0.75, 0.0, 0.0, 1.0, 1.0, 0.25, 1.0
	},
	{	// deeppink
		1.0, 0.625, 0.0, 0.0, 1.0, 1.0, 0.375, 1.0
	},
	{	// rose
		1.0, 0.5, 0.0, 0.0, 1.0, 1.0, 0.5, 1.0
	},
	{	// raspberry
		1.0, 0.375, 0.0, 0.0, 1.0, 1.0, 0.625, 1.0
	},
	{	// crimson
		1.0, 0.25, 0.0, 0.0, 1.0, 1.0, 0.75, 1.0
	},
	{	// amaranth
		1.0, 0.125, 0.0, 0.0, 1.0, 1.0, 0.875, 1.0
	},
};

KLBDC const KOLIBA_EFFILUT KOLIBA_QuintaryColorsX[KQC_COUNT] = {
	{	// red
		1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0
	},
	{	// scarlet
		1.0, -1.0, -0.75, -1.0, 1.0, 0.75, 1.0, 1.0
	},
	{	// vermilion
		1.0, -1.0, -0.5, -1.0, 1.0, 0.5, 1.0, 1.0
	},
	{	// persimmon
		1.0, -1.0, -0.25, -1.0, 1.0, 0.25, 1.0, 1.0
	},
	{	// orange
		1.0, -1.0, 0.0, -1.0, 1.0, 0.0, 1.0, 1.0
	},
	{	// orangepeel
		1.0, -1.0, 0.25, -1.0, 1.0, -0.25, 1.0, 1.0
	},
	{	// amber
		1.0, -1.0, 0.5, -1.0, 1.0, -0.5, 1.0, 1.0
	},
	{	// goldenyellow
		1.0, -1.0, 0.75, -1.0, 1.0, -0.75, 1.0, 1.0
	},
	{	// yellow
		1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, 1.0
	},
	{	// lemon
		1.0, -1.0, 1.0, -0.75, 0.75, -1.0, 1.0, 1.0
	},
	{	// lime
		1.0, -1.0, 1.0, -0.5, 0.5, -1.0, 1.0, 1.0
	},
	{	// springbud
		1.0, -1.0, 1.0, -0.25, 0.25, -1.0, 1.0, 1.0
	},
	{	// chartreuse
		1.0, -1.0, 1.0, 0.0, 0.0, -1.0, 1.0, 1.0
	},
	{	// brightgreen
		1.0, -1.0, 1.0, 0.25, -0.25, -1.0, 1.0, 1.0
	},
	{	// harlequin
		1.0, -1.0, 1.0, 0.5, -0.5, -1.0, 1.0, 1.0
	},
	{	// neongreen
		1.0, -1.0, 1.0, 0.75, -0.75, -1.0, 1.0, 1.0
	},
	{	// green
		1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0
	},
	{	// jade
		1.0, -0.75, 1.0, 1.0, -1.0, -1.0, 0.75, 1.0
	},
	{	// erin
		1.0, -0.5, 1.0, 1.0, -1.0, -1.0, 0.5, 1.0
	},
	{	// emerald
		1.0, -0.25, 1.0, 1.0, -1.0, -1.0, 0.25, 1.0
	},
	{	// springgreen
		1.0, 0.0, 1.0, 1.0, -1.0, -1.0, 0.0, 1.0
	},
	{	// mint
		1.0, 0.25, 1.0, 1.0, -1.0, -1.0, -0.25, 1.0
	},
	{	// aquamarine
		1.0, 0.5, 1.0, 1.0, -1.0, -1.0, -0.5, 1.0
	},
	{	// turquoise
		1.0, 0.75, 1.0, 1.0, -1.0, -1.0, -0.75, 1.0
	},
	{	// cyan
		1.0, 1.0, 1.0, 1.0, -1.0, -1.0, -1.0, 1.0
	},
	{	// skyblue
		1.0, 1.0, 0.75, 1.0, -1.0, -0.75, -1.0, 1.0
	},
	{	// capri
		1.0, 1.0, 0.5, 1.0, -1.0, -0.5, -1.0, 1.0
	},
	{	// cornflower
		1.0, 1.0, 0.25, 1.0, -1.0, -0.25, -1.0, 1.0
	},
	{	// azure
		1.0, 1.0, 0.0, 1.0, -1.0, 0.0, -1.0, 1.0
	},
	{	// cobalt
		1.0, 1.0, -0.25, 1.0, -1.0, 0.25, -1.0, 1.0
	},
	{	// cerulean
		1.0, 1.0, -0.5, 1.0, -1.0, 0.5, -1.0, 1.0
	},
	{	// sapphire
		1.0, 1.0, -0.75, 1.0, -1.0, 0.75, -1.0, 1.0
	},
	{	// blue
		1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0
	},
	{	// iris
		1.0, 1.0, -1.0, 0.75, -0.75, 1.0, -1.0, 1.0
	},
	{	// indigo
		1.0, 1.0, -1.0, 0.5, -0.5, 1.0, -1.0, 1.0
	},
	{	// veronica
		1.0, 1.0, -1.0, 0.25, -0.25, 1.0, -1.0, 1.0
	},
	{	// violet
		1.0, 1.0, -1.0, 0.0, 0.0, 1.0, -1.0, 1.0
	},
	{	// amethyst
		1.0, 1.0, -1.0, -0.25, 0.25, 1.0, -1.0, 1.0
	},
	{	// purple
		1.0, 1.0, -1.0, -0.5, 0.5, 1.0, -1.0, 1.0
	},
	{	// phlox
		1.0, 1.0, -1.0, -0.75, 0.75, 1.0, -1.0, 1.0
	},
	{	// magenta
		1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0
	},
	{	// fuchsia
		1.0, 0.75, -1.0, -1.0, 1.0, 1.0, -0.75, 1.0
	},
	{	// cerise
		1.0, 0.5, -1.0, -1.0, 1.0, 1.0, -0.5, 1.0
	},
	{	// deeppink
		1.0, 0.25, -1.0, -1.0, 1.0, 1.0, -0.25, 1.0
	},
	{	// rose
		1.0, 0.0, -1.0, -1.0, 1.0, 1.0, 0.0, 1.0
	},
	{	// raspberry
		1.0, -0.25, -1.0, -1.0, 1.0, 1.0, 0.25, 1.0
	},
	{	// crimson
		1.0, -0.5, -1.0, -1.0, 1.0, 1.0, 0.5, 1.0
	},
	{	// amaranth
		1.0, -0.75, -1.0, -1.0, 1.0, 1.0, 0.75, 1.0
	},
};

KLBDC const KOLIBA_QUINTARYCOLORS KOLIBA_QuintaryColorCount = KQC_COUNT;

KLBDC unsigned int KOLIBA_QuintarySteps(unsigned int ary) {
	if (ary > 5) ary = 5;
	else if (ary == 0) ary = 1;
	return (1 << (5-ary));
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalEfficaciesF(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, KOLIBA_QUINTARYCOLORS index, const KOLIBA_SLUT * const alt) {
	KOLIBA_SLUT const * modifier = (alt != NULL) ? alt : &KOLIBA_Rec2020Slut;
	KOLIBA_QUINTARYCOLORS col = (index < KQC_COUNT) ? index : KQC_red;

	return KOLIBA_ApplyEfficacies(sLut, slt, &KOLIBA_QuintaryColorsF[col], modifier);
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalEfficaciesX(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, KOLIBA_QUINTARYCOLORS index, const KOLIBA_SLUT * const alt) {
	KOLIBA_SLUT const * modifier = (alt != NULL) ? alt : &KOLIBA_Rec2020Slut;
	KOLIBA_QUINTARYCOLORS col = (index < KQC_COUNT) ? index : KQC_red;

	return KOLIBA_ApplyEfficacies(sLut, slt, &KOLIBA_QuintaryColorsX[col], modifier);
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalAngleEfficaciesF(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, double angle, const KOLIBA_SLUT * const alt) {
	KOLIBA_EFFILUT effi;
	KOLIBA_QUINTARYCOLORS e0, e1;
	KOLIBA_SLUT const * modifier = (alt != NULL) ? alt : &KOLIBA_Rec2020Slut;

	// This contraption should return the correct result with any
	// math library regardless of how it calculates the mod of
	// a negative number.
	angle = fmod(360.0 + fmod(angle, 360.0), 360);

	if (angle >= 240.0) {
		angle -= 240.0;
		e0    = KQC_blue;
		e1    = KQC_red;
	}
	else if (angle >= 120.0) {
		angle -=120.0;
		e0     = KQC_green;
		e1     = KQC_blue;
	}
	else {
		e0     = KQC_red;
		e1     = KQC_green;
	}

	return KOLIBA_ApplyEfficacies(sLut, slt, (KOLIBA_EFFILUT *)KOLIBA_Interpolate((double *)&effi, (double *)(KOLIBA_QuintaryColorsF+e0), angle/120.0, (double *)(KOLIBA_QuintaryColorsF+e1), sizeof(KOLIBA_EFFILUT)/sizeof(double)), modifier);
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalAngleEfficaciesX(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, double angle, const KOLIBA_SLUT * const alt) {
	KOLIBA_EFFILUT effi;
	KOLIBA_QUINTARYCOLORS e0, e1;
	KOLIBA_SLUT const * modifier = (alt != NULL) ? alt : &KOLIBA_Rec2020Slut;

	// This contraption should return the correct result with any
	// math library regardless of how it calculates the mod of
	// a negative number.
	angle = fmod(360.0 + fmod(angle, 360.0), 360);

	if (angle >= 240.0) {
		angle -= 240.0;
		e0    = KQC_blue;
		e1    = KQC_red;
	}
	else if (angle >= 120.0) {
		angle -=120.0;
		e0     = KQC_green;
		e1     = KQC_blue;
	}
	else {
		e0     = KQC_red;
		e1     = KQC_green;
	}

	return KOLIBA_ApplyEfficacies(sLut, slt, (KOLIBA_EFFILUT *)KOLIBA_Interpolate((double *)&effi, (double *)(KOLIBA_QuintaryColorsX+e0), angle/120.0, (double *)(KOLIBA_QuintaryColorsX+e1), sizeof(KOLIBA_EFFILUT)/sizeof(double)), modifier);
}
