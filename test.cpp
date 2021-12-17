#include <iostream>
#include "movstr.h"

int main() {
	char buf[0x100];
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
	MovString(buf, "abcdefghijklmnopqrstuvwxyz\n"); printf(buf);
}