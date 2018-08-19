#include"fileData.h"
#include<string>
#include<fstream>
#include<Windows.h>
#include<iostream>
#include<vector>

fileData::fileData(string name) {
	//getting data 
	ifstream picture(name, ios_base::binary);
	picture.read(&idLength, 1);
	picture.read(&colorMapType, 1);
	picture.read(&dataTypeCode, 1);
	picture.read((char*)&colorMapOrigin, 2);
	picture.read((char*)&colorMapLength, 2);
	picture.read(&colorMapDepth, 1);
	picture.read((char*)&xOrigin, 2);
	picture.read((char*)&yOrigin, 2);
	picture.read((char*)&width, 2);
	picture.read((char*)&height, 2);
	picture.read(&bitsPerPixel, 1);
	picture.read(&imageDescriptor, 1);
	//each pixel has 3 values associated with it R,G,B
	size = 3 * width * height;
	pixelData = new unsigned char[size];
	//first component is blue,green,red
	for (int i = 0; i < size; i++) {
		picture.read((char*)&pixelData[i], 1);
	}
	
}
unsigned char* fileData::getPixelData() {
	return pixelData;
}
int fileData::getSize() {
	return size;
}
int fileData::getHeight() {
	return height;
}
int fileData::getWidth() {
	return width;
}
void fileData::writeFile(string fileName, unsigned char* pixels) {
	ofstream outputFile(fileName + ".tga", ios_base::binary);
	outputFile.write((char*)&idLength, 1);
	outputFile.write((char*)&colorMapType, 1);
	outputFile.write((char*)&dataTypeCode, 1);
	outputFile.write((char*)&colorMapOrigin, 2);
	outputFile.write((char*)&colorMapLength, 2);
	outputFile.write((char*)&colorMapDepth, 1);
	outputFile.write((char*)&xOrigin, 2);
	outputFile.write((char*)&yOrigin, 2);
	outputFile.write((char*)&width, 2);
	outputFile.write((char*)&height, 2);
	outputFile.write((char*)&bitsPerPixel, 1);
	outputFile.write((char*)&imageDescriptor, 1);
	for (int i = 0; i < size; i++) {
		outputFile.write((char*)&pixels[i], 1);
	}
}
