#pragma once
#include <type_traits>
#include "fixed_string.hpp"

class CompileTimeIfPossible {
private:
	//These are constants which crt.rand use
	constexpr static unsigned Rand_Multiplier = 0x343FD;
	constexpr static unsigned Rand_Increment = 0x269EC3;
	constexpr static unsigned Rand_Modulus = 0x7FFF;
public:
	constexpr static unsigned Rand(unsigned& Seed) {
		Seed = Seed * Rand_Multiplier + Rand_Increment;
		return (Seed >> 0x10) & Rand_Modulus;
	}

	template<class Type>
	constexpr static unsigned Hash(const Type* p) {
		static_assert(sizeof(Type) <= 2, "Type must be character.");

		return *p ? unsigned(*p) + 33 * Hash(p + 1) : 5381;
	}
};

class CompileTime {
private:
	//This function must be inlined for optimization.
	template <auto Index>
	__forceinline static bool RepeatEach(auto func) {
		if constexpr (std::is_invocable_v<decltype(func), std::integral_constant<decltype(Index), Index>>) {
			if constexpr (std::is_same_v<std::invoke_result_t<decltype(func), std::integral_constant<decltype(Index), Index>>, bool>) {
				return func(std::integral_constant<decltype(Index), Index>());
			}
			else {
				func(std::integral_constant<decltype(Index), Index>());
				return true;
			}
		}
		else if constexpr (std::is_invocable_v<decltype(func)>) {
			if constexpr (std::is_same_v<std::invoke_result_t<decltype(func)>, bool>) {
				return func();
			}
			else {
				func();
				return true;
			}
		}
		else func(1 / 0);
	}

public:
	//This function must be inlined for optimization.
	template <auto LoopCount, auto Index = 0>
	__forceinline static void Repeat(auto func) {
		static_assert(LoopCount <= 0x200, "Too big loopcount");

		//These macros are for inline optimization.
		//Template recursive calls ruin the optimization.
#define CheckAndRepeatEach0(N)\
		if constexpr (Index + N < LoopCount) if (!RepeatEach<Index + N>(func)) return
#define CheckAndRepeatEach1(N)\
		CheckAndRepeatEach0(N + 0x00); CheckAndRepeatEach0(N + 0x01); CheckAndRepeatEach0(N + 0x02); CheckAndRepeatEach0(N + 0x03);\
		CheckAndRepeatEach0(N + 0x04); CheckAndRepeatEach0(N + 0x05); CheckAndRepeatEach0(N + 0x06); CheckAndRepeatEach0(N + 0x07)
#define CehckAndRepeatEach2(N)\
		CheckAndRepeatEach1(N + 0x00); CheckAndRepeatEach1(N + 0x08); CheckAndRepeatEach1(N + 0x10); CheckAndRepeatEach1(N + 0x18);\
		CheckAndRepeatEach1(N + 0x20); CheckAndRepeatEach1(N + 0x28); CheckAndRepeatEach1(N + 0x30); CheckAndRepeatEach1(N + 0x38)
#define CehckAndRepeatEach3(N)\
		CehckAndRepeatEach2(N + 0x00); CehckAndRepeatEach2(N + 0x40); CehckAndRepeatEach2(N + 0x80); CehckAndRepeatEach2(N + 0xC0)

		CehckAndRepeatEach3(0x000);
		CehckAndRepeatEach3(0x100);
	}

	consteval static size_t StrLen(const char* str) {
		size_t Len = 0;
		while (str[Len++]);
		return Len;
	}

	consteval static unsigned Rand(unsigned Count, unsigned Seed) {
		for (unsigned i = 0; i < Count; i++)
			CompileTimeIfPossible::Rand(Seed);
		return CompileTimeIfPossible::Rand(Seed);
	}

	template<class Type>
	consteval static unsigned Hash(const Type* p) {
		static_assert(sizeof(Type) <= 2, "Type must be character.");

		return CompileTimeIfPossible::Hash(p);
	}
};

consteval static unsigned operator""h(const char* str, size_t len) { return CompileTime::Hash(str); }
consteval static unsigned operator""h(const wchar_t* str, size_t len) { return CompileTime::Hash(str); }