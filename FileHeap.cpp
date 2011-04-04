/*
 * FileHeap.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: Mahmoud
 */

#include "FileHeap.h"
#include "Helper.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

FilePointer::FilePointer() {
	this->address = 0;
	this->size = 0;
}

FilePointer::FilePointer(int address, int size) {
	this->address = address;
	this->size = size;
}

FilePointer::~FilePointer() {
}

int FilePointer::getAddress() {
	return address;
}

void FilePointer::setAddress(int address) {
		this->address = address;
}

int FilePointer::getSize() {
	return size;
}

void FilePointer::setSize(int size) {
	this->size = size;
}

FileHeap::FileHeap(string storage_file_name) {
	ofstream storage_helper(storage_file_name.c_str());

	storage_file.open(storage_file_name.c_str(), ios::in | ios::out);

	if (!storage_file.is_open()) {
		cerr << "Unable to open storage file '" << storage_file_name << "'. Exiting..." << endl;
		exit(0);
	}

	cout << "Storage file '" << storage_file_name << "' successfully opened. Continuing with operations..." << endl;
	cout << "Initializing file's heap..." << endl;

	storage_file.write(int_to_bytes(0), 4);
}

FileHeap::~FileHeap() {
	cout << "Closing storage file..." << endl;
	storage_file.close();
}

/*
 * The heap is a sequence of integers and actual data
 * every chunk of data is contained between two integers (|8| 8 bytes |8| - 8 bytes available) which represent the size of the chunk
 * a negative size means that the chunk is reserved (|-8| 8 bytes |-8| - 8 bytes reserved)
 */
FilePointer* FileHeap::alloc(int size) {
	cout << "Allocating a data chunk of size " << size << endl;
	FilePointer *file_pointer = new FilePointer();
	file_pointer->setSize(size);
	char * size_in_bytes = int_to_bytes(size);

	storage_file.seekp(0);

	int chunk_size = -1;
	char chunk_size_bytes[4];
	storage_file.read(chunk_size_bytes, 4);
	chunk_size = bytes_to_int(chunk_size_bytes);
	while (chunk_size < 0 || (chunk_size != 0 && chunk_size < size)) {
		storage_file.seekp(4 + abs(chunk_size), ios_base::cur);
		storage_file.read(chunk_size_bytes, 4);
		chunk_size = bytes_to_int(chunk_size_bytes);
	}

	cout << "Free space found at location " << storage_file.tellp() << endl;

	file_pointer->setAddress(storage_file.tellp());
	storage_file.seekp(-4, ios_base::cur);
	storage_file.write(size_in_bytes, 4);
	storage_file.seekp(size, ios_base::cur);
	storage_file.write(int_to_bytes(size), 4);

	if (chunk_size == 0) {
		storage_file.write(int_to_bytes(0), 4);
	} else {
		int new_chunk_size = chunk_size - size;
		storage_file.write(int_to_bytes(new_chunk_size), 4);
		storage_file.seekp(new_chunk_size, ios_base::cur);
		storage_file.write(int_to_bytes(new_chunk_size), 4);
	}

	return file_pointer;
}

void FileHeap::free(const FilePointer& pointer) {

}

char * FileHeap::getValue(const FilePointer& pointer) {
	return 0;
}

void FileHeap::setValue(const FilePointer& pointer, const char * data, int size) {

}

