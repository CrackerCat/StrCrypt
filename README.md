# StrCrypt
Compile-time string crypter library for C++

- Having plain strings stored in the binary file or in memory can help reversering attempts to be much easier.
- If the program is targeted by string detection scans you had to change the strings everytime you get detected.

What this library do?
- String data is encrypted compiled-time and decrypted run-time with pseudo random function. (you can customize pseudo random function, default is CRT.rand)
- String data is can not be seem by IDA code analisis because getting string need to decyrpt with pseudo random function and unique seed.

example usage 
```
#include <iostream>
#include "encrypt_string.h"

int main() {
	printf("Just add 'e' suffix to end of string to encrypt your string.\n"e);
	wprintf(L"C++20 required to compile.\n"e);

	char buf[100];
	printf(buf << "works with c buffer \n"e);

	wchar_t wbuf[100];
	wprintf(wbuf << L"works with c buffer(wchar_t).\n"e);

	std::array<char, 100> stdarr = "works with std::array<char> : = \n"e;
	printf(stdarr.data());
	stdarr << "works with std::array<char> : << \n"e;
	printf(stdarr.data());

	std::array<wchar_t, 100> wstdarr = L"works with std::array<wchar_t> : =\n"e;
	wprintf(wstdarr.data());
	wstdarr << L"works with std::array<wchar_t> : <<\n"e;
	wprintf(wstdarr.data());

	std::string stdstr = "works with std::string : =\n"e;
	printf(stdstr.c_str());
	stdstr << "works with std::string : <<\n"e;
	printf(stdstr.c_str());

	std::wstring wstdstr = L"works with std::wstring : =\n"e;
	wprintf(wstdstr.c_str());
	wstdstr << L"works with std::wstring : <<\n"e;
	wprintf(wstdstr.c_str());
	return 0;
}
```

