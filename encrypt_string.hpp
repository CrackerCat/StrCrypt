#pragma warning(disable : 4455)
#pragma once

#include <string>
#include <atomic>
#include "fixed_string.hpp"
#include "compiletime.hpp"

template <class Type>
__declspec(noinline) void DecryptString(Type* Dst, unsigned Seed) noexcept {
	static_assert(sizeof(Type) <= 2, "Type must be character.");

	unsigned i = 0;
	do {
		Dst[i] ^= (Type)CompileTimeIfPossible::Rand(Seed);
	} while (Dst[i++]);
}

template <class Type>
__declspec(noinline) void DecryptStringWithCrtRand(Type* Dst, unsigned Seed) noexcept {
	static_assert(sizeof(Type) <= 2, "Type must be character.");

	unsigned i = 0;
	srand(Seed);
	do {
		Dst[i] ^= (Type)rand();
	} while (Dst[i++]);
}

template <fixstr::basic_fixed_string Src, class Type>
Type* MovString(Type* Dst) noexcept {
	static_assert(sizeof(Src[0]) == sizeof(Type), "Type mismatch");
	static_assert(sizeof(Type) <= 2, "Type must be character.");

	constexpr unsigned TimeSeed =
		(__TIME__[7] - '0') * 1 + (__TIME__[6] - '0') * 10 +
		(__TIME__[4] - '0') * 60 + (__TIME__[3] - '0') * 600 +
		(__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000;
	constexpr unsigned Seed = CompileTime::Rand(0, TimeSeed * CompileTime::Hash(Src.data()));

	//This lambda must be inlined for optimization.
	CompileTime::Repeat<Src.size() + 1>([&](auto Index) [[msvc::forceinline]] {
		if constexpr (Index % 4 == 0) _ReadWriteBarrier();
		//This for making sure original Src string never leak by constexpr assignment.
		constexpr Type ConstValue = Src[Index] ^ (Type)CompileTime::Rand(Index, Seed);
		Dst[Index] = ConstValue;
	});

	DecryptStringWithCrtRand(Dst, Seed);
	//DecryptString(Dst, Seed);
	return Dst;
}

template <fixstr::basic_fixed_string Src, size_t N, class Type = decltype(Src)::value_type>
Type* MovArray(Type(&Dst)[N]) noexcept {
	static_assert(N >= Src.size() + 1, "Array size is less than string.");
	return MovString<Src>(Dst);
}

template <fixstr::basic_fixed_string Src, size_t N, class Type = decltype(Src)::value_type>
std::array<Type, N>& MovStdArray(std::array<Type, N>& Dst) noexcept {
	static_assert(N >= Src.size() + 1, "Array size is less than string.");
	MovString<Src>(Dst.data());
	return Dst;
}

template <fixstr::basic_fixed_string Src, class Type = decltype(Src)::value_type>
std::basic_string<Type>& MovStdString(std::basic_string<Type>& Dst) noexcept {
	Dst.resize(Src.size());
	MovString<Src>(Dst.data());
	return Dst;
}

template <fixstr::basic_fixed_string Src, class Type = decltype(Src)::value_type>
const std::basic_string<Type> MakeStdString() noexcept {
	std::basic_string<Type> Dst;
	Dst.resize(Src.size());
	MovString<Src>(Dst.data());
	return Dst;
}

#define ElementType(Element) std::remove_const_t<std::remove_reference_t<decltype(*Element.begin())>>

template <fixstr::basic_fixed_string Src>
class EncryptedString {
private:
	mutable ElementType(Src) Temp[Src.size() + 1];
public:
	//This constructor make compiler not initialize temp array to 0
	EncryptedString() {}
	operator const ElementType(Src)* () const noexcept {
		return MovArray<Src>(Temp);
	}
};

#ifndef __INTELLISENSE__
template <fixstr::basic_fixed_string Src>
ElementType(Src)* operator<<(ElementType(Src)* Dst, const EncryptedString<Src> Str) noexcept {
	return MovString<Src>(Dst);
}

template <fixstr::basic_fixed_string Src, size_t M>
std::array<ElementType(Src), M>& operator<<(std::array<ElementType(Src), M>& Dst, const EncryptedString<Src> Str) noexcept {
	return MovStdArray<Src, M>(Dst);
}

template <fixstr::basic_fixed_string Src>
std::basic_string<ElementType(Src)>& operator<<(std::basic_string<ElementType(Src)>& Dst, const EncryptedString<Src> Str) noexcept {
	return MovStdString<Src>(Dst);
}

template <fixstr::basic_fixed_string Src>
const EncryptedString<Src> operator""e() noexcept {
	return EncryptedString<Src>();
}

template <fixstr::basic_fixed_string Src>
const std::basic_string<ElementType(Src)> operator""es() noexcept {
	return MakeStdString<Src>();
}
#else
char* operator<<(char* Dst, const EncryptedString<""> Str);
wchar_t* operator<<(wchar_t* Dst, const EncryptedString<L""> Str);
template <size_t M> std::array<char, M>& operator<<(std::array<char, M>& Dst, const EncryptedString<""> Str);
template <size_t M> std::array<wchar_t, M>& operator<<(std::array<wchar_t, M>& Dst, const EncryptedString<L""> Str);
std::basic_string<char>& operator<<(std::basic_string<char>& Dst, const EncryptedString<""> Str);
std::basic_string<wchar_t>& operator<<(std::basic_string<wchar_t>& Dst, const EncryptedString<L""> Str);
const EncryptedString<""> operator""e(const char*, size_t);
const EncryptedString<L""> operator""e(const wchar_t*, size_t);
std::string operator""es(const char*, size_t);
std::wstring operator""es(const wchar_t*, size_t);
#endif