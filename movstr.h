#pragma once
#include <string>
#include <atomic>
#include "fixed_string.hpp"
#include "compiletime.h"

__declspec(noinline) static void DecryptString(char* szDst, unsigned Seed) {
	unsigned i = 0;
	do {
		szDst[i] ^= (char)CompileTimeIfPossible::Rand(Seed);
	} while (szDst[i++]);
}

__declspec(noinline) static void DecryptStringWithCrtRand(char* szDst, unsigned Seed) {
	unsigned i = 0;
	srand(Seed);
	do {
		szDst[i] ^= (char)rand();
	} while (szDst[i++]);
}

template <fixstr::basic_fixed_string szSrc, size_t Counter>
__forceinline static char* MovString_Template(char* szDst) {
	constexpr unsigned TimeSeed =
		(__TIME__[7] - '0') * 1 + (__TIME__[6] - '0') * 10 +
		(__TIME__[4] - '0') * 60 + (__TIME__[3] - '0') * 600 +
		(__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000;
	constexpr unsigned Seed = CompileTime::Rand(0, unsigned(TimeSeed * Counter));
	CompileTime::Repeat<szSrc.size() + 1>([&](auto Index) [[msvc::forceinline]] {
		if constexpr (Index % 4 == 0) std::atomic_thread_fence(std::memory_order_acq_rel);
		szDst[Index] = szSrc[Index] ^ (char)CompileTime::Rand((unsigned)Index, Seed);
		});
	DecryptStringWithCrtRand(szDst, Seed);
	//DecryptString(szDst, Seed);
	return szDst;
}

template <fixstr::basic_fixed_string szSrc, size_t Counter>
__forceinline static std::string& MovStdString_Template(std::string& szDst) {
	szDst.resize(szSrc.size());
	MovString_Template<szSrc, Counter>(szDst.data());
	return szDst;
}

template <fixstr::basic_fixed_string szSrc, size_t Counter>
__forceinline static std::string StdString_Template() {
	std::string szDst(szSrc.size(), 0);
	MovString_Template<szSrc, Counter>(szDst.data());
	return szDst;
}

#define MovString(szDst, szSrc) MovString_Template<szSrc, __COUNTER__>(szDst)
#define MovStdString(szDst, szSrc) MovStdString_Template<szSrc, __COUNTER__>(szDst)
#define StdString(szSrc) StdString_Template<szSrc, __COUNTER__>()