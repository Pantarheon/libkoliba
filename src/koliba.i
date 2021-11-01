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

/*
	The #defines inside the module change the names of the C structs
	into the names of the classes available in whatever scripting
	language we use this for. They affect the output of the
	C preprocessor.

	They must appear before the #include, and they must be repeated
	exactly the same before the %include outside the module statement.
	That way the redefinition is applied both, here in the SWIG source
	code and in the koliba_wrap.c file SWIG produces.

	The %renames, on the other hand, are processed by SWIG, not by
	the C preprocessor.
*/
%module	koliba
%{
/*

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

#define	KOLIBA_FLUT	flut
#define	KOLIBA_SLUT	slut
#define	KOLIBA_PLUT	plut
#define KOLIBA_EFFILUT elut
#define KOLIBA_VERTICES vertices
#define KOLIBA_RGB	vertex

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
%ignore KOLIBA_GetStringDataFormat;

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
%ignore KOLIBA_ConvertDiachromaticMatrixToFlut;
%ignore KOLIBA_ApplyPureErythropy;

%ignore KOLIBA_FixSlut;
%ignore KOLIBA_SlutEfficacy;
%ignore KOLIBA_InterpolateSluts;
%ignore KOLIBA_InterpolateSlutVertices;
%ignore KOLIBA_ApplyEfficacies;
%ignore KOLIBA_SlutEfficacy;
%ignore KOLIBA_ApplyNaturalContrasts;
%ignore KOLIBA_SetEfficacies;
%ignore KOLIBA_SetDualEfficacies;
%ignore KOLIBA_ColorRoller;
%ignore KOLIBA_ApplySphericalEfficacies;
%ignore KOLIBA_SetFarbosity;
%ignore KOLIBA_IsIdentitySlut;
%ignore KOLIBA_ConvertFlutToSlut;
%ignore KOLIBA_ConvertPlutToSlut;
%ignore KOLIBA_VerticesToSlut;
%ignore KOLIBA_SlutIs1D;
%ignore KOLIBA_SlutSelect;
%ignore KOLIBA_InvertSlutVertices;
%ignore KOLIBA_ApplyGainToSlutVertices;
%ignore KOLIBA_ApplyLiftToSlutVertices;
%ignore KOLIBA_AddOffsetToSlutVertices;
%ignore KOLIBA_SlutToString;
%ignore KOLIBA_StringToSlut;
%ignore KOLIBA_ApplyEfficacyToSlutVertices;
%ignore KOLIBA_ApplyContrastToSlutVertices;
%ignore KOLIBA_ConvertGrayToFlut;
%ignore KOLIBA_ConvertRgbToSlut;
%ignore	KOLIBA_ResetSlut;
%ignore KOLIBA_DiscardSlutSvit;
%ignore KOLIBA_DiscardSlutFarba;
%ignore KOLIBA_ResetSlutBlack;
%ignore KOLIBA_ResetSlutBlue;
%ignore KOLIBA_ResetSlutGreen;
%ignore KOLIBA_ResetSlutCyan;
%ignore KOLIBA_ResetSlutRed;
%ignore KOLIBA_ResetSlutMagenta;
%ignore KOLIBA_ResetSlutYellow;
%ignore KOLIBA_ResetSlutWhite;
%ignore KOLIBA_ConvertMatrixToSlut;
%ignore KOLIBA_SlutIsMatrix;
%ignore KOLIBA_MultiplySluts;
%ignore KOLIBA_ConvertChannelBlendToSlut;
%ignore KOLIBA_ConvertChromaMatrixToSlut;
%ignore KOLIBA_ConvertChromatToSlut;
%ignore KOLIBA_ConvertDichromaticMatrixToSlut;
%ignore KOLIBA_ConvertAnachromaticMatrixToSlut;
%ignore KOLIBA_ConvertDiachromaticMatrixToSlut;
%ignore KOLIBA_ConvertPaletteToSlut;
%ignore KOLIBA_ApplyErythropy;
%ignore KOLIBA_ConvertMalletToSlut;
%ignore KOLIBA_MultiplyMalletsToSlut;
%ignore KOLIBA_ConvertMalletsToSlut;
%ignore KOLIBA_ConvertColorFilterToSlut;
%ignore KOLIBA_ApplyStrutRing;
%ignore KOLIBA_ReadSlutFromCompatibleNamedFile;
%ignore KOLIBA_WriteSlutToNamedFile;
%ignore KOLIBA_ReadSlutFromNamedFile;
%ignore KOLIBA_WriteSlttToNamedFile;
%ignore KOLIBA_ReadSlttFromNamedFile;

%ignore KOLIBA_VerticesIsMatrix;

#define	KOLIBA_FLUT	flut
#define	KOLIBA_SLUT	slut
#define	KOLIBA_PLUT	plut
#define KOLIBA_EFFILUT elut
#define KOLIBA_VERTICES vertices
#define KOLIBA_RGB	vertex

%include "koliba.h"
#include <stdbool.h>

%inline %{
	KOLIBA_ftype stringFormat(char *string) {
		KOLIBA_ftype ftype = KOLIBA_GetStringDataFormat(string);
		return (ftype <= KOLIBA_ftunknown) ? KOLIBA_ftnoslut : ftype;
	}
%}

/* Convert the _KOLIBA_FLUT structure into class koliba.flut(). */

%extend _KOLIBA_FLUT {
	_KOLIBA_FLUT(KOLIBA_FLUT *fLut = &KOLIBA_IdentityFlut) {
		return (fLut == NULL) ? NULL :
			(KOLIBA_FLUT *)memcpy(malloc(sizeof(KOLIBA_FLUT)), fLut, sizeof(KOLIBA_FLUT));
	}

	_KOLIBA_FLUT(KOLIBA_SLUT *sLut) {
		KOLIBA_VERTICES v;

		return (sLut == NULL) ? NULL :
			KOLIBA_ConvertSlutToFlut(malloc(sizeof(KOLIBA_FLUT)),KOLIBA_SlutToVertices(&v,sLut));
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

	_KOLIBA_FLUT(const KOLIBA_CHROMA * chroma, const KOLIBA_RGB * model=&KOLIBA_Rec2020) {
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

	_KOLIBA_FLUT(const KOLIBA_DIACHROMA *diachroma, bool normalize=false) {
		KOLIBA_MATRIX mat;
		KOLIBA_FLUT *f = malloc(sizeof(KOLIBA_FLUT));
		return KOLIBA_ConvertMatrixToFlut(f, KOLIBA_DiachromaticMatrix(&mat, diachroma, normalize));
	}

	// Convert FLUT to a text string.
	char *__str__() {
		static char s[1024];
		sprintf(s,
			"fLut   [\n"
			"black   [%g, %g, %g]\n"
			"red     [%g, %g, %g]\n"
			"green   [%g, %g, %g]\n"
			"blue    [%g, %g, %g]\n"
			"yellow  [%g, %g, %g]\n"
			"magenta [%g, %g, %g]\n"
			"cyan    [%g, %g, %g]\n"
			"white   [%g, %g, %g]\n"
			"       ]",
			$self->black.r, $self->black.g, $self->black.b,
			$self->red.r, $self->red.g, $self->red.b,
			$self->green.r, $self->green.g, $self->green.b,
			$self->blue.r, $self->blue.g, $self->blue.b,
			$self->yellow.r, $self->yellow.g, $self->yellow.b,
			$self->magenta.r, $self->magenta.g, $self->magenta.b,
			$self->cyan.r, $self->cyan.g, $self->cyan.b,
			$self->white.r, $self->white.g, $self->white.b
		);
		return s;
	}

	void fix(void) {$self=KOLIBA_FixFlut($self);}
	void efficacy(double efficacy) {$self=KOLIBA_FlutEfficacy($self,$self,efficacy);}

	void interpolate(KOLIBA_FLUT *modifier, double rate) {
		$self=KOLIBA_InterpolateFluts($self,$self,rate,modifier);
	}

	KOLIBA_FLAGS flags(void) {return KOLIBA_FlutFlags($self);}
	bool isidentity(void) {return KOLIBA_IsIdentityFlut($self);}
	void scale(double factor) {$self=KOLIBA_ScaleFlut($self,$self,factor);}

	void monofarba(const KOLIBA_RGB * gray, double primary, double secondary, uint8_t flags) {
		$self=KOLIBA_MonoFarbaToFlut($self,gray,primary,secondary,flags);
	}

	void redmonofarba(void) {
		KOLIBA_SLUT sLut;
		KOLIBA_VERTICES vert;

		KOLIBA_SlutToVertices(&vert, KOLIBA_MonoFarbaToSlut(&sLut, NULL, 1.25, -0.25, KOLIBA_SLUTRED));
		$self=KOLIBA_ConvertSlutToFlut($self,&vert);
	}

	void gray(const KOLIBA_RGB * const gray=NULL) {$self=KOLIBA_ConvertGrayToFlut($self,gray);}
	void color(const KOLIBA_RGB * const color=NULL) {$self=KOLIBA_ConvertRgbToFlut($self,color);}
	bool ismatrix(void) {return KOLIBA_FlutIsMatrix($self);}

	void cluster(const KOLIBA_FLUT * const modifier) {
		$self=KOLIBA_Flutter($self, $self, modifier);
	}

	void purery(const KOLIBA_VERTEX * const red=NULL) {
		$self=KOLIBA_ApplyPureErythropy($self, (red) ? red : (KOLIBA_VERTEX *)&($self->red));
	}

	~_KOLIBA_FLUT() {
		free($self);
	}
}

/* Convert the _KOLIBA_SLUT structure into class koliba.slut(). */

%extend _KOLIBA_SLUT {
	_KOLIBA_SLUT(KOLIBA_SLUT *sLut = &KOLIBA_IdentitySlut) {
		return (sLut == NULL) ? NULL :
			(KOLIBA_SLUT *)memcpy(malloc(sizeof(KOLIBA_SLUT)),sLut, sizeof(KOLIBA_SLUT));
	}

	_KOLIBA_SLUT(KOLIBA_SLUT *sLut, double efficacy) {
		return (sLut == NULL) ? NULL :
			(KOLIBA_SLUT *)KOLIBA_SlutEfficacy(malloc(sizeof(KOLIBA_SLUT)), sLut, efficacy);
	}

	_KOLIBA_SLUT(
		double import,
		double angle=225.0,
		double atmosphere=0.0,
		double fx=-0.5,
		double efficacy=1.0
	) {
		KOLIBA_SLUT *s = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ColorRoller(s, import, angle, atmosphere, fx, efficacy);
	}

	_KOLIBA_SLUT(KOLIBA_FLUT *fLut) {
		return (fLut == NULL) ? NULL :
			KOLIBA_ConvertFlutToSlut(malloc(sizeof(KOLIBA_SLUT)), fLut);
	}

	_KOLIBA_SLUT(KOLIBA_PLUT *pLut) {
		KOLIBA_SLUT *s = malloc(sizeof(KOLIBA_SLUT));
		if (KOLIBA_ConvertPlutToSlut(s, pLut))
			return s;
		free(s);
		return NULL;
	}

	_KOLIBA_SLUT(KOLIBA_VERTICES *vertices) {
		// This works even if vertices == NULL.
		return KOLIBA_VerticesToSlut(malloc(sizeof(KOLIBA_SLUT)), vertices);
	}

	_KOLIBA_SLUT(KOLIBA_MATRIX *matrix) {
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		if (KOLIBA_ConvertMatrixToSlut(sLut, matrix))
			return sLut;
		free (sLut);
		return NULL;
	}

	_KOLIBA_SLUT(KOLIBA_CHANNELBLEND *blend) {
		KOLIBA_SLUT *f = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ConvertChannelBlendToSlut(f,blend);
	}

	_KOLIBA_SLUT(const KOLIBA_CHROMA * chroma, const KOLIBA_RGB * model=&KOLIBA_Rec2020) {
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ConvertChromaMatrixToSlut(sLut,chroma,model);
	}

	_KOLIBA_SLUT(const KOLIBA_CHROMAT *chromat) {
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ConvertChromatToSlut(sLut,chromat);
	}

	_KOLIBA_SLUT(const KOLIBA_DICHROMA *dichroma, bool normalize=false, unsigned int channel=0) {
		KOLIBA_MATRIX mat;
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ConvertMatrixToSlut(sLut, KOLIBA_DichromaticMatrix(&mat, dichroma, normalize, channel%3));
	}

	_KOLIBA_SLUT(const KOLIBA_ANACHROMA *anachroma, bool normalize=false, unsigned int channel=0) {
		KOLIBA_MATRIX mat;
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ConvertMatrixToSlut(sLut, KOLIBA_AnachromaticMatrix(&mat, anachroma, normalize, channel%3));
	}

	_KOLIBA_SLUT(const KOLIBA_DIACHROMA *diachroma, bool normalize=false) {
		KOLIBA_MATRIX mat;
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ConvertMatrixToSlut(sLut, KOLIBA_DiachromaticMatrix(&mat, diachroma, normalize));
	}

	_KOLIBA_SLUT(const KOLIBA_PALETTE *palette) {
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		if (KOLIBA_ConvertPaletteToSlut(sLut, palette)) return sLut;
		free (sLut);
		return NULL;
	}

	_KOLIBA_SLUT(const KOLIBA_MALLET *mallet, const KOLIBA_RGB *gray=NULL) {
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		return KOLIBA_ConvertMalletToSlut(sLut,NULL,mallet,gray);
	}

	_KOLIBA_SLUT(const KOLIBA_CFLT *colorFilter) {
		if (colorFilter == NULL) return NULL;
		return KOLIBA_ConvertColorFilterToSlut(malloc(sizeof(KOLIBA_SLUT)),colorFilter);
	}

	_KOLIBA_SLUT(const KOLIBA_VERTEX *ring, KOLIBA_Pluts plut=KOLIBA_PlutRed, double strut=1.0) {
		return (ring==NULL) ? NULL : KOLIBA_ApplyStrutRing(malloc(sizeof(KOLIBA_SLUT)),ring,plut,strut);
	}

	_KOLIBA_SLUT(char *filename) {
		KOLIBA_SLUT *sLut = malloc(sizeof(KOLIBA_SLUT));
		if ((sLut) &&
			(KOLIBA_ReadSlutFromCompatibleNamedFile(sLut, filename, NULL) == NULL)) {
				free(sLut);
				return NULL;
		}
		return sLut;
	}

	// Convert SLUT to a marshaling string.
	char *marshal(void) {
		static char string[SLTAMINCHARS];
		return KOLIBA_SlutToString(string, $self, SLTAMINCHARS);
	}

	// Convert a marshaling` string to sLut
	bool marshal(char *m) {
		KOLIBA_SLUT s;
		if (KOLIBA_MarshalSlutFromCompatibleString(&s, m, NULL) == NULL) return false;
		memcpy($self, &s, sizeof(KOLIBA_SLUT));
		return true;
	}

	// Convert SLUT to a text string.
	char *__str__() {
		static char s[1024];
		sprintf(s,
			"sLut   [\n"
			"black   [%g, %g, %g]\n"
			"blue    [%g, %g, %g]\n"
			"green   [%g, %g, %g]\n"
			"cyan    [%g, %g, %g]\n"
			"red     [%g, %g, %g]\n"
			"magenta [%g, %g, %g]\n"
			"yellow  [%g, %g, %g]\n"
			"white   [%g, %g, %g]\n"
			"       ]",
			$self->black.r, $self->black.g, $self->black.b,
			$self->blue.r, $self->blue.g, $self->blue.b,
			$self->green.r, $self->green.g, $self->green.b,
			$self->cyan.r, $self->cyan.g, $self->cyan.b,
			$self->red.r, $self->red.g, $self->red.b,
			$self->magenta.r, $self->magenta.g, $self->magenta.b,
			$self->yellow.r, $self->yellow.g, $self->yellow.b,
			$self->white.r, $self->white.g, $self->white.b
		);
		return s;
	}

	void fix(void) {KOLIBA_FixSlut($self);}
	void efficacy(double efficacy) {KOLIBA_SlutEfficacy($self,$self,efficacy);}

	void interpolate(KOLIBA_SLUT *modifier, double rate=0.5) {
		KOLIBA_InterpolateSluts($self,$self,rate,modifier);
	}

	void interpolate(KOLIBA_SLUT *source, KOLIBA_SLUT *modifier, double rate=0.5) {
		KOLIBA_InterpolateSluts($self,source,rate,modifier);
	}

	void interpolate(KOLIBA_SLUT *modifier, unsigned char flags, double rate=0.5) {
		KOLIBA_InterpolateSlutVertices($self,$self,modifier,rate,flags);
	}

	void interpolate(KOLIBA_SLUT *source, KOLIBA_SLUT *modifier, unsigned char flags, double rate=0.5) {
		KOLIBA_InterpolateSlutVertices($self,source,modifier,rate,flags);
	}

	void interpolate(KOLIBA_SLUT *modifier, KOLIBA_EFFILUT *efficacies) {
		KOLIBA_ApplyEfficacies($self,$self,efficacies,modifier);
	}

	void interpolate(KOLIBA_SLUT *source, KOLIBA_SLUT *modifier, KOLIBA_EFFILUT *efficacies) {
		KOLIBA_ApplyEfficacies($self,source,efficacies,modifier);
	}

	void efficacy(double efficacy) {KOLIBA_SlutEfficacy($self,$self,efficacy);}

	void efficacy(double efficacy, unsigned char flags) {
		KOLIBA_InterpolateSlutVertices(
			$self, $self,
			&KOLIBA_IdentitySlut,
			efficacy,
			flags
		);
	}

	void natcon(const KOLIBA_EFFILUT * const efficacies) {
		KOLIBA_ApplyNaturalContrasts($self, efficacies);
	}

	void natcon(double efficacy) {
		KOLIBA_EFFILUT efficacies;
		KOLIBA_SetEfficacies(&efficacies, efficacy);
		KOLIBA_ApplyNaturalContrasts($self, &efficacies);
	}

	void natcon(double cmyk, double rgbw) {
		KOLIBA_EFFILUT efficacies;
		KOLIBA_SetDualEfficacies(&efficacies, cmyk, rgbw);
		KOLIBA_ApplyNaturalContrasts($self, &efficacies);
	}

	void colorRoller(
		double import=0.5,
		double angle=225.0,
		double atmosphere=0.0,
		double fx=-0.5,
		double efficacy=1.0
	)
	{
		KOLIBA_ColorRoller($self, import, angle, atmosphere, fx, efficacy);
	}

	void spherical(
		double angle=0.0,
		 const KOLIBA_SLUT * const atmosphere = NULL,
		 double fx = 0.0
	)
	{
		KOLIBA_ApplySphericalEfficacies($self,$self,angle,atmosphere,fx);
	}

	void farbosity(double center=0.5, double width=1.0) {
		KOLIBA_SetFarbosity($self, center, width);
	}

	bool isidentity(void) {return(KOLIBA_IsIdentitySlut($self));}
	bool is1d(void) {return KOLIBA_SlutIs1D($self);}

	void copy(const KOLIBA_SLUT *const lut, unsigned char flags=KOLIBA_SLUTALL) {
		KOLIBA_SlutSelect($self,lut,flags);
	}

	void invert(unsigned char flags=KOLIBA_SLUTALL) {
		KOLIBA_InvertSlutVertices($self,flags);
	}

	void gain(double gain, unsigned char flags=KOLIBA_SLUTALL) {
		KOLIBA_ApplyGainToSlutVertices($self, flags, gain);
	}

	void lift(double lift, unsigned char flags=KOLIBA_SLUTALL) {
		KOLIBA_ApplyLiftToSlutVertices($self, flags, lift);
	}

	void offset(double offset, unsigned char flags=KOLIBA_SLUTALL) {
		KOLIBA_AddOffsetToSlutVertices($self, flags, offset);
	}

	void contrast(
		double contrast,
		unsigned char flags=KOLIBA_SLUTSVIT,
		KOLIBA_SLUT *centers=&KOLIBA_ContrastSlut
	) {KOLIBA_ApplyContrastToSlutVertices($self,centers,flags,contrast);}

	void KOLIBA_ApplySaturationToSlutVertices(
		double saturation,
		unsigned char flags=KOLIBA_SLUTFARBA,
		KOLIBA_RGB *gray=NULL
	) {
		KOLIBA_SLUT temp;
		KOLIBA_ApplySaturationToSlutVertices(
			$self,
			(gray==NULL)?&KOLIBA_Rec2020Slut:KOLIBA_ConvertGrayToSlut(&temp,gray),
			flags,
			saturation
		);
	}

	void monofarba(const KOLIBA_RGB * gray, double primary, double secondary, uint8_t flags) {
		$self=KOLIBA_MonoFarbaToSlut($self,gray,primary,secondary,flags);
	}

	void redmonofarba(void) {
		KOLIBA_MonoFarbaToSlut($self, NULL, 1.25, -0.25, KOLIBA_SLUTRED);
	}

	void gray(const KOLIBA_RGB * const gray=NULL) {KOLIBA_ConvertGrayToSlut($self,gray);}
	void color(const KOLIBA_RGB * const color=NULL) {KOLIBA_ConvertRgbToSlut($self,color);}

	void reset(void) {KOLIBA_ResetSlut($self);}
	void resetSvit(void) {KOLIBA_DiscardSlutSvit($self,$self);}
	void resetFarba(void) {KOLIBA_DiscardSlutFarba($self,$self);}
	void resetBlack(void) {KOLIBA_ResetSlutBlack($self);}
	void resetBlue(void) {KOLIBA_ResetSlutBlue($self);}
	void resetCyan(void) {KOLIBA_ResetSlutCyan($self);}
	void resetRed(void) {KOLIBA_ResetSlutRed($self);}
	void resetMagenta(void) {KOLIBA_ResetSlutMagenta($self);}
	void resetYellow(void) {KOLIBA_ResetSlutYellow($self);}
	void resetWhite(void) {KOLIBA_ResetSlutWhite($self);}
	bool ismatrix(void) {return KOLIBA_SlutIsMatrix($self);}

	void cluster(const KOLIBA_SLUT * const modifier) {
		$self=KOLIBA_MultiplySluts($self, $self, modifier);
	}

	void erythropy(void) {KOLIBA_ApplyErythropy($self,$self);}

	void mallet(const KOLIBA_MALLET *mallet, const KOLIBA_RGB *gray=NULL) {
		KOLIBA_ConvertMalletToSlut($self,$self,mallet,gray);
	}

	void mallets(
		const KOLIBA_MALLET *mallets,
		unsigned int count,
		const KOLIBA_RGB *gray=NULL,
		bool cluster=true
	) {
		if (cluster) KOLIBA_MultiplyMalletsToSlut($self,$self,mallets,gray,count);
		else KOLIBA_ConvertMalletsToSlut($self,$self,mallets,gray,count);
	}

	bool checksum(double sum) {return KOLIBA_CheckSlut($self,sum);}
	bool write(char *filename) {return (KOLIBA_WriteSlutToNamedFile($self,filename)==0);}
	bool read(char *filename) {return(KOLIBA_ReadSlutFromNamedFile($self,filename)!=NULL);}
	bool marshalWrite(char *filename) {return(KOLIBA_WriteSlttToNamedFile($self,filename)==0);}
	bool marshalRead(char *filename) {return(KOLIBA_ReadSlttFromNamedFile($self,filename)!=NULL);}

	~_KOLIBA_SLUT() {
		free($self);
	}
}

/* Convert the _KOLIBA_VERTICES structure into class koliba.vertices(). */

%extend _KOLIBA_VERTICES {
	_KOLIBA_VERTICES(KOLIBA_SLUT *sLut=&KOLIBA_IdentitySlut) {
		return KOLIBA_SlutToVertices(malloc(sizeof(KOLIBA_VERTICES)),sLut);
	}

	bool ismatrix(void) {return KOLIBA_VerticesIsMatrix($self);}

	~_KOLIBA_VERTICES() {
		free($self);
	}
}

/* Convert the _KOLIBA_RGB structure into class koliba.vertex(). */

%extend _KOLIBA_RGB {
	_KOLIBA_RGB(KOLIBA_RGB *vertex=NULL) {
		return (vertex) ? memcpy(malloc(sizeof(KOLIBA_RGB)),vertex,sizeof(KOLIBA_RGB)) :
		calloc(1, sizeof(KOLIBA_RGB));
	}

	_KOLIBA_RGB(double red, double green, double blue) {
		KOLIBA_RGB *v = malloc(sizeof(KOLIBA_RGB));
		v->r = red;
		v->g = green;
		v->b = blue;
		return(v);
	}

	void set(double r, double g, double b) {
		$self->r = r;
		$self->g = g;
		$self->b = b;
	}

	char *__str__() {
		static char s[128];
		sprintf(s, "rgb[%g, %g, %g]", $self->r, $self->g, $self->b);
		return s;
	}

	~_KOLIBA_RGB() {
		free($self);
	}
}

#endif
