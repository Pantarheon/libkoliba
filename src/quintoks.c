/*

	quintoks.c

	Copyright 2019 G. Adam Stanislav
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
#include <string.h>

KLBDC const char * const KOLIBA_QuintaryColorTokens[KQC_COUNT] = {
	"red",
	"scarlet",
	"vermilion",
	"persimmon",
	"orange",
	"orangepeel",
	"amber",
	"goldenyellow",
	"yellow",
	"lemon",
	"lime",
	"springbud",
	"chartreuse",
	"brightgreen",
	"harlequin",
	"neongreen",
	"green",
	"jade",
	"erin",
	"emerald",
	"springgreen",
	"mint",
	"aquamarine",
	"turquoise",
	"cyan",
	"skyblue",
	"capri",
	"cornflower",
	"azure",
	"cobalt",
	"cerulean",
	"sapphire",
	"blue",
	"iris",
	"indigo",
	"veronica",
	"violet",
	"amethyst",
	"purple",
	"phlox",
	"magenta",
	"fuchsia",
	"cerise",
	"deeppink",
	"rose",
	"raspberry",
	"crimson",
	"amaranth"
};

KLBDC const char * const KOLIBA_QuintaryColorNames[KQC_COUNT] = {
	"Red",
	"Scarlet",
	"Vermilion",
	"Persimmon",
	"Orange",
	"Orange Peel",
	"Amber",
	"Golden Yellow",
	"Yellow",
	"Lemon",
	"Lime",
	"Spring Bud",
	"Chartreuse",
	"Bright Green",
	"Harlequin",
	"Neon Green",
	"Green",
	"Jade",
	"Erin",
	"Emerald",
	"Spring Green",
	"Mint",
	"Aquamarine",
	"Turquoise",
	"Cyan",
	"Sky Blue",
	"Capri",
	"Cornflower",
	"Azure",
	"Cobalt",
	"Cerulean",
	"Sapphire",
	"Blue",
	"Iris",
	"Indigo",
	"Veronica",
	"Violet",
	"Amethyst",
	"Purple",
	"Phlox",
	"Magenta",
	"Fuchsia",
	"Cerise",
	"Deep Pink",
	"Rose",
	"Raspberry",
	"Crimson",
	"Amaranth"
};

KLBDC const KOLIBA_QUINTARYCOLORS KOLIBA_QuintaryColorCount = KQC_COUNT;

KLBDC unsigned int KOLIBA_QuintarySteps(unsigned int ary) {
	if (ary > 5) ary = 5;
	else if (ary == 0) ary = 1;
	return (1 << (5-ary));
}

KLBDC signed int KOLIBA_AngleToQuintaryIndex(double angle) {
	double d = (fmod(360.0+fmod(angle, 360.0), 360.0)*(double)KQC_COUNT)/360.0;
	int    i = (int)d;

	return (d == (double)i) ? i : -1;
}

KLBDC signed int KOLIBA_TokenToQuintaryIndex(const char * const token) {
	unsigned int i;
	for (i = 0; i < KQC_COUNT; i++)
		if (strcmpi(token, KOLIBA_QuintaryColorTokens[i]) == 0)
			return i;
	return -1;
}
