/*
	THIS IS STILL EXPERIMENTAL AND WILL BE COMPLETELY REDONE.
	SO PLEASE DO NOT USE IT IN ANY OFFICIAL WAY YET BECAUSE
	YOU WILL ONLY END UP FRUSTRATED.

	THE EVENTUAL MODULE WILL MOST LIKELY BE BASED ON "C++" CLASSES
	RATHER THAN THE PLAIN C LIBRARY.

	koliba.i

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

#ifndef	KOLIBA_SWG
#define	KOLIBA_SWG

%module	koliba
%{
	#include "koliba.h"
%}

/* Strip KOLIBA_ from function and data names.  */
/* Though we will "ignore" most functions here. */
%rename("%(strip:[KOLIBA_])s") "";
%rename(TwoPi) KOLIBA_2Pi;
%rename(OneEightyDivPi) KOLIBA_180DivPi;
%rename(OneDiv2Pi)	KOLIBA_1Div2Pi;
%rename(OneDiv360)	KOLIBA_1Div360;
%rename(OneDFlutFlags) KOLIBA_1DFlutFlags;
%rename(EightBitBuffer) KOLIBA_8BitBuffer;
%ignore KOLIBA_360;

/* This code/data is internal to libkoliba and is not exported.      */
/* But it is listed in koliba.h, so we have tell SWIG to ignore it.  */
%ignore KOLIBA_IdentityMallet;
%ignore KOLIBA_TriFarbaF;
%ignore KOLIBA_TriFarbaX;
%ignore KOLIBA_CopyColorToSlutVertices;
%ignore KOLIBA_Ones;
%ignore KOLIBA_NaturalContrastSlut;
%ignore KOLIBA_Rec2020Slut;
%ignore KOLIBA_NaN;

/* Do not make low-level code directly accessible outside any class. */
%ignore KOLIBA_ConvertSlutToFlut;
%ignore KOLIBA_ConvertMatrixToFlut;
%ignore KOLIBA_FixFlut;
%ignore KOLIBA_FlutEfficacy;
%ignore KOLIBA_InterpolateFluts;
%ignore KOLIBA_FlutFlags;
%ignore KOLIBA_IsIdentityFlut;
%ignore KOLIBA_ScaleFlut;
%ignore KOLIBA_MonoFarbaToFlut;
%ignore KOLIBA_ConvertGrayToFlut;
%ignore KOLIBA_ConvertRgbToFlut;
%ignore KOLIBA_FlutIsMatrix;
%ignore KOLIBA_Flutter;
%ignore KOLIBA_ConvertChannelBlendToFlut;
%ignore KOLIBA_ConvertChromaMatrixToFlut;
%ignore KOLIBA_ConvertChromatToFlut;
%ignore KOLIBA_ConvertDichromaticMatrixToFlut;
%ignore KOLIBA_ConvertAnachromaticMatrixToFlut;

%include "koliba.h"
#include <stdbool.h>

/* Convert the _KOLIBA_FLUT structure into a class. */
%extend _KOLIBA_FLUT {
	_KOLIBA_FLUT(KOLIBA_FLUT *fLut = &KOLIBA_IdentityFlut) {
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		memcpy(f, fLut, sizeof(KOLIBA_FLUT));
		return f;
	}

	_KOLIBA_FLUT(KOLIBA_SLUT *sLut) {
		KOLIBA_VERTICES v;
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertSlutToFlut(f,KOLIBA_SlutToVertices(&v,sLut));
	}

	_KOLIBA_FLUT(KOLIBA_VERTICES *vertices) {
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertSlutToFlut(f,vertices);
	}

	_KOLIBA_FLUT(KOLIBA_MATRIX *matrix) {
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertMatrixToFlut(f,matrix);
	}

	_KOLIBA_FLUT(KOLIBA_CHANNELBLEND *blend) {
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertChannelBlendToFlut(f,blend);
	}

	_KOLIBA_FLUT(const KOLIBA_CHROMA * chroma, const KOLIBA_RGB * model) {
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertChromaMatrixToFlut(f,chroma,model);
	}

	_KOLIBA_FLUT(const KOLIBA_CHROMAT *chromat) {
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertChromatToFlut(f,chromat);
	}

	_KOLIBA_FLUT(const KOLIBA_DICHROMA *dichroma, bool normalize=false, unsigned int channel=0) {
		KOLIBA_MATRIX mat;
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertMatrixToFlut(f, KOLIBA_DichromaticMatrix(&mat, dichroma, normalize, channel%3));
	}

	_KOLIBA_FLUT(const KOLIBA_ANACHROMA *anachroma, bool normalize=false, unsigned int channel=0) {
		KOLIBA_MATRIX mat;
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertMatrixToFlut(f, KOLIBA_AnachromaticMatrix(&mat, anachroma, normalize, channel%3));
	}

	void fix(void) {KOLIBA_FixFlut($self);}
	void efficacy(double efficacy) {KOLIBA_FlutEfficacy($self,$self,efficacy);}

	void interpolate(KOLIBA_FLUT *modifier, double rate) {
		KOLIBA_InterpolateFluts($self,$self,rate,modifier);
	}

	KOLIBA_FLAGS flags(void) {return KOLIBA_FlutFlags($self);}
	bool isidentity(void) {return KOLIBA_IsIdentityFlut($self);}
	void scale(double factor) {KOLIBA_ScaleFlut($self,$self,factor);}

	void monofarba(const KOLIBA_RGB * gray, double primary, double secondary, uint8_t flags) {
		KOLIBA_MonoFarbaToFlut($self,gray,primary,secondary,flags);
	}

	void redmonofarba(void) {
		KOLIBA_SLUT sLut;
		KOLIBA_VERTICES vert;

		KOLIBA_SlutToVertices(&vert, KOLIBA_MonoFarbaToSlut(&sLut, NULL, 1.25, -0.25, KOLIBA_SLUTRED));
		KOLIBA_ConvertSlutToFlut($self,&vert);
	}

	void gray(const KOLIBA_RGB * const gray=NULL) {KOLIBA_ConvertGrayToFlut($self,gray);}
	void color(const KOLIBA_RGB * const color=NULL) {KOLIBA_ConvertRgbToFlut($self,color);}
	bool ismatrix(void) {return KOLIBA_FlutIsMatrix($self);}

	void flutter(const KOLIBA_FLUT * const modifier) {
		KOLIBA_Flutter($self, $self, modifier);
	}

	~_KOLIBA_FLUT() {
		free($self);
	}
}

#endif
