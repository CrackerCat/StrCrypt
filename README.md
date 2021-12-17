# StrCrypt
Compile-time string crypter library for C++

- Having plain strings stored in the binary file or in memory can help reversering attempts to be much easier.
- If the program is targeted by string detection scans you had to change the strings everytime you get detected.

What this library do?
- Remove string data from .rdata section.
- String data is encrypted compiled-time and decrypted run-time with pseudo random function.(you can customize pseudo random function, default is CRT.rand)
- Each strings invoked has each different seed to decrypt even though strings are same.

example
```
#include <stdio.h>
#include "movstr.h"

int main() {
	char buf[0x100];
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
}
```
