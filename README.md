# StrCrypt
Compile-time string crypter library for C++

- Having plain strings stored in the binary file or in memory can help reversering attempts to be much easier.
- If the program is targeted by string detection scans you had to change the strings everytime you get detected.

example
```
#include "movstr.h"

void main() {
  char buf[256];
  MovStr(buf, "TestString");  //"TestString" does not remain in .rdata section anymore.
  printf(buf);
}
```

- Binary not encrypted(substitute "MovStr" to "strcpy")
![0](https://user-images.githubusercontent.com/32794121/117529344-1ac5c280-b012-11eb-8356-7d651fa578ab.jpg)
- Binary encrypted with STRDEF_RAW
![1](https://user-images.githubusercontent.com/32794121/117529351-26b18480-b012-11eb-9747-38b036ce727e.jpg)
- Binary encrypted with STRDEF_ENCRYPT_KEY1
![2](https://user-images.githubusercontent.com/32794121/117529359-2adda200-b012-11eb-9df7-733d2f471884.jpg)
- Binary encrypted with STRDEF_ENCRYPT_KEY2
![3](https://user-images.githubusercontent.com/32794121/117529364-2e712900-b012-11eb-8cf4-fe961c5e25c5.jpg)
