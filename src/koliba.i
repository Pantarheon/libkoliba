/*
	THIS IS STILL EXPERIMENTAL AND WILL BE COMPLETELY REDONE.
	SO PLEASE DO NOT USE IT IN ANY OFFICIAL WAY BECAUSE YOU
	WILL ONLY END UP FRUSTRATED.

	THE EVENTUAL MODULE WILL MOST LIKELY BE BASED ON "C++" CLASSES
	RATHER THAN THE PLAIN C LIBRARY.
*/

#ifndef	KOLIBA_SWG
#define	KOLIBA_SWG

%module	koliba
%{
	#include "koliba.h"
%}

%include "koliba.h"
#include <stdbool.h>

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

	void fix(void) {KOLIBA_FixFlut($self);}

	void efficacy(double efficacy) {KOLIBA_FlutEfficacy($self,$self,efficacy);}

	void interpolate(KOLIBA_FLUT *modifier, double rate) {
		KOLIBA_InterpolateFluts($self,$self,rate,modifier);
	}

	KOLIBA_FLAGS flags(void) {return KOLIBA_FlutFlags($self);}

	bool identity(void) {return KOLIBA_IsIdentityFlut($self);}

	void scale(double factor) {KOLIBA_ScaleFlut($self,$self,factor);}

	~_KOLIBA_FLUT() {
		free($self);
	}
}

#endif
