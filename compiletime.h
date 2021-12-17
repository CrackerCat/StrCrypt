#pragma once
#include <type_traits>

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

	constexpr static unsigned Hash(const char* p) {
		return *p ? unsigned(*p) + 33 * Hash(p + 1) : 5381;
	}
};

class CompileTime {
private:
	template <auto Index>
	static bool RepeatEach(auto func) {
		if constexpr (std::is_invocable_v<decltype(func), std::integral_constant<size_t, Index>>) {
			if constexpr (std::is_same_v<std::invoke_result_t<decltype(func), std::integral_constant<size_t, Index>>, bool>) {
				return func(std::integral_constant<size_t, Index>());
			}
			else {
				func(std::integral_constant<size_t, Index>());
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
	template <auto LoopCount, auto Index = 0>
	static void Repeat(auto func) {
		if constexpr (Index + 0 < LoopCount) if (!RepeatEach<Index + 0>(func)) return;
		if constexpr (Index + 1 < LoopCount) if (!RepeatEach<Index + 1>(func)) return;
		if constexpr (Index + 2 < LoopCount) if (!RepeatEach<Index + 2>(func)) return;
		if constexpr (Index + 3 < LoopCount) if (!RepeatEach<Index + 3>(func)) return;
		if constexpr (Index + 4 < LoopCount) if (!RepeatEach<Index + 4>(func)) return;
		if constexpr (Index + 5 < LoopCount) if (!RepeatEach<Index + 5>(func)) return;
		if constexpr (Index + 6 < LoopCount) if (!RepeatEach<Index + 6>(func)) return;
		if constexpr (Index + 7 < LoopCount) if (!RepeatEach<Index + 7>(func)) return;
		if constexpr (Index + 8 < LoopCount) if (!RepeatEach<Index + 8>(func)) return;
		if constexpr (Index + 9 < LoopCount) if (!RepeatEach<Index + 9>(func)) return;
		if constexpr (Index + 10 < LoopCount) Repeat<LoopCount, Index + 10>(func);
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

	consteval static unsigned Hash(const char* p) {
		return CompileTimeIfPossible::Hash(p);
	}
};