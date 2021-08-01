/*

	spherical.c

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

#define	SPHERICAL_C
#include "koliba.h"
#include <math.h>

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

KLBHID const KOLIBA_EFFILUT KOLIBA_TriFarbaF[3] = {
	{	// red
		1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0
	},
	{	// green
		1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0
	},
	{	// blue
		1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0
	}
};

KLBHID const KOLIBA_EFFILUT KOLIBA_TriFarbaX[3] = {
	{	// red
		1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0
	},
	{	// green
		1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0
	},
	{	// blue
		1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0
	}
};

// These are deprecated and will be removed as unnecessary.
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

static double uhol(double angle, size_t *start, size_t *end) {
	// This contraption should return the correct result with any
	// math library regardless of how it calculates the mod of
	// a negative number.
	angle = fmod(360.0 + fmod(angle, 360.0), 360.0);

	if (angle >= 240.0) {
		angle -= 240.0;
		*start = 2;
		*end   = 0;
	}
	else if (angle >= 120.0) {
		angle -=120.0;
		*start = 1;
		*end   = 2;
	}
	else {
		*start = 0;
		*end   = 1;
	}

	return angle / 120.0;
}

KLBDC KOLIBA_EFFILUT *KOLIBA_SphericalEffilut(KOLIBA_EFFILUT *effi, double angle, double fx) {
	KOLIBA_EFFILUT effiF, effiX;
	size_t start, end;

	angle = uhol(angle, &start, &end);
	return (KOLIBA_EFFILUT *)KOLIBA_Interpolate(
		(double *)effi,
		KOLIBA_Interpolate((double *)&effiX, (double *)(KOLIBA_TriFarbaX+end), angle, (double *)(KOLIBA_TriFarbaX+start), sizeof(KOLIBA_EFFILUT)/sizeof(double)),
		fx,
		KOLIBA_Interpolate((double *)&effiF, (double *)(KOLIBA_TriFarbaF+end), angle, (double *)(KOLIBA_TriFarbaF+start), sizeof(KOLIBA_EFFILUT)/sizeof(double)),
		sizeof(KOLIBA_EFFILUT)/sizeof(double)
	);
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalEfficacies(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, double angle, const KOLIBA_SLUT * const alt, double fx) {
	KOLIBA_EFFILUT effi;

	return KOLIBA_ApplyEfficacies(
		sLut,
		(slt != NULL) ? slt : &KOLIBA_NaturalFarbaContrastSlut,
		KOLIBA_SphericalEffilut(&effi, angle, fx),
		(alt != NULL) ? alt : &KOLIBA_Rec2020Slut
	);
}

// We can combine several of the options along with a few defaults
// for the purpose of using all this in video editing, typically
// using some kind of plug-in (such as OpenFX, but we want to make
// it as flexible as we can). We want the effect to be animatable,
// i.e., to allow the various parameters to change from frame to
// frame of the video. For that, we replace all of them with a
// handful of double arguments.
//
// One of them will allow us to choose the "import" SLUT by
// interpolating between the ILUT and the Natural Farba Contrast
// LUT. Another will allow us not just to use any angle but
// to also choose which of the two EFFILUT tables to use, or
// even anything in-between them (or outside them in extrapolation).
// Last but not least we need a double to determine which
// one (or interpolation of which two) out of three atmosphere
// LUT to use, the three being the Home LUT, the No Farba LUT, and
// the 2020 LUT. Because we may need to pick two out of three,
// this double needs to be circular, so we will use an angle
// in degrees to choose among them. This also allows the user
// to go through all of them repeatedly in succession.
//
// And, we need to offer an efficacy for it all.
//
// We can call the effect a color roller.

KLBDC KOLIBA_SLUT *KOLIBA_ColorRoller(KOLIBA_SLUT *sLut, double imp, double angle, double atmo, double fx, double efficacy) {
	KOLIBA_SLUT slt, alt;
	KOLIBA_EFFILUT effiF, effiX, effi;
	size_t start, end;
	KOLIBA_QUINTARYCOLORS e0, e1;
	const KOLIBA_SLUT *a0, *a1;

	atmo = uhol(atmo, &start, &end);
	a0   = (start == 0) ? &KOLIBA_HomeSlut :
		(start == 1) ? &KOLIBA_Rec2020Slut : &KOLIBA_NoFarbaSlut;
	a1   = (end   == 0) ? &KOLIBA_HomeSlut :
		(end   == 1) ? &KOLIBA_Rec2020Slut : &KOLIBA_NoFarbaSlut;

	return KOLIBA_InterpolateSluts(
		sLut,
		KOLIBA_ApplySphericalEfficacies(
			sLut,
			KOLIBA_InterpolateSluts(
				&slt,
				&KOLIBA_NaturalFarbaContrastSlut,
				-imp,
				&KOLIBA_IdentitySlut
			),
			angle,
			KOLIBA_InterpolateSluts(
				&alt, a1, atmo, a0
			),
			fx
		),
		efficacy,
		&KOLIBA_IdentitySlut
	);
}



// The rest is deprecated and will be removed in libkoliba v1.0.
KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalEfficaciesF(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, KOLIBA_QUINTARYCOLORS index, const KOLIBA_SLUT * const alt) {
	return KOLIBA_ApplySphericalEfficacies(sLut, slt, KOLIBA_SphericalToAngle(index), alt, 0);
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalEfficaciesX(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, KOLIBA_QUINTARYCOLORS index, const KOLIBA_SLUT * const alt) {
	return KOLIBA_ApplySphericalEfficacies(sLut, slt, KOLIBA_SphericalToAngle(index), alt, 1.0);
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalAngleEfficaciesF(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, double angle, const KOLIBA_SLUT * const alt) {
	return KOLIBA_ApplySphericalEfficacies(sLut, slt, angle, alt, 0);
}

KLBDC KOLIBA_SLUT *KOLIBA_ApplySphericalAngleEfficaciesX(KOLIBA_SLUT *sLut, const KOLIBA_SLUT * const slt, double angle, const KOLIBA_SLUT * const alt) {
	return KOLIBA_ApplySphericalEfficacies(sLut, slt, angle, alt, 1.0);
}
