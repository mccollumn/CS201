/** ---------------------------------------------
*
* @file		decrypt.c
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assignment 6: Dynamic Mem, File IO, bit ops
*		   
*
* -------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** ---------------------------------------------
* 	
* getArg - Gets arg from cmd line
*
* @param	argc	arg count 
* @param	argv	arg values 
*
* @return 			Argument 
*
* -------------------------------------------- */
char* getArg(int argc, char* argv[]);

/** ---------------------------------------------
* 	
* outputName - Generates name of output file
*
* @param 	inputFilename	Name of input file
*
* @return  					Name of output file
*
* -------------------------------------------- */
char* outputName(char* inputFilename);

/** ---------------------------------------------
* 	
* readFile - Reads file into memory
*
* @param	inputFilename	Name of file to read
* @param 	buffer			File data
*
* @return  					Length of file
*
* -------------------------------------------- */
long readFile(char* inputFilename, unsigned char* data);

/** ---------------------------------------------
* 	
* writeFile - Writes data to file
*
* @param 	outputFilename	Name of file to write
* @param 	pDataToWrite	Pointer to data in mem
* @param 	dataSize		Size of data to write	
*
* -------------------------------------------- */
void writeFile(char* outputFilename, unsigned char* pDataToWrite, long dataSize);

void decode(unsigned char* codedData, unsigned char* decodedData, long dataSize);

int flipBits(unsigned char* codedByte);

unsigned int swapNibbles(unsigned char* codedByte);

int main(int argc, char* argv[]) {
	char* inputFilename;
	char* outputFilename;
	inputFilename = getArg(argc, argv);
	outputFilename = outputName(inputFilename);

	unsigned char* data;
	long dataSize;
	dataSize = readFile(inputFilename, data);

	writeFile(outputFilename, data, dataSize);

	printf("Author:\t\tNick McCollum\n");
	printf("Input file:\t%s\n", inputFilename);
	printf("File size:\t%d bytes\n", (int)dataSize);
	printf("Output file:\t%s\n", outputFilename);

	unsigned char* p = data;
	for (int i = 0; i < dataSize; i++) {
		printf("%x ", *p);	
		p++;
	}
	printf("\n");

	unsigned char* decodedData;
//	decode(data, decodedData, dataSize);

//	writeFile(outputFilename, decodedData, dataSize); 

	return 1;
}

//-----------------------------------------------
char* getArg(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(0);
	}

	return argv[1];
}

//-----------------------------------------------
char* outputName(char* inputFilename) {
	int strLength = strlen(inputFilename);
	char* filename = (char*) malloc(sizeof(char) * (strLength + 3));
	strcpy(filename, inputFilename);
	strcat(filename, ".d");
	return filename;
}

//-----------------------------------------------
long readFile(char* inputFilename, unsigned char* data) {
	FILE* pFile;
	long lSize;
	long result;
	unsigned char* buffer;

	pFile = fopen(inputFilename, "rb");
	if (pFile == NULL) {
		fputs("File could not be opened\n", stderr);
		exit(0);
	}

	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	buffer = (unsigned char*) malloc (lSize);
	if (buffer == NULL) {
		fputs("Memory error reading file\n", stderr);
		exit(0);
	}

	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize) {
		fputs("Error reading file\n", stderr);
		exit(0);
	}

	unsigned char* p = buffer;
	for (int i = 0; i < lSize; i++) {
		printf("%x ", *p);	
		p++;
	}
	printf("\n");

	data = (unsigned char*) malloc (lSize + 1);
	memcpy(data, buffer, lSize);

	fclose(pFile);
	
	return result;
}

//-----------------------------------------------
void writeFile(char* outputFilename, unsigned char* dataToWrite, long dataSize) {
	FILE* pFile;
	long result;

	if (dataToWrite == NULL) {
		fputs("Nothing to write\n", stderr);
		exit(0);
	}

	pFile = fopen(outputFilename, "wb");
	if (pFile == NULL) {
		fputs("Could not open file for writing\n", stderr);
	}

	result = fwrite(dataToWrite, 1, dataSize, pFile);
	if (result != dataSize) {
		fputs("File write error\n", stderr);
	}

	fclose(pFile);
}

//-----------------------------------------------
int flipBits(unsigned char* codedByte) {
	return *codedByte ^ 0xff;
}

//-----------------------------------------------
unsigned int swapNibbles(unsigned char* codedByte) {
	return (((int)codedByte << 4) & 0xff) + ((int)codedByte >> 4);
}

//-----------------------------------------------
void decode(unsigned char* codedData, unsigned char* decodedData, long dataSize) {
	unsigned char result[dataSize];
	unsigned char* p = codedData;
//	char* p = codedData;

	for (int i = 0; i < dataSize; i++) {
		printf("Bit: %x", *p);

	 	unsigned char swapc = (((int)p << 4) & 0xff) + ((int)p >> 4);
/*
		int swap = swapNibbles(p);
		printf(" - Swapped bit: %x", swap);
		printf(" - Swapped char: %c\n", (char) swap);
*/
		printf(" - Swapped bit: %x", swapc);
		printf(" - Swapped char: %c\n", (unsigned char) swapc);
		result[i] = (unsigned char)swapc;


/*
		int flip = flipBits(p);
		printf(" - Flipped bit: %x", flip);
		printf(" - Flipped char: %c\n", (char) flip);
		result[i] = (char)flip;
*/

		p++;
	}

	printf("%s\n", result);
}
