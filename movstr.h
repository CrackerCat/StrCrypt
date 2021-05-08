#pragma once

#ifdef __clang__
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include "CompileTimeRandom.h"
#include <intrin.h>

#define STR_CHAR(s, i) (i < sizeof(s) ? s[i] : 0)
#define STR_UNSIGNED(s, i) ((STR_CHAR(s, i + 0) << 0) + (STR_CHAR(s, i + 1) << 8) + (STR_CHAR(s, i + 2) << 16) + (STR_CHAR(s, i + 3) << 24))

#define STRDEF_ENCRYPT_KEY2(s, i) \
if constexpr (i < sizeof(s)) {\
	unsigned* p = (unsigned*)&b[i];\
	constexpr unsigned v = STR_UNSIGNED(s, i);\
	constexpr unsigned k1 = (unsigned)DYC_RAND_NEXT;\
	constexpr unsigned k2 = (unsigned)DYC_RAND_NEXT;\
	unsigned t;\
	_addcarry_u32(0, (v ^ k1) + k2, -(int)k2, &t);\
	*p = t ^ k1;\
	_ReadWriteBarrier();\
}

#define STRDEF_ENCRYPT_KEY1(s, i) \
if constexpr (i < sizeof(s)) {\
	unsigned* p = (unsigned*)&b[i];\
	constexpr unsigned v = STR_UNSIGNED(s, i);\
	constexpr unsigned k = (unsigned)DYC_RAND_NEXT;\
	unsigned t;\
	_addcarry_u32(0, v + k, -(int)k, &t);\
	*p = t;\
	_ReadWriteBarrier();\
}

#define STRDEF_RAW(s, i) \
if constexpr (i < sizeof(s)) {\
	unsigned* p = (unsigned*)&b[i];\
	constexpr unsigned v = STR_UNSIGNED(s, i);\
	*p = v;\
	_ReadWriteBarrier();\
}

#ifdef DEBUG
#define STRDEF STRDEF_RAW
#else
#define STRDEF STRDEF_ENCRYPT_KEY2
#endif

#define MovStr(dst, s) [](char* b) {\
STRDEF(s, 0x00)\
STRDEF(s, 0x04)\
STRDEF(s, 0x08)\
STRDEF(s, 0x0C)\
STRDEF(s, 0x10)\
STRDEF(s, 0x14)\
STRDEF(s, 0x18)\
STRDEF(s, 0x1C)\
STRDEF(s, 0x20)\
STRDEF(s, 0x24)\
STRDEF(s, 0x28)\
STRDEF(s, 0x2C)\
STRDEF(s, 0x30)\
STRDEF(s, 0x34)\
STRDEF(s, 0x38)\
STRDEF(s, 0x3C)\
STRDEF(s, 0x40)\
STRDEF(s, 0x44)\
STRDEF(s, 0x48)\
STRDEF(s, 0x4C)\
STRDEF(s, 0x50)\
STRDEF(s, 0x54)\
STRDEF(s, 0x58)\
STRDEF(s, 0x5C)\
STRDEF(s, 0x60)\
STRDEF(s, 0x64)\
STRDEF(s, 0x68)\
STRDEF(s, 0x6C)\
STRDEF(s, 0x70)\
STRDEF(s, 0x74)\
STRDEF(s, 0x78)\
STRDEF(s, 0x7C)\
STRDEF(s, 0x80)\
STRDEF(s, 0x84)\
STRDEF(s, 0x88)\
STRDEF(s, 0x8C)\
STRDEF(s, 0x90)\
STRDEF(s, 0x94)\
STRDEF(s, 0x98)\
STRDEF(s, 0x9C)\
STRDEF(s, 0xA0)\
STRDEF(s, 0xA4)\
STRDEF(s, 0xA8)\
STRDEF(s, 0xAC)\
STRDEF(s, 0xB0)\
STRDEF(s, 0xB4)\
STRDEF(s, 0xB8)\
STRDEF(s, 0xBC)\
STRDEF(s, 0xC0)\
STRDEF(s, 0xC4)\
STRDEF(s, 0xC8)\
STRDEF(s, 0xCC)\
STRDEF(s, 0xD0)\
STRDEF(s, 0xD4)\
STRDEF(s, 0xD8)\
STRDEF(s, 0xDC)\
STRDEF(s, 0xE0)\
STRDEF(s, 0xE4)\
STRDEF(s, 0xE8)\
STRDEF(s, 0xEC)\
STRDEF(s, 0xF0)\
STRDEF(s, 0xF4)\
STRDEF(s, 0xF8)\
STRDEF(s, 0xFC)\
return b;}(dst)
