# StrCrypt
Compile-time string crypter library for C++

- Having plain strings stored in the binary file or in memory can help reversering attempts to be much easier.
- If the program is targeted by string detection scans you had to change the strings everytime you get detected.

What this library do?
- Remove string data from .rdata section.
- String data is encrypted compiled-time and decrypted run-time with pseudo random function.(you can customize pseudo random function, default is CRT.rand)
- String data is can not be seem by IDA code analisis because getting string need to decyrpt with pseudo random function and unique seed.
- It can be integrated with code obfuscation with VMProtect or Themida because binary code has string data.

example usage 
```
//Decrypt string and put into buffer.
char* operator<<(char* Dst, const EncryptedString<"String"> Str);

//Decrypt unicode string and put into buffer.
wchar_t* operator<<(wchar_t* Dst, const EncryptedString<L"String"> Str);

//Decrypt string and put into char std::array.
template <size_t M> std::array<char, M>& operator<<(std::array<char, M>& Dst, const EncryptedString<"String"> Str);

//Decrypt unicode string and put into wchar_t std::array.
template <size_t M> std::array<wchar_t, M>& operator<<(std::array<wchar_t, M>& Dst, const EncryptedString<L"String"> Str);

//Decrypt string and put into std::string.
std::basic_string<char>& operator<<(std::basic_string<char>& Dst, const EncryptedString<"String"> Str);

//Decrypt unicode string and put into std::wstring.
std::basic_string<wchar_t>& operator<<(std::basic_string<wchar_t>& Dst, const EncryptedString<L"String"> Str);

//Decrypt string and get const char* pointer.
const EncryptedString<"String"> operator""e(const char*, size_t);

//Decrypt unicode string and get const wchar_t* pointer.
const EncryptedString<L"String"> operator""e(const wchar_t*, size_t);

//Decrypt string and get std::string.
std::string operator""es(const char*, size_t);

//Decrypt unicode string and get std::wstring.
std::wstring operator""es(const wchar_t*, size_t);

#include <stdio.h>
#include <string>
#include "encrypt_string.hpp"

int main() {
	printf("Just add 'e' suffix to end of string to encrypt your string. C++20 required to compile.\n"e);
	wprintf(L"All strings protected are encrypted in .text section and never shown at .rdata section.\n"e);

	printf("Compiler knows previous string constant is not valid so decrypted string in stack maybe overwrited by current string.\n"e);
	wprintf(L"Don't worry about stack usage in using encrypted string constant.\n"e);

	char buf[100];
	printf(buf << "This operator put string to buffer.\n"e);

	wchar_t wbuf[100];
	wprintf(wbuf << L"Me too!\n"e);

	std::array<char, 100> stdarr;
	stdarr << "You can put your string into std::array also.\n"e;
	printf(stdarr.data());

	std::array<wchar_t, 100> wstdarr;
	wstdarr << L"If you are using std::array, This operator checks array size too.\n"e;
	wprintf(wstdarr.data());

	std::string stdstr = "you need to adding es for getting std::string object.\n"es;
	printf(stdstr.c_str());

	std::wstring wstdstr;
	wstdstr << L"Using '<<' operator is more recommended because of less overhead.\n"e;
	wprintf(wstdstr.c_str());
	return 0;
}
```
![Desktop Screenshot 2021 12 09 - 02 13 32 86](https://user-images.githubusercontent.com/32794121/146677926-9caa8741-f661-4a08-9762-3b792601f6ee.jpg)

![Desktop Screenshot 2021 12 09 - 02 13 32 86 - 복사본 (2)](https://user-images.githubusercontent.com/32794121/146679649-488a3784-b3e2-4c18-a339-92286dc59ae7.jpg)


How about binary code? let's see.

![Desktop Screenshot 2021 12 09 - 02 13 32 86 - 복사본](https://user-images.githubusercontent.com/32794121/146678487-24bc9584-e44b-40d6-9394-07eaf6d12221.jpg)


```
template <class Type>
__declspec(noinline) void DecryptStringWithCrtRand(Type* Dst, unsigned Seed) noexcept {
	static_assert(sizeof(Type) <= 2, "Type must be character.");

	unsigned i = 0;
	srand(Seed);
	do {
		Dst[i] ^= (Type)rand();
	} while (Dst[i++]);
}
```
