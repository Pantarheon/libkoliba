/*

	pi.c

	Copyright 2019-2022 G. Adam Stanislav
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

// We cannot include koliba.h here because
// C has no way of declaring doubles as hex
// values. But we can "cheat" by declaring
// these as uint64_t values here but as
// doubles in koliba.h and the C compiler
// will be no wiser.
//
// But we still need to copy the export
// functionality from koliba.h here.

#ifdef	_WIN32
typedef	unsigned long long uint64_t;
#else
#include <stdint.h>
#endif

#ifdef	NOKLIBLIB
# define	KLBHID
# define	KLBDC
#elif defined _WIN32
#ifdef	DLL
# define	KLBDC	__declspec(dllexport)
#else	// !DLL
# define	KLBDC	__declspec(dllimport)
#endif	// DLL
#elif defined __APPLE__ || defined linux || defined __FreeBSD__
#  define KLBDC __attribute__((visibility("default")))
#else	// !_WIN32 !__APPLE__ !linux !__FreeBSD__
# define	KLBDC
#endif	// _WIN32

#ifdef __cplusplus
extern "C" {
#endif

KLBDC const uint64_t KOLIBA_Pi            = 0x400921FB54442D18;
KLBDC const uint64_t KOLIBA_2Pi           = 0x401921FB54442D18;
KLBDC const uint64_t KOLIBA_PiDiv2        = 0x3FF921FB54442D18;
KLBDC const uint64_t KOLIBA_PiDiv180      = 0x3F91DF46A2529D39;
KLBDC const uint64_t KOLIBA_180DivPi      = 0x404CA5DC1A63C1F8;
KLBDC const uint64_t KOLIBA_1Div2Pi       = 0x3FC45F306DC9C883;
KLBDC const uint64_t KOLIBA_1DivSqrt2Pi   = 0x3FD9884533D43651;
KLBDC const uint64_t KOLIBA_1Div360       = 0x3F66C16C16C16C17;
KLBDC const uint64_t KOLIBA_360           = 0x4076800000000000;
KLBDC const uint64_t KOLIBA_1Div2         = 0x3FE0000000000000;
KLBDC const uint64_t KOLIBA_1DivPi        = 0x3FD45F306DC9C883;
KLBDC const uint64_t KOLIBA_1DivSqrtPi    = 0x3FE20DD750429B6D;
KLBDC const uint64_t KOLIBA_180           = 0x4066800000000000;
KLBDC const uint64_t KOLIBA_1Div180       = 0x3F76C16C16C16C17;
KLBDC const uint64_t KOLIBA_2             = 0x4000000000000000;

KLBDC const uint64_t KOLIBA_Kappa         = 0x3FE1AC5111534A22;
KLBDC const uint64_t KOLIBA_1DivKappa     = 0x3FFCF876CCDF6CD9;
KLBDC const uint64_t KOLIBA_1MinKappa     = 0x3FDCA75DDD596BBD;
KLBDC const uint64_t KOLIBA_1Div1MinKappa = 0x4001DE56060EC9D0;

#ifdef __cplusplus
}
#endif

