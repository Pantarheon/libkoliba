/*

	kpltsfmt.c

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

#include "koliba.h"
#include <inttypes.h>


KLBDC const char KOLIBA_PrintPlttFormat[] = "kPlt\n"
	"%.16" PRIX64 " "		/* black.r */
	"%.16" PRIX64 " "		/* black.g */
	"%.16" PRIX64 " "		/* black.b */
	"%.16" PRIX64 "\n"		/* black.e */
	"%.16" PRIX64 " "		/* white.r */
	"%.16" PRIX64 " "		/* white.g */
	"%.16" PRIX64 " "		/* white.b */
	"%.16" PRIX64 "\n"		/* white.e */
	"%.16" PRIX64 " "		/* red.r */
	"%.16" PRIX64 " "		/* red.g */
	"%.16" PRIX64 " "		/* red.b */
	"%.16" PRIX64 "\n"		/* red.e */
	"%.16" PRIX64 " "		/* green.r */
	"%.16" PRIX64 " "		/* green.g */
	"%.16" PRIX64 " "		/* green.b */
	"%.16" PRIX64 "\n"		/* green.e */
	"%.16" PRIX64 " "		/* blue.r */
	"%.16" PRIX64 " "		/* blue.g */
	"%.16" PRIX64 " "		/* blue.b */
	"%.16" PRIX64 "\n"		/* blue.e */
	"%.16" PRIX64 " "		/* cyan.r */
	"%.16" PRIX64 " "		/* cyan.g */
	"%.16" PRIX64 " "		/* cyan.b */
	"%.16" PRIX64 "\n"		/* cyan.e */
	"%.16" PRIX64 " "		/* magenta.r */
	"%.16" PRIX64 " "		/* magenta.g */
	"%.16" PRIX64 " "		/* magenta.b */
	"%.16" PRIX64 "\n"		/* magenta.e */
	"%.16" PRIX64 " "		/* yellow.r */
	"%.16" PRIX64 " "		/* yellow.g */
	"%.16" PRIX64 " "		/* yellow.b */
	"%.16" PRIX64 "\n"		/* yellow.e */
	"%.16" PRIX64 "\n"		/* efficacy */
	"%u\n";					/* erythropy */

KLBDC const char KOLIBA_ScanPlttFormat[] = " kPlt\n"
	"%" SCNx64 " "		/* black.r */
	"%" SCNx64 " "		/* black.g */
	"%" SCNx64 " "		/* black.b */
	"%" SCNx64 "\n"		/* black.e */
	"%" SCNx64 " "		/* white.r */
	"%" SCNx64 " "		/* white.g */
	"%" SCNx64 " "		/* white.b */
	"%" SCNx64 "\n"		/* white.e */
	"%" SCNx64 " "		/* red.r */
	"%" SCNx64 " "		/* red.g */
	"%" SCNx64 " "		/* red.b */
	"%" SCNx64 "\n"		/* red.e */
	"%" SCNx64 " "		/* green.r */
	"%" SCNx64 " "		/* green.g */
	"%" SCNx64 " "		/* green.b */
	"%" SCNx64 "\n"		/* green.e */
	"%" SCNx64 " "		/* blue.r */
	"%" SCNx64 " "		/* blue.g */
	"%" SCNx64 " "		/* blue.b */
	"%" SCNx64 "\n"		/* blue.e */
	"%" SCNx64 " "		/* cyan.r */
	"%" SCNx64 " "		/* cyan.g */
	"%" SCNx64 " "		/* cyan.b */
	"%" SCNx64 "\n"		/* cyan.e */
	"%" SCNx64 " "		/* magenta.r */
	"%" SCNx64 " "		/* magenta.g */
	"%" SCNx64 " "		/* magenta.b */
	"%" SCNx64 "\n"		/* magenta.e */
	"%" SCNx64 " "		/* yellow.r */
	"%" SCNx64 " "		/* yellow.g */
	"%" SCNx64 " "		/* yellow.b */
	"%" SCNx64 "\n"		/* yellow.e */
	"%" SCNx64 "\n"		/* efficacy */
	"%u\n";				/* erythropy */

KLBDC const char KOLIBA_ScanPlttHeaderFormat[] = " kPlt\n%" SCNx64 " ";
