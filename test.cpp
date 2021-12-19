#include <iostream>
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