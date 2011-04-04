/*
 * FileHeap.h
 *
 *  Created on: Apr 4, 2011
 *      Author: Mahmoud
 */

#ifndef FILEHEAP_H_
#define FILEHEAP_H_

#include <fstream>

using namespace std;

/*
 * This class models a pointer to a chunk of data within the file.
 * address: the index where the chunk is located relative to the start of the file
 * size: the size of the chunk in bytes
 */
class FilePointer {
private:
	int address;
	int size;
public:
	FilePointer();
	FilePointer(int address, int size);
	~FilePointer();
	int getAddress();
	void setAddress(int address);
	int getSize();
	void setSize(int size);
};


/*
 * This class incorporates the memory allocation operations that can be performed on the file.
 * storage_file: the file that will hold the data
 */
class FileHeap {
private:
	fstream storage_file;
public:
	FileHeap(string storage_file_name);
	~FileHeap();

	/* allocates a chuck of data of a given size */
	FilePointer* alloc(int size);

	/* frees the space located at a given location in the file */
	void free(const FilePointer& pointer);

	/* returns the value of the data at a given location in the file */
	char * getValue(const FilePointer& pointer);

	/* sets the value of data at a given location in the file */
	void setValue(const FilePointer& pointer, const char * data, int size);
};

#endif /* FILEHEAP_H_ */
