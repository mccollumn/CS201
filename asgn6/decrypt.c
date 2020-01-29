/** ---------------------------------------------
*
* @file		decrypt.c
* @author	Nick McCollum
* @version	1.0
*
* CS-201 - Assignment 6: Dynamic Mem, File IO, bit ops
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
long readFile(char* inputFilename, unsigned char** data);

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

/** ---------------------------------------------
* 	
* decode - Decodes the provided data,
*		   flipping bits for even bytes,
*		   and swapping nibbles for odd bytes
*
* @param 	codedData	Coded data from file
* @param	decodedData	Data after decoding
* @param	dataSize	Size of data 
*
* -------------------------------------------- */
void decode(unsigned char* codedData, unsigned char* decodedData, long dataSize);

/** ---------------------------------------------
* 	
* flipBits - Flips all bits for provided byte
*
* @param 	codedByte	The byte to flip
*
* @return  				The byte with bits flipped
*
* -------------------------------------------- */
unsigned char flipBits(unsigned char* codedByte);

/** ---------------------------------------------
* 	
* swapNibbles - Swaps nibbles for provided byte
*
* @param 	codedbyte	The byte to swap
*
* @return  				The byte with nibbles swapped
*
* -------------------------------------------- */
unsigned char swapNibbles(unsigned char* codedByte);

//-----------------------------------------------
int main(int argc, char* argv[]) {
	// Get input filename and generate output filename
	char* inputFilename;
	char* outputFilename;
	inputFilename = getArg(argc, argv);
	outputFilename = outputName(inputFilename);

	// Read the file
	unsigned char* data = NULL;
	long dataSize;
	dataSize = readFile(inputFilename, &data);

/*
	// Test - Write file contents to console
	unsigned char* p = data;
	for (int i = 0; i < lSize; i++) {
		printf("%x ", *p);	
		p++;
	}
	printf("\n");
*/

	// Decode the data
	unsigned char* decodedData;
	decodedData = (unsigned char*) malloc(dataSize);
	decode(data, decodedData,  dataSize);

	// Write decoded data to file
	writeFile(outputFilename, decodedData, dataSize); 

	// Print results to console
	printf("Author:\t\tNick McCollum\n");
	printf("Input file:\t%s\n", inputFilename);
	printf("File size:\t%d bytes\n", (int)dataSize);
	printf("Output file:\t%s\n", outputFilename);
	printf("Decryption successful! Output file created.\n");

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
long readFile(char* inputFilename, unsigned char** data) {
	FILE* pFile;
	long lSize;
	long result;

	pFile = fopen(inputFilename, "rb");
	if (pFile == NULL) {
		fputs("File could not be opened\n", stderr);
		exit(0);
	}

	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	*data = (unsigned char*) malloc (lSize);
	if (*data == NULL) {
		fputs("Memory error reading file\n", stderr);
		exit(0);
	}

	result = fread(*data, 1, lSize, pFile);
	if (result != lSize) {
		fputs("Error reading file\n", stderr);
		exit(0);
	}

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
unsigned char flipBits(unsigned char* codedByte) {
	return *codedByte ^ 0xff;
}

//-----------------------------------------------
unsigned char swapNibbles(unsigned char* codedByte) {
	return ((*codedByte & 0x0f) << 4 | (*codedByte & 0xf0) >> 4);
}

//-----------------------------------------------
void decode(unsigned char* codedData, unsigned char* decodedData, long dataSize) {
	unsigned char* p = codedData;
	
	for (int i = 0; i < dataSize; i++) {
		if (i % 2 == 0) {
			decodedData[i] = flipBits(p);
			p++;
		}
		else {
			decodedData[i] = swapNibbles(p);
			p++;
		}
	}	

/*
	// Test - print decode results to console
	unsigned char result[dataSize];
	unsigned char* p = codedData;

	for (int i = 0; i < dataSize; i++) {
		printf("Bit: %x", *p);

	 	unsigned char swapc = swapNibbles(p);
		printf(" - Swapped bit: %x", swapc);
		printf(" - Swapped char: %c\n", (unsigned char) swapc);
		result[i] = swapc;

		unsigned char flip = flipBits(p);
		printf(" - Flipped bit: %x", flip);
		printf(" - Flipped char: %c\n", (unsigned char) flip);
		results[i] = (unsigned char)flip;

		p++;
	}

	printf("%s\n", result);
*/
}
