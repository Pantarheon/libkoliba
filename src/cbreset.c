/*

	cbreset.c

	Copyright 2019-2021 G. Adam Stanislav
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
#include <string.h>

#if !defined(NULL)
	#define	NULL	((void*)0)
#endif

// Reset a channel blend to default contents.

KLBDC KOLIBA_CHANNELBLEND * KOLIBA_ResetChannelBlend(KOLIBA_CHANNELBLEND *blend) {
	return (blend == NULL) ? blend : memcpy(blend, &KOLIBA_IdentityChannelBlend, sizeof(KOLIBA_CHANNELBLEND));
}

KLBDC KOLIBA_CHANNELBLEND * KOLIBA_ResetChannelBlendRed(KOLIBA_CHANNELBLEND *blend) {
	if (blend != NULL) {
		memcpy(&blend->mat.Red, &KOLIBA_IdentityMatrix.Red, sizeof(KOLIBA_ROW));
		blend->nr = false;
		if (blend->na) {
			blend->ng = true;
			blend->nb = true;
			blend->na = false;
		}
	}
	return blend;
}

KLBDC KOLIBA_CHANNELBLEND * KOLIBA_ResetChannelBlendGreen(KOLIBA_CHANNELBLEND *blend) {
	if (blend != NULL) {
		memcpy(&blend->mat.Green, &KOLIBA_IdentityMatrix.Green, sizeof(KOLIBA_ROW));
		blend->ng = false;
		if (blend->na) {
			blend->nr = true;
			blend->nb = true;
			blend->na = false;
		}
	}
	return blend;
}

KLBDC KOLIBA_CHANNELBLEND * KOLIBA_ResetChannelBlendBlue(KOLIBA_CHANNELBLEND *blend) {
	if (blend != NULL) {
		memcpy(&blend->mat.Blue, &KOLIBA_IdentityMatrix.Blue, sizeof(KOLIBA_ROW));
		blend->nb = false;
		if (blend->na) {
			blend->nr = true;
			blend->ng = true;
			blend->na = false;
		}
	}
	return blend;
}

