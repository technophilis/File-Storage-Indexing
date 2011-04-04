/*
 * main.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: Mahmoud
 *
 *      The main file where the library is tested
 */

#include "FileHeap.h"
#include <cstdlib>
#include <time.h>
#include "Helper.h"

char * random_generator(int size);

int main() {
	FileHeap file_heap("DATA_1.dat");

	FilePointer *small_pointer = file_heap.alloc(16);
	FilePointer *big_pointer = file_heap.alloc(16 * 4);

	/*char* small_data = random_generator(10);
	file_heap.setValue(small_pointer, small_data, 10);

	char* big_data = random_generator(3000);
	file_heap.setValue(big_pointer, big_data, 3000);

	char* small_data_retrieved = file_heap.getValue(small_pointer);
	cout << small_data_retrieved << endl;

	char* big_data_retrieved = file_heap.getValue(big_pointer);
	cout << big_data_retrieved << endl;

	delete [] small_data;
	delete [] big_data; */

	delete small_pointer;
	delete big_pointer;

	return 0;
}


char * random_generator(int size) {
	char * data = new char[size];
	srand(time(NULL));
	for (int i = 0; i < size; i++) {

	}
	return data;
}
