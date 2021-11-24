/*
	THIS IS STILL UNDER DEVELOPMENT AND MAY BE COMPLETELY REDONE.
	SO PLEASE DO NOT USE IT IN ANY OFFICIAL WAY YET BECAUSE
	YOU WILL ONLY END UP FRUSTRATED.

	libkoliba.i

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

#ifndef	LIBKOLIBA_SWG
#define	LIBKOLIBA_SWG

%module	libkoliba
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

#define	KOLIBA_ABGR32PIXEL	abgr32pixel
#define	KOLIBA_ABGR8PIXEL	abgr8pixel
#define	KOLIBA_ANACHROMA	anachroma
#define	KOLIBA_ARGB32PIXEL	argb32pixel
#define	KOLIBA_ARGB8PIXEL	argb8pixel
#define	KOLIBA_BGRA32PIXEL	bgra32pixel
#define	KOLIBA_BGRA8PIXEL	bgra8pixel
#define	KOLIBA_CFLT	cflt
#define	KOLIBA_CFLT2	cflt2
#define	KOLIBA_CHANNELBLEND	blend
#define	KOLIBA_CHROMA	chroma
#define	KOLIBA_CHROMAT	chromat
#define	KOLIBA_CHROMAT2	chromat2
#define	KOLIBA_COLORMASK	colormask
#define	KOLIBA_CUBE_VERTICES	cubevertices
#define	KOLIBA_DIACHROMA	diachroma
#define	KOLIBA_DICHROMA	dichroma
#define	KOLIBA_DICHROMA2	dichroma2
#define	KOLIBA_EFFILUT	elut
#define	KOLIBA_FFLUT	fflut
#define	KOLIBA_FLBINDEX	flbindex
#define	KOLIBA_FLINDEX	flindex
#define	KOLIBA_FLUT	flut
#define	KOLIBA_FLWINDEX	flwindex
#define	KOLIBA_GEMINIX	geminix
#define	KOLIBA_LDX	ldx
#define	KOLIBA_MALLET	mallet
#define	KOLIBA_MATRIX	matrix
#define	KOLIBA_MATRIX2	matrix2
#define	KOLIBA_PALETTE	palette
#define	KOLIBA_PALETTE2	palette2
#define	KOLIBA_PIGMENT	pigment
#define	KOLIBA_PIXEL	pixel
#define	KOLIBA_PLUT	plut
#define	KOLIBA_RGB	vertex
#define	KOLIBA_RGBA16PIXEL	rgba16pixel
#define	KOLIBA_RGBA32PIXEL	rgba32pixel
#define	KOLIBA_RGBA8PIXEL	rgba8pixel
#define	KOLIBA_ROW	row
#define	KOLIBA_SLUT	slut
#define	KOLIBA_SLUT2	slut2
#define	KOLIBA_VERTICES	vertices
#define	KOLIBA_XYZ	xyz
#define	KOLIBA_XYZBINDEX	xyzbindex
#define	KOLIBA_XYZINDEX	xyzindex
#define	KOLIBA_XYZWINDEX	xyzwindex

#include "koliba.h"
%}

/* Strip KOLIBA_ from function and data names.  */
%rename("%(strip:[KOLIBA_])s") "";
%rename(TwoPi) KOLIBA_2Pi;
%rename(OneEightyDivPi) KOLIBA_180DivPi;
%rename(OneDiv2Pi)	KOLIBA_1Div2Pi;
%rename(OneDiv360)	KOLIBA_1Div360;
%rename(OneDFlutFlags) KOLIBA_1DFlutFlags;
%rename(EightBitBuffer) KOLIBA_8BitBuffer;
%ignore KOLIBA_360;

%ignore KOLIBA_IdentityMallet;
%ignore KOLIBA_TriFarbaF;
%ignore KOLIBA_TriFarbaX;
%ignore KOLIBA_CopyColorToSlutVertices;
%ignore KOLIBA_Ones;
%ignore KOLIBA_NaturalContrastSlut;
%ignore KOLIBA_NaN;

#define	KOLIBA_ABGR32PIXEL	abgr32pixel
#define	KOLIBA_ABGR8PIXEL	abgr8pixel
#define	KOLIBA_ANACHROMA	anachroma
#define	KOLIBA_ARGB32PIXEL	argb32pixel
#define	KOLIBA_ARGB8PIXEL	argb8pixel
#define	KOLIBA_BGRA32PIXEL	bgra32pixel
#define	KOLIBA_BGRA8PIXEL	bgra8pixel
#define	KOLIBA_CFLT	cflt
#define	KOLIBA_CFLT2	cflt2
#define	KOLIBA_CHANNELBLEND	blend
#define	KOLIBA_CHROMA	chroma
#define	KOLIBA_CHROMAT	chromat
#define	KOLIBA_CHROMAT2	chromat2
#define	KOLIBA_COLORMASK	colormask
#define	KOLIBA_CUBE_VERTICES	cubevertices
#define	KOLIBA_DIACHROMA	diachroma
#define	KOLIBA_DICHROMA	dichroma
#define	KOLIBA_DICHROMA2	dichroma2
#define	KOLIBA_EFFILUT	elut
#define	KOLIBA_FFLUT	fflut
#define	KOLIBA_FLBINDEX	flbindex
#define	KOLIBA_FLINDEX	flindex
#define	KOLIBA_FLUT	flut
#define	KOLIBA_FLWINDEX	flwindex
#define	KOLIBA_GEMINIX	geminix
#define	KOLIBA_LDX	ldx
#define	KOLIBA_MALLET	mallet
#define	KOLIBA_MATRIX	matrix
#define	KOLIBA_MATRIX2	matrix2
#define	KOLIBA_PALETTE	palette
#define	KOLIBA_PALETTE2	palette2
#define	KOLIBA_PIGMENT	pigment
#define	KOLIBA_PIXEL	pixel
#define	KOLIBA_PLUT	plut
#define	KOLIBA_RGB	vertex
#define	KOLIBA_RGBA16PIXEL	rgba16pixel
#define	KOLIBA_RGBA32PIXEL	rgba32pixel
#define	KOLIBA_RGBA8PIXEL	rgba8pixel
#define	KOLIBA_ROW	row
#define	KOLIBA_SLUT	slut
#define	KOLIBA_SLUT2	slut2
#define	KOLIBA_VERTICES	vertices
#define	KOLIBA_XYZ	xyz
#define	KOLIBA_XYZBINDEX	xyzbindex
#define	KOLIBA_XYZINDEX	xyzindex
#define	KOLIBA_XYZWINDEX	xyzwindex
%include "koliba.h"


#endif
