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

CC=gcc
CFLG=-O3
CFLAGS=$(CFLG) -fPIC
ASFLAGS=--gstabs
PREFIX=/usr

objects = 8bitbuff.o abgr8xyz.o anachroma.o \
	anglearea.o anglecanon.o anglecos.o angledeg.o \
	anglenorm.o anglepi.o anglerad.o \
	angleset.o anglesin.o angleturn.o \
	apppx.o appxyz.o arclength.o argb8xyz.o \
	bgra32xyz.o bgra8xyz.o bindbxyz.o bindoxyz.o bindwxyz.o bindxyz.o \
	byte255.o calcsum.o cb2mat.o \
	cbreset.o cbsfmt.o cbstr.o cflthead.o checksum.o chordlength.o \
	chrmhead.o chrmreset.o chrmsfmt.o chroma.o \
	chrreset.o chrtstr.o cmyx.o colmask.o contrasts.o \
	dblsrgb.o deffiset.o diachroma.o dichroma.o dicrhead.o effiflut.o \
	effilut.o effinc.o effinv.o effiset.o effislut.o erythropia.o \
	externpx.o externxyz.o \
	farbsity.o fflut.o file.o findex.o fixdbl.o fixslut.o \
	flbinflut.o flinflut.o fltcube.o fltismat.o fltscale.o fltscube.o flutms.o \
	flutslut.o flutter.o flwinflut.o flyxyz.o frange.o fund.o gainslut.o \
	gamma.o gcomp.o getdtafmt.o getstrfmt.o gmnxfmt.o gmnxstr.o \
	gray2flut.o gray2slut.o gsmat.o homeslut.o \
	idchr.o idmallet.o idmat.o \
	idplt.o idplut.o idsfac.o idslut.o indbxyz.o indcxyz.o indoxyz.o indwxyz.o indxyz.o interflut.o \
	intermat.o interpol.o interslt.o intslut.o \
	invmat.o invslut.o isidflut.o isidslut.o \
	kplthead.o kpltsfmt.o ldxapply.o ldxhead.o ldxxyz.o \
	libver.o liftslut.o linsrgb.o m34str.o m3x4head.o m3x4sfmt.o \
	mal2slut.o malinit.o malsinit.o \
	mals2slut.o mat2cb.o mat3x3.o matgem.o \
	matreset.o matrixgain.o matrixlift.o matto3x3.o mgemslt.o mglspan.o \
	mkcube.o mkidcube.o mkpslut.o mmals2slut.o mofarslt.o monocycl.o \
	mrslslut.o msflt.o msltslt.o msslt.o mulgems.o mulmats.o mulsluts.o \
	nan.o natcon.o nfslut.o \
	nmatrow.o nofarba.o nosvit.o offsetslut.o \
	ones.o pal8rgba.o partslt.o pi.o plt2slt.o pltreset.o \
	pltvalid.o polypx.o polyxyz.o plut2slt.o plutreset.o \
	psfmt.o purcol.o purery.o px32xyz.o px8xyz.o quintoks.o \
	rdcmpmtx.o rdcmpslut.o readcbln.o readcflt.o readchrm.o readdicr.o \
	readgmnx.o readkplt.o readchrt.o \
	readm34t.o readm3x4.o readsltt.o \
	readslut.o rec601.o rec709.o rec2020.o \
	recrec.o rgb2flut.o rgb2slut.o rgba8srgb.o rgbslut.o rgbycc.o \
	ring.o sinterpol.o slt2pal.o slt2plut.o slt2vert.o \
	sltcfs.o sltfactors.o sltgem.o sltismat.o sltmcs.o sltms.o sltreset.o sltstr.o \
	slut2cube.o sluthead.o slutis1d.o spherical.o srgba8bytes.o strutring.o \
	swapgem.o tetramat.o tintflut.o unindxyz.o unindbxyz.o unindoxyz.o unindwxyz.o \
	valcbtitle.o vert2slt.o vertex.o vertis1d.o vertismat.o vertpixl.o \
	vertsamp.o windbxyz.o windoxyz.o windwxyz.o windxyz.o word65535.o writecbln.o \
	writecflt.o writechrm.o writechrt.o writedicr.o writegmnx.o writekplt.o writem34t.o \
	writem3x4.o writesltt.o \
	writeslut.o xtrctch.o xyz32bgra.o xyz8bgras.o xyz32px.o \
	xyz8abgr.o xyz8abgrs.o xyz8argb.o xyz8argbs.o xyz8bgra.o xyz8px.o xyz8pxs.o \
	yccmat.o yccrgb.o  yshift.o yunshift.o zeroes.o 

lib:	libkoliba.so

rebuild: clean lib

libkoliba.so: $(objects)
	$(CC) --shared -o libkoliba.so $(objects) -lm

install: lib
	install -p -s libkoliba.so $(PREFIX)/lib
	cp -p koliba.h $(PREFIX)/include
	chown root:root $(PREFIX)/include/koliba.h

%.o: %.c koliba.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(objects) libkoliba.so


