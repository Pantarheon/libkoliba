/*

	flutter.c

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

KLBHID extern const double KOLIBA_Zeroes[24];

// The flutter blend. This operation is vaguely analogous
// to matrix multiplication, but that is not truly defined
// for two 8x3 matrices (which fLuts are).
//
// Nevertheless, it can produce a new effect. So, why not?

KLBDC KOLIBA_FLUT * KOLIBA_Flutter(KOLIBA_FLUT *output, const KOLIBA_FLUT * const modificand, const KOLIBA_FLUT * const modifier) {
	KOLIBA_FLUT fLut;
	double	D, E, F, G, H, I, J, K, L;

	if ((output == NULL) || (modifier == NULL) || (modificand == NULL)) return NULL;

#define	A	(modifier->Black.r)
#define	B	(modifier->Black.g)
#define	C	(modifier->Black.b)

	D = modifier->Red.r;
	E = modifier->Red.g;
	F = modifier->Red.b;

	G = modifier->Green.r;
	H = modifier->Green.g;
	I = modifier->Green.b;

	J = modifier->Blue.r;
	K = modifier->Blue.g;
	L = modifier->Blue.b;

#define	M	(modifier->Yellow.r)
#define	N	(modifier->Yellow.g)
#define	O	(modifier->Yellow.b)

#define	P	(modifier->Magenta.r)
#define	Q	(modifier->Magenta.g)
#define	R	(modifier->Magenta.b)

#define	S	(modifier->Cyan.r)
#define	T	(modifier->Cyan.g)
#define	U	(modifier->Cyan.b)

#define	V	(modifier->White.r)
#define	W	(modifier->White.g)
#define	X	(modifier->White.b)

#define	Z	(*KOLIBA_Zeroes)

#define	ma	(modificand->Black.r)
#define	mb	(modificand->Black.g)
#define	mc	(modificand->Black.b)

#define	md	(modificand->Red.r)
#define	me	(modificand->Red.g)
#define	mf	(modificand->Red.b)

#define	mg	(modificand->Green.r)
#define	mh	(modificand->Green.g)
#define	mi	(modificand->Green.b)

#define	mj	(modificand->Blue.r)
#define	mk	(modificand->Blue.g)
#define	ml	(modificand->Blue.b)

#define	mm	(modificand->Yellow.r)
#define	mn	(modificand->Yellow.g)
#define	mo	(modificand->Yellow.b)

#define	mp	(modificand->Magenta.r)
#define	mq	(modificand->Magenta.g)
#define	mr	(modificand->Magenta.b)

#define	ms	(modificand->Cyan.r)
#define	mt	(modificand->Cyan.g)
#define	mu	(modificand->Cyan.b)

#define	mv	(modificand->White.r)
#define	mw	(modificand->White.g)
#define	mx	(modificand->White.b)

	fLut.Black.r	= A + D*ma + G*mb + J*mc;
	fLut.Black.g	= B + E*ma + H*mb + K*mc;
	fLut.Black.b	= C + F*ma + I*mb + L*mc;

	fLut.Red.r		=     D*md + G*me + J*mf;
	fLut.Red.g		=     E*md + H*me + K*mf;
	fLut.Red.b		=     F*md + I*me + L*mf;

	fLut.Green.r	=     D*mg + G*mh + J*mi;
	fLut.Green.g	=     E*mg + H*mh + K*mi;
	fLut.Green.b	=     F*mg + I*mh + L*mi;

	fLut.Blue.r		=     D*mj + G*mk + J*ml;
	fLut.Blue.g		=     E*mj + H*mk + K*ml;
	fLut.Blue.b		=     F*mj + I*mk + L*ml;

	fLut.Yellow.r	= M + D*mm + G*mn + J*mo;
	fLut.Yellow.g	= N + E*mm + H*mn + K*mo;
	fLut.Yellow.b	= O + F*mm + I*mn + L*mo;

	fLut.Magenta.r	= P + D*mp + G*mq + J*mr;
	fLut.Magenta.g	= Q + E*mp + H*mq + K*mr;
	fLut.Magenta.b	= R + F*mp + I*mq + L*mr;

	fLut.Cyan.r		= S + D*ms + G*mt + J*mu;
	fLut.Cyan.g		= T + E*ms + H*mt + K*mu;
	fLut.Cyan.b		= U + F*ms + I*mt + L*mu;

	fLut.White.r	= V + D*mv + G*mw + J*mx;
	fLut.White.g	= W + E*mv + H*mw + K*mx;
	fLut.White.b	= X + F*mv + I*mw + L*mx;

	return (KOLIBA_FLUT *)memcpy(output, &fLut, sizeof(KOLIBA_FLUT));
}
