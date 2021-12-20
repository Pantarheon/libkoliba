#	Copyright 2019-2021 G. Adam Stanislav
#	All rights reserved
#
#	Redistribution and use in source and binary forms,
#	with or without modification, are permitted provided
#	that the following conditions are met:
#
#	1. Redistributions of source code must retain the
#	above copyright notice, this list of conditions
#	and the following disclaimer.
#
#	2. Redistributions in binary form must reproduce the
#	above copyright notice, this list of conditions and
#	the following disclaimer in the documentation and/or
#	other materials provided with the distribution.
#
#	3. Neither the name of the copyright holder nor the
#	names of its contributors may be used to endorse or
#	promote products derived from this software without
#	specific prior written permission.
#
#	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS
#	AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
#	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#	SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
#	OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#	PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
#	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Use this makefile to create a static Windows library (koliba.lib)
# compiled by the Microsoft C compiler.

CC=cl
CFLG=-Ox -DNOKLIBLIB
CFLAGS=$(CFLG)

objects = 8bitbuff.obj abgr8xyz.obj anachroma.obj anglearea.o anglecos.obj angledeg.obj \
	anglenorm.o anglepi.obj anglerad.obj \
	angleset.obj anglesin.obj angleturn.obj apppx.obj appxyz.obj argb8xyz.obj \
	bgra32xyz.obj bgra8xyz.obj bindbxyz.obj bindoxyz.obj bindwxyz.obj bindxyz.obj \
	byte255.obj calcsum.obj cb2mat.obj \
	cbreset.obj cbsfmt.obj cbstr.obj cflthead.obj checksum.obj \
	chrmhead.obj chrmreset.obj chrmsfmt.obj chroma.obj \
	chrreset.obj chrtstr.obj cmyx.obj colmask.obj contrasts.obj \
	dblsrgb.obj deffiset.obj diachroma.obj dichroma.obj dicrhead.obj effiflut.obj \
	effilut.obj effinc.obj effinv.obj effiset.obj effislut.obj erythropia.obj \
	externpx.obj externxyz.obj \
	farbsity.obj fflut.obj file.obj findex.obj fixdbl.obj fixslut.obj \
	flbinflut.obj flinflut.obj fltcube.obj fltismat.obj fltscale.obj fltscube.obj flutms.obj \
	flutslut.obj flutter.obj flwinflut.obj flyxyz.obj frange.obj fund.obj gainslut.obj \
	gamma.obj gcomp.obj getdtafmt.obj getstrfmt.obj gmnxfmt.obj gmnxstr.obj \
	gray2flut.obj gray2slut.obj gsmat.obj homeslut.obj \
	idchr.obj idmallet.obj idmat.obj \
	idplt.obj idplut.obj idsfac.obj idslut.obj indbxyz.obj indcxyz.obj indoxyz.obj indwxyz.obj indxyz.obj interflut.obj \
	intermat.obj interpol.obj interslt.obj intslut.obj \
	invmat.obj invslut.obj isidflut.obj isidslut.obj \
	kplthead.obj kpltsfmt.obj ldxapply.obj ldxhead.obj ldxxyz.obj \
	libver.obj liftslut.obj linsrgb.obj m34str.obj m3x4head.obj m3x4sfmt.obj \
	mal2slut.obj malinit.obj malsinit.obj \
	mals2slut.obj mat2cb.obj mat3x3.obj matgem.obj \
	matreset.obj matrixgain.obj matrixlift.obj matto3x3.obj mgemslt.obj mglspan.obj \
	mkcube.obj mkidcube.obj mkpslut.obj mmals2slut.obj mofarslt.obj \
	mrslslut.obj msflt.obj msltslt.obj msslt.obj mulgems.obj mulmats.obj mulsluts.obj \
	nan.obj natcon.obj nfslut.obj \
	nmatrow.obj nofarba.obj nosvit.obj offsetslut.obj \
	ones.obj pal8rgba.obj partslt.obj pi.obj plt2slt.obj pltreset.obj \
	pltvalid.obj polypx.obj polyxyz.obj plut2slt.obj plutreset.obj \
	psfmt.obj purcol.obj purery.obj px32xyz.obj px8xyz.obj quintoks.obj \
	rdcmpmtx.obj rdcmpslut.obj readcbln.obj readcflt.obj readchrm.obj readdicr.obj \
	readgmnx.obj readkplt.obj readchrt.obj \
	readm34t.obj readm3x4.obj readsltt.obj \
	readslut.obj rec601.obj rec709.obj rec2020.obj \
	recrec.obj rgb2flut.obj rgb2slut.obj rgba8srgb.obj rgbslut.obj rgbycc.obj \
	ring.obj sinterpol.obj slt2pal.obj slt2plut.obj slt2vert.obj \
	sltcfs.obj sltfactors.obj sltgem.obj sltismat.obj sltmcs.obj sltms.obj sltreset.obj sltstr.obj \
	slut2cube.obj sluthead.obj slutis1d.obj spherical.obj srgba8bytes.obj strutring.obj \
	swapgem.obj tetramat.obj tintflut.obj unindxyz.obj unindbxyz.obj unindoxyz.obj unindwxyz.obj \
	valcbtitle.obj vert2slt.obj vertex.obj vertis1d.obj vertismat.obj vertpixl.obj \
	vertsamp.obj windbxyz.obj windoxyz.obj windwxyz.obj windxyz.obj word65535.obj writecbln.obj \
	writecflt.obj writechrm.obj writechrt.obj writedicr.obj writegmnx.obj writekplt.obj writem34t.obj \
	writem3x4.obj writesltt.obj \
	writeslut.obj xtrctch.obj xyz32bgra.obj xyz8bgras.obj xyz32px.obj \
	xyz8abgr.obj xyz8abgrs.obj xyz8argb.obj xyz8argbs.obj xyz8bgra.obj xyz8px.obj xyz8pxs.obj \
	yccmat.obj yccrgb.obj yshift.obj yunshift.obj zeroes.obj 

lib:	koliba.lib 

koliba.lib: $(objects)
	lib $(objects) -out:koliba.lib

%.obj: %.c koliba.h
	$(CC) -c $(CFLAGS) $< 



