/*
 * Helper.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: username
 */

#include "Helper.h"
#include <stdio.h>

using namespace std;

char * int_to_bytes(int integer) {
	char * bytes = new char[4];
	bytes[3] = ((char)(integer)) & 0xFF;
	bytes[2] = ((char)(integer >> 8)) & 0xFF;
	bytes[1] = ((char)(integer >> 16)) & 0xFF;
	bytes[0] = ((char)(integer >> 24)) & 0xFF;
	return bytes;
}

int bytes_to_int(const char bytes[]) {
	int integer = bytes[0];
	for (int i = 1; i < 4; i++) {
		integer = (integer << 8) + bytes[i];
	}
	return integer;
}

void helper_test() {
	char * res = int_to_bytes(16);
	for (int i = 0; i < 4; i++) printf("%X ", res[i]);
	printf("\n");
}
