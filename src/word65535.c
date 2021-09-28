/*

	word65535.c

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

#if defined _WIN32
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


// Quick lookup tables.
//
// Unlike with the simple 8 bpc table, we need two tables
// (one table would certainly work but would be huge),
// one for the high byte, one for the low byte.
//
// This works because (a+b)/c = a/c + b/c, or in our case,
// (HighByte*256+LowByte)/65535 =
// HighByte*256/65535 + LowByte/65535.
// So we pass the high byte as index to HighWordDiv65535,
// the low byte to LowWordDiv65535, and add up the results.
// This is faster than dividing by 65535.0.
KLBDC const uint64_t KOLIBA_HighWordDiv65535[256] = {
	0x0,	// 0	0 = 0/65535
	0x3F70001000100010,	// 1	0.00390631 = 256/65535
	0x3F80001000100010,	// 2	0.00781262 = 512/65535
	0x3F88001800180018,	// 3	0.0117189 = 768/65535
	0x3F90001000100010,	// 4	0.0156252 = 1024/65535
	0x3F94001400140014,	// 5	0.0195315 = 1280/65535
	0x3F98001800180018,	// 6	0.0234379 = 1536/65535
	0x3F9C001C001C001C,	// 7	0.0273442 = 1792/65535
	0x3FA0001000100010,	// 8	0.0312505 = 2048/65535
	0x3FA2001200120012,	// 9	0.0351568 = 2304/65535
	0x3FA4001400140014,	// 10	0.0390631 = 2560/65535
	0x3FA6001600160016,	// 11	0.0429694 = 2816/65535
	0x3FA8001800180018,	// 12	0.0468757 = 3072/65535
	0x3FAA001A001A001A,	// 13	0.050782 = 3328/65535
	0x3FAC001C001C001C,	// 14	0.0546883 = 3584/65535
	0x3FAE001E001E001E,	// 15	0.0585946 = 3840/65535
	0x3FB0001000100010,	// 16	0.062501 = 4096/65535
	0x3FB1001100110011,	// 17	0.0664073 = 4352/65535
	0x3FB2001200120012,	// 18	0.0703136 = 4608/65535
	0x3FB3001300130013,	// 19	0.0742199 = 4864/65535
	0x3FB4001400140014,	// 20	0.0781262 = 5120/65535
	0x3FB5001500150015,	// 21	0.0820325 = 5376/65535
	0x3FB6001600160016,	// 22	0.0859388 = 5632/65535
	0x3FB7001700170017,	// 23	0.0898451 = 5888/65535
	0x3FB8001800180018,	// 24	0.0937514 = 6144/65535
	0x3FB9001900190019,	// 25	0.0976577 = 6400/65535
	0x3FBA001A001A001A,	// 26	0.101564 = 6656/65535
	0x3FBB001B001B001B,	// 27	0.10547 = 6912/65535
	0x3FBC001C001C001C,	// 28	0.109377 = 7168/65535
	0x3FBD001D001D001D,	// 29	0.113283 = 7424/65535
	0x3FBE001E001E001E,	// 30	0.117189 = 7680/65535
	0x3FBF001F001F001F,	// 31	0.121096 = 7936/65535
	0x3FC0001000100010,	// 32	0.125002 = 8192/65535
	0x3FC0801080108011,	// 33	0.128908 = 8448/65535
	0x3FC1001100110011,	// 34	0.132815 = 8704/65535
	0x3FC1801180118012,	// 35	0.136721 = 8960/65535
	0x3FC2001200120012,	// 36	0.140627 = 9216/65535
	0x3FC2801280128013,	// 37	0.144533 = 9472/65535
	0x3FC3001300130013,	// 38	0.14844 = 9728/65535
	0x3FC3801380138014,	// 39	0.152346 = 9984/65535
	0x3FC4001400140014,	// 40	0.156252 = 10240/65535
	0x3FC4801480148015,	// 41	0.160159 = 10496/65535
	0x3FC5001500150015,	// 42	0.164065 = 10752/65535
	0x3FC5801580158016,	// 43	0.167971 = 11008/65535
	0x3FC6001600160016,	// 44	0.171878 = 11264/65535
	0x3FC6801680168017,	// 45	0.175784 = 11520/65535
	0x3FC7001700170017,	// 46	0.17969 = 11776/65535
	0x3FC7801780178018,	// 47	0.183597 = 12032/65535
	0x3FC8001800180018,	// 48	0.187503 = 12288/65535
	0x3FC8801880188019,	// 49	0.191409 = 12544/65535
	0x3FC9001900190019,	// 50	0.195315 = 12800/65535
	0x3FC980198019801A,	// 51	0.199222 = 13056/65535
	0x3FCA001A001A001A,	// 52	0.203128 = 13312/65535
	0x3FCA801A801A801B,	// 53	0.207034 = 13568/65535
	0x3FCB001B001B001B,	// 54	0.210941 = 13824/65535
	0x3FCB801B801B801C,	// 55	0.214847 = 14080/65535
	0x3FCC001C001C001C,	// 56	0.218753 = 14336/65535
	0x3FCC801C801C801D,	// 57	0.22266 = 14592/65535
	0x3FCD001D001D001D,	// 58	0.226566 = 14848/65535
	0x3FCD801D801D801E,	// 59	0.230472 = 15104/65535
	0x3FCE001E001E001E,	// 60	0.234379 = 15360/65535
	0x3FCE801E801E801F,	// 61	0.238285 = 15616/65535
	0x3FCF001F001F001F,	// 62	0.242191 = 15872/65535
	0x3FCF801F801F8020,	// 63	0.246098 = 16128/65535
	0x3FD0001000100010,	// 64	0.250004 = 16384/65535
	0x3FD0401040104010,	// 65	0.25391 = 16640/65535
	0x3FD0801080108011,	// 66	0.257816 = 16896/65535
	0x3FD0C010C010C011,	// 67	0.261723 = 17152/65535
	0x3FD1001100110011,	// 68	0.265629 = 17408/65535
	0x3FD1401140114011,	// 69	0.269535 = 17664/65535
	0x3FD1801180118012,	// 70	0.273442 = 17920/65535
	0x3FD1C011C011C012,	// 71	0.277348 = 18176/65535
	0x3FD2001200120012,	// 72	0.281254 = 18432/65535
	0x3FD2401240124012,	// 73	0.285161 = 18688/65535
	0x3FD2801280128013,	// 74	0.289067 = 18944/65535
	0x3FD2C012C012C013,	// 75	0.292973 = 19200/65535
	0x3FD3001300130013,	// 76	0.29688 = 19456/65535
	0x3FD3401340134013,	// 77	0.300786 = 19712/65535
	0x3FD3801380138014,	// 78	0.304692 = 19968/65535
	0x3FD3C013C013C014,	// 79	0.308598 = 20224/65535
	0x3FD4001400140014,	// 80	0.312505 = 20480/65535
	0x3FD4401440144014,	// 81	0.316411 = 20736/65535
	0x3FD4801480148015,	// 82	0.320317 = 20992/65535
	0x3FD4C014C014C015,	// 83	0.324224 = 21248/65535
	0x3FD5001500150015,	// 84	0.32813 = 21504/65535
	0x3FD5401540154015,	// 85	0.332036 = 21760/65535
	0x3FD5801580158016,	// 86	0.335943 = 22016/65535
	0x3FD5C015C015C016,	// 87	0.339849 = 22272/65535
	0x3FD6001600160016,	// 88	0.343755 = 22528/65535
	0x3FD6401640164016,	// 89	0.347662 = 22784/65535
	0x3FD6801680168017,	// 90	0.351568 = 23040/65535
	0x3FD6C016C016C017,	// 91	0.355474 = 23296/65535
	0x3FD7001700170017,	// 92	0.35938 = 23552/65535
	0x3FD7401740174017,	// 93	0.363287 = 23808/65535
	0x3FD7801780178018,	// 94	0.367193 = 24064/65535
	0x3FD7C017C017C018,	// 95	0.371099 = 24320/65535
	0x3FD8001800180018,	// 96	0.375006 = 24576/65535
	0x3FD8401840184018,	// 97	0.378912 = 24832/65535
	0x3FD8801880188019,	// 98	0.382818 = 25088/65535
	0x3FD8C018C018C019,	// 99	0.386725 = 25344/65535
	0x3FD9001900190019,	// 100	0.390631 = 25600/65535
	0x3FD9401940194019,	// 101	0.394537 = 25856/65535
	0x3FD980198019801A,	// 102	0.398444 = 26112/65535
	0x3FD9C019C019C01A,	// 103	0.40235 = 26368/65535
	0x3FDA001A001A001A,	// 104	0.406256 = 26624/65535
	0x3FDA401A401A401A,	// 105	0.410163 = 26880/65535
	0x3FDA801A801A801B,	// 106	0.414069 = 27136/65535
	0x3FDAC01AC01AC01B,	// 107	0.417975 = 27392/65535
	0x3FDB001B001B001B,	// 108	0.421881 = 27648/65535
	0x3FDB401B401B401B,	// 109	0.425788 = 27904/65535
	0x3FDB801B801B801C,	// 110	0.429694 = 28160/65535
	0x3FDBC01BC01BC01C,	// 111	0.4336 = 28416/65535
	0x3FDC001C001C001C,	// 112	0.437507 = 28672/65535
	0x3FDC401C401C401C,	// 113	0.441413 = 28928/65535
	0x3FDC801C801C801D,	// 114	0.445319 = 29184/65535
	0x3FDCC01CC01CC01D,	// 115	0.449226 = 29440/65535
	0x3FDD001D001D001D,	// 116	0.453132 = 29696/65535
	0x3FDD401D401D401D,	// 117	0.457038 = 29952/65535
	0x3FDD801D801D801E,	// 118	0.460945 = 30208/65535
	0x3FDDC01DC01DC01E,	// 119	0.464851 = 30464/65535
	0x3FDE001E001E001E,	// 120	0.468757 = 30720/65535
	0x3FDE401E401E401E,	// 121	0.472663 = 30976/65535
	0x3FDE801E801E801F,	// 122	0.47657 = 31232/65535
	0x3FDEC01EC01EC01F,	// 123	0.480476 = 31488/65535
	0x3FDF001F001F001F,	// 124	0.484382 = 31744/65535
	0x3FDF401F401F401F,	// 125	0.488289 = 32000/65535
	0x3FDF801F801F8020,	// 126	0.492195 = 32256/65535
	0x3FDFC01FC01FC020,	// 127	0.496101 = 32512/65535
	0x3FE0001000100010,	// 128	0.500008 = 32768/65535
	0x3FE0201020102010,	// 129	0.503914 = 33024/65535
	0x3FE0401040104010,	// 130	0.50782 = 33280/65535
	0x3FE0601060106010,	// 131	0.511727 = 33536/65535
	0x3FE0801080108011,	// 132	0.515633 = 33792/65535
	0x3FE0A010A010A011,	// 133	0.519539 = 34048/65535
	0x3FE0C010C010C011,	// 134	0.523445 = 34304/65535
	0x3FE0E010E010E011,	// 135	0.527352 = 34560/65535
	0x3FE1001100110011,	// 136	0.531258 = 34816/65535
	0x3FE1201120112011,	// 137	0.535164 = 35072/65535
	0x3FE1401140114011,	// 138	0.539071 = 35328/65535
	0x3FE1601160116011,	// 139	0.542977 = 35584/65535
	0x3FE1801180118012,	// 140	0.546883 = 35840/65535
	0x3FE1A011A011A012,	// 141	0.55079 = 36096/65535
	0x3FE1C011C011C012,	// 142	0.554696 = 36352/65535
	0x3FE1E011E011E012,	// 143	0.558602 = 36608/65535
	0x3FE2001200120012,	// 144	0.562509 = 36864/65535
	0x3FE2201220122012,	// 145	0.566415 = 37120/65535
	0x3FE2401240124012,	// 146	0.570321 = 37376/65535
	0x3FE2601260126012,	// 147	0.574228 = 37632/65535
	0x3FE2801280128013,	// 148	0.578134 = 37888/65535
	0x3FE2A012A012A013,	// 149	0.58204 = 38144/65535
	0x3FE2C012C012C013,	// 150	0.585946 = 38400/65535
	0x3FE2E012E012E013,	// 151	0.589853 = 38656/65535
	0x3FE3001300130013,	// 152	0.593759 = 38912/65535
	0x3FE3201320132013,	// 153	0.597665 = 39168/65535
	0x3FE3401340134013,	// 154	0.601572 = 39424/65535
	0x3FE3601360136013,	// 155	0.605478 = 39680/65535
	0x3FE3801380138014,	// 156	0.609384 = 39936/65535
	0x3FE3A013A013A014,	// 157	0.613291 = 40192/65535
	0x3FE3C013C013C014,	// 158	0.617197 = 40448/65535
	0x3FE3E013E013E014,	// 159	0.621103 = 40704/65535
	0x3FE4001400140014,	// 160	0.62501 = 40960/65535
	0x3FE4201420142014,	// 161	0.628916 = 41216/65535
	0x3FE4401440144014,	// 162	0.632822 = 41472/65535
	0x3FE4601460146014,	// 163	0.636728 = 41728/65535
	0x3FE4801480148015,	// 164	0.640635 = 41984/65535
	0x3FE4A014A014A015,	// 165	0.644541 = 42240/65535
	0x3FE4C014C014C015,	// 166	0.648447 = 42496/65535
	0x3FE4E014E014E015,	// 167	0.652354 = 42752/65535
	0x3FE5001500150015,	// 168	0.65626 = 43008/65535
	0x3FE5201520152015,	// 169	0.660166 = 43264/65535
	0x3FE5401540154015,	// 170	0.664073 = 43520/65535
	0x3FE5601560156015,	// 171	0.667979 = 43776/65535
	0x3FE5801580158016,	// 172	0.671885 = 44032/65535
	0x3FE5A015A015A016,	// 173	0.675792 = 44288/65535
	0x3FE5C015C015C016,	// 174	0.679698 = 44544/65535
	0x3FE5E015E015E016,	// 175	0.683604 = 44800/65535
	0x3FE6001600160016,	// 176	0.68751 = 45056/65535
	0x3FE6201620162016,	// 177	0.691417 = 45312/65535
	0x3FE6401640164016,	// 178	0.695323 = 45568/65535
	0x3FE6601660166016,	// 179	0.699229 = 45824/65535
	0x3FE6801680168017,	// 180	0.703136 = 46080/65535
	0x3FE6A016A016A017,	// 181	0.707042 = 46336/65535
	0x3FE6C016C016C017,	// 182	0.710948 = 46592/65535
	0x3FE6E016E016E017,	// 183	0.714855 = 46848/65535
	0x3FE7001700170017,	// 184	0.718761 = 47104/65535
	0x3FE7201720172017,	// 185	0.722667 = 47360/65535
	0x3FE7401740174017,	// 186	0.726574 = 47616/65535
	0x3FE7601760176017,	// 187	0.73048 = 47872/65535
	0x3FE7801780178018,	// 188	0.734386 = 48128/65535
	0x3FE7A017A017A018,	// 189	0.738293 = 48384/65535
	0x3FE7C017C017C018,	// 190	0.742199 = 48640/65535
	0x3FE7E017E017E018,	// 191	0.746105 = 48896/65535
	0x3FE8001800180018,	// 192	0.750011 = 49152/65535
	0x3FE8201820182018,	// 193	0.753918 = 49408/65535
	0x3FE8401840184018,	// 194	0.757824 = 49664/65535
	0x3FE8601860186018,	// 195	0.76173 = 49920/65535
	0x3FE8801880188019,	// 196	0.765637 = 50176/65535
	0x3FE8A018A018A019,	// 197	0.769543 = 50432/65535
	0x3FE8C018C018C019,	// 198	0.773449 = 50688/65535
	0x3FE8E018E018E019,	// 199	0.777356 = 50944/65535
	0x3FE9001900190019,	// 200	0.781262 = 51200/65535
	0x3FE9201920192019,	// 201	0.785168 = 51456/65535
	0x3FE9401940194019,	// 202	0.789075 = 51712/65535
	0x3FE9601960196019,	// 203	0.792981 = 51968/65535
	0x3FE980198019801A,	// 204	0.796887 = 52224/65535
	0x3FE9A019A019A01A,	// 205	0.800793 = 52480/65535
	0x3FE9C019C019C01A,	// 206	0.8047 = 52736/65535
	0x3FE9E019E019E01A,	// 207	0.808606 = 52992/65535
	0x3FEA001A001A001A,	// 208	0.812512 = 53248/65535
	0x3FEA201A201A201A,	// 209	0.816419 = 53504/65535
	0x3FEA401A401A401A,	// 210	0.820325 = 53760/65535
	0x3FEA601A601A601A,	// 211	0.824231 = 54016/65535
	0x3FEA801A801A801B,	// 212	0.828138 = 54272/65535
	0x3FEAA01AA01AA01B,	// 213	0.832044 = 54528/65535
	0x3FEAC01AC01AC01B,	// 214	0.83595 = 54784/65535
	0x3FEAE01AE01AE01B,	// 215	0.839857 = 55040/65535
	0x3FEB001B001B001B,	// 216	0.843763 = 55296/65535
	0x3FEB201B201B201B,	// 217	0.847669 = 55552/65535
	0x3FEB401B401B401B,	// 218	0.851575 = 55808/65535
	0x3FEB601B601B601B,	// 219	0.855482 = 56064/65535
	0x3FEB801B801B801C,	// 220	0.859388 = 56320/65535
	0x3FEBA01BA01BA01C,	// 221	0.863294 = 56576/65535
	0x3FEBC01BC01BC01C,	// 222	0.867201 = 56832/65535
	0x3FEBE01BE01BE01C,	// 223	0.871107 = 57088/65535
	0x3FEC001C001C001C,	// 224	0.875013 = 57344/65535
	0x3FEC201C201C201C,	// 225	0.87892 = 57600/65535
	0x3FEC401C401C401C,	// 226	0.882826 = 57856/65535
	0x3FEC601C601C601C,	// 227	0.886732 = 58112/65535
	0x3FEC801C801C801D,	// 228	0.890639 = 58368/65535
	0x3FECA01CA01CA01D,	// 229	0.894545 = 58624/65535
	0x3FECC01CC01CC01D,	// 230	0.898451 = 58880/65535
	0x3FECE01CE01CE01D,	// 231	0.902358 = 59136/65535
	0x3FED001D001D001D,	// 232	0.906264 = 59392/65535
	0x3FED201D201D201D,	// 233	0.91017 = 59648/65535
	0x3FED401D401D401D,	// 234	0.914076 = 59904/65535
	0x3FED601D601D601D,	// 235	0.917983 = 60160/65535
	0x3FED801D801D801E,	// 236	0.921889 = 60416/65535
	0x3FEDA01DA01DA01E,	// 237	0.925795 = 60672/65535
	0x3FEDC01DC01DC01E,	// 238	0.929702 = 60928/65535
	0x3FEDE01DE01DE01E,	// 239	0.933608 = 61184/65535
	0x3FEE001E001E001E,	// 240	0.937514 = 61440/65535
	0x3FEE201E201E201E,	// 241	0.941421 = 61696/65535
	0x3FEE401E401E401E,	// 242	0.945327 = 61952/65535
	0x3FEE601E601E601E,	// 243	0.949233 = 62208/65535
	0x3FEE801E801E801F,	// 244	0.95314 = 62464/65535
	0x3FEEA01EA01EA01F,	// 245	0.957046 = 62720/65535
	0x3FEEC01EC01EC01F,	// 246	0.960952 = 62976/65535
	0x3FEEE01EE01EE01F,	// 247	0.964858 = 63232/65535
	0x3FEF001F001F001F,	// 248	0.968765 = 63488/65535
	0x3FEF201F201F201F,	// 249	0.972671 = 63744/65535
	0x3FEF401F401F401F,	// 250	0.976577 = 64000/65535
	0x3FEF601F601F601F,	// 251	0.980484 = 64256/65535
	0x3FEF801F801F8020,	// 252	0.98439 = 64512/65535
	0x3FEFA01FA01FA020,	// 253	0.988296 = 64768/65535
	0x3FEFC01FC01FC020,	// 254	0.992203 = 65024/65535
	0x3FEFE01FE01FE020,	// 255	0.996109 = 65280/65535
};

KLBDC const uint64_t KOLIBA_LowWordDiv65535[256] = {
	0x0,	// 0	0 = 0/65535
	0x3EF0001000100010,	// 1	1.5259e-005 = 1/65535
	0x3F00001000100010,	// 2	3.0518e-005 = 2/65535
	0x3F08001800180018,	// 3	4.57771e-005 = 3/65535
	0x3F10001000100010,	// 4	6.10361e-005 = 4/65535
	0x3F14001400140014,	// 5	7.62951e-005 = 5/65535
	0x3F18001800180018,	// 6	9.15541e-005 = 6/65535
	0x3F1C001C001C001C,	// 7	0.000106813 = 7/65535
	0x3F20001000100010,	// 8	0.000122072 = 8/65535
	0x3F22001200120012,	// 9	0.000137331 = 9/65535
	0x3F24001400140014,	// 10	0.00015259 = 10/65535
	0x3F26001600160016,	// 11	0.000167849 = 11/65535
	0x3F28001800180018,	// 12	0.000183108 = 12/65535
	0x3F2A001A001A001A,	// 13	0.000198367 = 13/65535
	0x3F2C001C001C001C,	// 14	0.000213626 = 14/65535
	0x3F2E001E001E001E,	// 15	0.000228885 = 15/65535
	0x3F30001000100010,	// 16	0.000244144 = 16/65535
	0x3F31001100110011,	// 17	0.000259403 = 17/65535
	0x3F32001200120012,	// 18	0.000274662 = 18/65535
	0x3F33001300130013,	// 19	0.000289921 = 19/65535
	0x3F34001400140014,	// 20	0.00030518 = 20/65535
	0x3F35001500150015,	// 21	0.000320439 = 21/65535
	0x3F36001600160016,	// 22	0.000335698 = 22/65535
	0x3F37001700170017,	// 23	0.000350958 = 23/65535
	0x3F38001800180018,	// 24	0.000366217 = 24/65535
	0x3F39001900190019,	// 25	0.000381476 = 25/65535
	0x3F3A001A001A001A,	// 26	0.000396735 = 26/65535
	0x3F3B001B001B001B,	// 27	0.000411994 = 27/65535
	0x3F3C001C001C001C,	// 28	0.000427253 = 28/65535
	0x3F3D001D001D001D,	// 29	0.000442512 = 29/65535
	0x3F3E001E001E001E,	// 30	0.000457771 = 30/65535
	0x3F3F001F001F001F,	// 31	0.00047303 = 31/65535
	0x3F40001000100010,	// 32	0.000488289 = 32/65535
	0x3F40801080108011,	// 33	0.000503548 = 33/65535
	0x3F41001100110011,	// 34	0.000518807 = 34/65535
	0x3F41801180118012,	// 35	0.000534066 = 35/65535
	0x3F42001200120012,	// 36	0.000549325 = 36/65535
	0x3F42801280128013,	// 37	0.000564584 = 37/65535
	0x3F43001300130013,	// 38	0.000579843 = 38/65535
	0x3F43801380138014,	// 39	0.000595102 = 39/65535
	0x3F44001400140014,	// 40	0.000610361 = 40/65535
	0x3F44801480148015,	// 41	0.00062562 = 41/65535
	0x3F45001500150015,	// 42	0.000640879 = 42/65535
	0x3F45801580158016,	// 43	0.000656138 = 43/65535
	0x3F46001600160016,	// 44	0.000671397 = 44/65535
	0x3F46801680168017,	// 45	0.000686656 = 45/65535
	0x3F47001700170017,	// 46	0.000701915 = 46/65535
	0x3F47801780178018,	// 47	0.000717174 = 47/65535
	0x3F48001800180018,	// 48	0.000732433 = 48/65535
	0x3F48801880188019,	// 49	0.000747692 = 49/65535
	0x3F49001900190019,	// 50	0.000762951 = 50/65535
	0x3F4980198019801A,	// 51	0.00077821 = 51/65535
	0x3F4A001A001A001A,	// 52	0.000793469 = 52/65535
	0x3F4A801A801A801B,	// 53	0.000808728 = 53/65535
	0x3F4B001B001B001B,	// 54	0.000823987 = 54/65535
	0x3F4B801B801B801C,	// 55	0.000839246 = 55/65535
	0x3F4C001C001C001C,	// 56	0.000854505 = 56/65535
	0x3F4C801C801C801D,	// 57	0.000869764 = 57/65535
	0x3F4D001D001D001D,	// 58	0.000885023 = 58/65535
	0x3F4D801D801D801E,	// 59	0.000900282 = 59/65535
	0x3F4E001E001E001E,	// 60	0.000915541 = 60/65535
	0x3F4E801E801E801F,	// 61	0.0009308 = 61/65535
	0x3F4F001F001F001F,	// 62	0.000946059 = 62/65535
	0x3F4F801F801F8020,	// 63	0.000961318 = 63/65535
	0x3F50001000100010,	// 64	0.000976577 = 64/65535
	0x3F50401040104010,	// 65	0.000991836 = 65/65535
	0x3F50801080108011,	// 66	0.0010071 = 66/65535
	0x3F50C010C010C011,	// 67	0.00102235 = 67/65535
	0x3F51001100110011,	// 68	0.00103761 = 68/65535
	0x3F51401140114011,	// 69	0.00105287 = 69/65535
	0x3F51801180118012,	// 70	0.00106813 = 70/65535
	0x3F51C011C011C012,	// 71	0.00108339 = 71/65535
	0x3F52001200120012,	// 72	0.00109865 = 72/65535
	0x3F52401240124012,	// 73	0.00111391 = 73/65535
	0x3F52801280128013,	// 74	0.00112917 = 74/65535
	0x3F52C012C012C013,	// 75	0.00114443 = 75/65535
	0x3F53001300130013,	// 76	0.00115969 = 76/65535
	0x3F53401340134013,	// 77	0.00117494 = 77/65535
	0x3F53801380138014,	// 78	0.0011902 = 78/65535
	0x3F53C013C013C014,	// 79	0.00120546 = 79/65535
	0x3F54001400140014,	// 80	0.00122072 = 80/65535
	0x3F54401440144014,	// 81	0.00123598 = 81/65535
	0x3F54801480148015,	// 82	0.00125124 = 82/65535
	0x3F54C014C014C015,	// 83	0.0012665 = 83/65535
	0x3F55001500150015,	// 84	0.00128176 = 84/65535
	0x3F55401540154015,	// 85	0.00129702 = 85/65535
	0x3F55801580158016,	// 86	0.00131228 = 86/65535
	0x3F55C015C015C016,	// 87	0.00132753 = 87/65535
	0x3F56001600160016,	// 88	0.00134279 = 88/65535
	0x3F56401640164016,	// 89	0.00135805 = 89/65535
	0x3F56801680168017,	// 90	0.00137331 = 90/65535
	0x3F56C016C016C017,	// 91	0.00138857 = 91/65535
	0x3F57001700170017,	// 92	0.00140383 = 92/65535
	0x3F57401740174017,	// 93	0.00141909 = 93/65535
	0x3F57801780178018,	// 94	0.00143435 = 94/65535
	0x3F57C017C017C018,	// 95	0.00144961 = 95/65535
	0x3F58001800180018,	// 96	0.00146487 = 96/65535
	0x3F58401840184018,	// 97	0.00148013 = 97/65535
	0x3F58801880188019,	// 98	0.00149538 = 98/65535
	0x3F58C018C018C019,	// 99	0.00151064 = 99/65535
	0x3F59001900190019,	// 100	0.0015259 = 100/65535
	0x3F59401940194019,	// 101	0.00154116 = 101/65535
	0x3F5980198019801A,	// 102	0.00155642 = 102/65535
	0x3F59C019C019C01A,	// 103	0.00157168 = 103/65535
	0x3F5A001A001A001A,	// 104	0.00158694 = 104/65535
	0x3F5A401A401A401A,	// 105	0.0016022 = 105/65535
	0x3F5A801A801A801B,	// 106	0.00161746 = 106/65535
	0x3F5AC01AC01AC01B,	// 107	0.00163272 = 107/65535
	0x3F5B001B001B001B,	// 108	0.00164797 = 108/65535
	0x3F5B401B401B401B,	// 109	0.00166323 = 109/65535
	0x3F5B801B801B801C,	// 110	0.00167849 = 110/65535
	0x3F5BC01BC01BC01C,	// 111	0.00169375 = 111/65535
	0x3F5C001C001C001C,	// 112	0.00170901 = 112/65535
	0x3F5C401C401C401C,	// 113	0.00172427 = 113/65535
	0x3F5C801C801C801D,	// 114	0.00173953 = 114/65535
	0x3F5CC01CC01CC01D,	// 115	0.00175479 = 115/65535
	0x3F5D001D001D001D,	// 116	0.00177005 = 116/65535
	0x3F5D401D401D401D,	// 117	0.00178531 = 117/65535
	0x3F5D801D801D801E,	// 118	0.00180056 = 118/65535
	0x3F5DC01DC01DC01E,	// 119	0.00181582 = 119/65535
	0x3F5E001E001E001E,	// 120	0.00183108 = 120/65535
	0x3F5E401E401E401E,	// 121	0.00184634 = 121/65535
	0x3F5E801E801E801F,	// 122	0.0018616 = 122/65535
	0x3F5EC01EC01EC01F,	// 123	0.00187686 = 123/65535
	0x3F5F001F001F001F,	// 124	0.00189212 = 124/65535
	0x3F5F401F401F401F,	// 125	0.00190738 = 125/65535
	0x3F5F801F801F8020,	// 126	0.00192264 = 126/65535
	0x3F5FC01FC01FC020,	// 127	0.0019379 = 127/65535
	0x3F60001000100010,	// 128	0.00195315 = 128/65535
	0x3F60201020102010,	// 129	0.00196841 = 129/65535
	0x3F60401040104010,	// 130	0.00198367 = 130/65535
	0x3F60601060106010,	// 131	0.00199893 = 131/65535
	0x3F60801080108011,	// 132	0.00201419 = 132/65535
	0x3F60A010A010A011,	// 133	0.00202945 = 133/65535
	0x3F60C010C010C011,	// 134	0.00204471 = 134/65535
	0x3F60E010E010E011,	// 135	0.00205997 = 135/65535
	0x3F61001100110011,	// 136	0.00207523 = 136/65535
	0x3F61201120112011,	// 137	0.00209049 = 137/65535
	0x3F61401140114011,	// 138	0.00210575 = 138/65535
	0x3F61601160116011,	// 139	0.002121 = 139/65535
	0x3F61801180118012,	// 140	0.00213626 = 140/65535
	0x3F61A011A011A012,	// 141	0.00215152 = 141/65535
	0x3F61C011C011C012,	// 142	0.00216678 = 142/65535
	0x3F61E011E011E012,	// 143	0.00218204 = 143/65535
	0x3F62001200120012,	// 144	0.0021973 = 144/65535
	0x3F62201220122012,	// 145	0.00221256 = 145/65535
	0x3F62401240124012,	// 146	0.00222782 = 146/65535
	0x3F62601260126012,	// 147	0.00224308 = 147/65535
	0x3F62801280128013,	// 148	0.00225834 = 148/65535
	0x3F62A012A012A013,	// 149	0.00227359 = 149/65535
	0x3F62C012C012C013,	// 150	0.00228885 = 150/65535
	0x3F62E012E012E013,	// 151	0.00230411 = 151/65535
	0x3F63001300130013,	// 152	0.00231937 = 152/65535
	0x3F63201320132013,	// 153	0.00233463 = 153/65535
	0x3F63401340134013,	// 154	0.00234989 = 154/65535
	0x3F63601360136013,	// 155	0.00236515 = 155/65535
	0x3F63801380138014,	// 156	0.00238041 = 156/65535
	0x3F63A013A013A014,	// 157	0.00239567 = 157/65535
	0x3F63C013C013C014,	// 158	0.00241093 = 158/65535
	0x3F63E013E013E014,	// 159	0.00242618 = 159/65535
	0x3F64001400140014,	// 160	0.00244144 = 160/65535
	0x3F64201420142014,	// 161	0.0024567 = 161/65535
	0x3F64401440144014,	// 162	0.00247196 = 162/65535
	0x3F64601460146014,	// 163	0.00248722 = 163/65535
	0x3F64801480148015,	// 164	0.00250248 = 164/65535
	0x3F64A014A014A015,	// 165	0.00251774 = 165/65535
	0x3F64C014C014C015,	// 166	0.002533 = 166/65535
	0x3F64E014E014E015,	// 167	0.00254826 = 167/65535
	0x3F65001500150015,	// 168	0.00256352 = 168/65535
	0x3F65201520152015,	// 169	0.00257877 = 169/65535
	0x3F65401540154015,	// 170	0.00259403 = 170/65535
	0x3F65601560156015,	// 171	0.00260929 = 171/65535
	0x3F65801580158016,	// 172	0.00262455 = 172/65535
	0x3F65A015A015A016,	// 173	0.00263981 = 173/65535
	0x3F65C015C015C016,	// 174	0.00265507 = 174/65535
	0x3F65E015E015E016,	// 175	0.00267033 = 175/65535
	0x3F66001600160016,	// 176	0.00268559 = 176/65535
	0x3F66201620162016,	// 177	0.00270085 = 177/65535
	0x3F66401640164016,	// 178	0.00271611 = 178/65535
	0x3F66601660166016,	// 179	0.00273136 = 179/65535
	0x3F66801680168017,	// 180	0.00274662 = 180/65535
	0x3F66A016A016A017,	// 181	0.00276188 = 181/65535
	0x3F66C016C016C017,	// 182	0.00277714 = 182/65535
	0x3F66E016E016E017,	// 183	0.0027924 = 183/65535
	0x3F67001700170017,	// 184	0.00280766 = 184/65535
	0x3F67201720172017,	// 185	0.00282292 = 185/65535
	0x3F67401740174017,	// 186	0.00283818 = 186/65535
	0x3F67601760176017,	// 187	0.00285344 = 187/65535
	0x3F67801780178018,	// 188	0.0028687 = 188/65535
	0x3F67A017A017A018,	// 189	0.00288396 = 189/65535
	0x3F67C017C017C018,	// 190	0.00289921 = 190/65535
	0x3F67E017E017E018,	// 191	0.00291447 = 191/65535
	0x3F68001800180018,	// 192	0.00292973 = 192/65535
	0x3F68201820182018,	// 193	0.00294499 = 193/65535
	0x3F68401840184018,	// 194	0.00296025 = 194/65535
	0x3F68601860186018,	// 195	0.00297551 = 195/65535
	0x3F68801880188019,	// 196	0.00299077 = 196/65535
	0x3F68A018A018A019,	// 197	0.00300603 = 197/65535
	0x3F68C018C018C019,	// 198	0.00302129 = 198/65535
	0x3F68E018E018E019,	// 199	0.00303655 = 199/65535
	0x3F69001900190019,	// 200	0.0030518 = 200/65535
	0x3F69201920192019,	// 201	0.00306706 = 201/65535
	0x3F69401940194019,	// 202	0.00308232 = 202/65535
	0x3F69601960196019,	// 203	0.00309758 = 203/65535
	0x3F6980198019801A,	// 204	0.00311284 = 204/65535
	0x3F69A019A019A01A,	// 205	0.0031281 = 205/65535
	0x3F69C019C019C01A,	// 206	0.00314336 = 206/65535
	0x3F69E019E019E01A,	// 207	0.00315862 = 207/65535
	0x3F6A001A001A001A,	// 208	0.00317388 = 208/65535
	0x3F6A201A201A201A,	// 209	0.00318914 = 209/65535
	0x3F6A401A401A401A,	// 210	0.00320439 = 210/65535
	0x3F6A601A601A601A,	// 211	0.00321965 = 211/65535
	0x3F6A801A801A801B,	// 212	0.00323491 = 212/65535
	0x3F6AA01AA01AA01B,	// 213	0.00325017 = 213/65535
	0x3F6AC01AC01AC01B,	// 214	0.00326543 = 214/65535
	0x3F6AE01AE01AE01B,	// 215	0.00328069 = 215/65535
	0x3F6B001B001B001B,	// 216	0.00329595 = 216/65535
	0x3F6B201B201B201B,	// 217	0.00331121 = 217/65535
	0x3F6B401B401B401B,	// 218	0.00332647 = 218/65535
	0x3F6B601B601B601B,	// 219	0.00334173 = 219/65535
	0x3F6B801B801B801C,	// 220	0.00335698 = 220/65535
	0x3F6BA01BA01BA01C,	// 221	0.00337224 = 221/65535
	0x3F6BC01BC01BC01C,	// 222	0.0033875 = 222/65535
	0x3F6BE01BE01BE01C,	// 223	0.00340276 = 223/65535
	0x3F6C001C001C001C,	// 224	0.00341802 = 224/65535
	0x3F6C201C201C201C,	// 225	0.00343328 = 225/65535
	0x3F6C401C401C401C,	// 226	0.00344854 = 226/65535
	0x3F6C601C601C601C,	// 227	0.0034638 = 227/65535
	0x3F6C801C801C801D,	// 228	0.00347906 = 228/65535
	0x3F6CA01CA01CA01D,	// 229	0.00349432 = 229/65535
	0x3F6CC01CC01CC01D,	// 230	0.00350958 = 230/65535
	0x3F6CE01CE01CE01D,	// 231	0.00352483 = 231/65535
	0x3F6D001D001D001D,	// 232	0.00354009 = 232/65535
	0x3F6D201D201D201D,	// 233	0.00355535 = 233/65535
	0x3F6D401D401D401D,	// 234	0.00357061 = 234/65535
	0x3F6D601D601D601D,	// 235	0.00358587 = 235/65535
	0x3F6D801D801D801E,	// 236	0.00360113 = 236/65535
	0x3F6DA01DA01DA01E,	// 237	0.00361639 = 237/65535
	0x3F6DC01DC01DC01E,	// 238	0.00363165 = 238/65535
	0x3F6DE01DE01DE01E,	// 239	0.00364691 = 239/65535
	0x3F6E001E001E001E,	// 240	0.00366217 = 240/65535
	0x3F6E201E201E201E,	// 241	0.00367742 = 241/65535
	0x3F6E401E401E401E,	// 242	0.00369268 = 242/65535
	0x3F6E601E601E601E,	// 243	0.00370794 = 243/65535
	0x3F6E801E801E801F,	// 244	0.0037232 = 244/65535
	0x3F6EA01EA01EA01F,	// 245	0.00373846 = 245/65535
	0x3F6EC01EC01EC01F,	// 246	0.00375372 = 246/65535
	0x3F6EE01EE01EE01F,	// 247	0.00376898 = 247/65535
	0x3F6F001F001F001F,	// 248	0.00378424 = 248/65535
	0x3F6F201F201F201F,	// 249	0.0037995 = 249/65535
	0x3F6F401F401F401F,	// 250	0.00381476 = 250/65535
	0x3F6F601F601F601F,	// 251	0.00383001 = 251/65535
	0x3F6F801F801F8020,	// 252	0.00384527 = 252/65535
	0x3F6FA01FA01FA020,	// 253	0.00386053 = 253/65535
	0x3F6FC01FC01FC020,	// 254	0.00387579 = 254/65535
	0x3F6FE01FE01FE020,	// 255	0.00389105 = 255/65535
};

#ifdef __cplusplus
}
#endif
