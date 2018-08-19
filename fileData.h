#pragma once
#include<string>
#include<vector>
using namespace std;

class fileData {
	//file data
	//for testing sake
public:
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
	int size;
	unsigned char* pixelData;
	fileData(string);
	unsigned char* getPixelData();
	int getSize();
	int getHeight();
	int getWidth();
	void writeFile(string fileName, unsigned char* pixels);
	
};