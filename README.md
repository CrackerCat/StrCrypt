# StrCrypt
Compile-time string crypter library for C++

- Having plain strings stored in the binary file or in memory can help reversering attempts to be much easier.
- If the program is targeted by string detection scans you had to change the strings everytime you get detected.

What this library do?
- Remove string data from .rdata section.
- String data is encrypted compiled-time and decrypted run-time with pseudo random function.(you can customize pseudo random function, default is CRT.rand)
- String data is can not be seem by IDA code analisis because getting string need to decyrpt with pseudo random function and unique seed.
- It can be integrated with code obfuscation with VMProtect or Themida because binary code has string data.

example
```
#include <stdio.h>
#include "movstr.h"

int main() {
	char buf[0x100];
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
	std::string str;

	MovStdString(str, "abcdefghijklmnopqrstuvwxyz\n");
	printf(str.c_str());

	printf(StdString("abcdefghijklmnopqrstuvwxyz\n").c_str());
}
```
![Desktop Screenshot 2021 12 09 - 02 13 32 86](https://user-images.githubusercontent.com/32794121/146554837-0c1c2292-c04c-475a-9447-bbce88db041f.jpg)

How about binary code? let's see.

![Desktop Screenshot 2021 12 09 - 02 13 32 86 - 복사본](https://user-images.githubusercontent.com/32794121/146556071-86207fcf-8a94-4b0d-b9ec-d1f25270235f.jpg)

```
__declspec(noinline) static void DecryptStringWithCrtRand(char* szDst, unsigned Seed) {
	unsigned i = 0;
	srand(Seed);
	do {
		szDst[i] ^= (char)rand();
	} while (szDst[i++]);
}
```
