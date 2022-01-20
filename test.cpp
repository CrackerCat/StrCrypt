#include <iostream>
#include "encrypt_string.h"

int main() {
	printf("Just add 'e' suffix to end of string to encrypt your string.\n"e);
	wprintf(L"C++20 required to compile.\n"e);

	char buf[100];
	printf(buf << "works with char buffer \n"e);

	wchar_t wbuf[100];
	wprintf(wbuf << L"works with wchar_t buffer.\n"e);

	std::array<char, 100> stdarr = "works with std::array<char> : constructor\n"e;
	printf(stdarr.data());
	stdarr = "works with std::array<char> : assignment\n"e;
	printf(stdarr.data());

	std::array<wchar_t, 100> wstdarr = L"works with std::array<wchar_t> : constructor\n"e;
	wprintf(wstdarr.data());
	wstdarr = L"works with std::array<wchar_t> : assignment\n"e;
	wprintf(wstdarr.data());

	std::string stdstr = "works with std::string : constructor\n"e;
	printf(stdstr.c_str());
	stdstr = (std::string)"works with std::string : assignment\n"e;
	printf(stdstr.c_str());

	std::wstring wstdstr = L"works with std::wstring : constructor\n"e;
	wprintf(wstdstr.c_str());
	wstdstr = (std::wstring)L"works with std::wstring : assignment\n"e;
	wprintf(wstdstr.c_str());
	return 0;
}