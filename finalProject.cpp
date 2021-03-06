// finalProject.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include<fstream>
#include "fileData.h"
using namespace std;

//numbers must stay in the range from 0-255 handling outofbounds numbers 
int overFlow(int &a) {
	if (a > 255) {
		a = 255;
	}
	else if (a < 0) {
		a = 0;
	}
	else {
		a = a;
	}
	return a;
}
float overFlow(float &a) {
	if (a > 255) {
		a = 255;
	}
	else if (a < 0) {
		a = 0;
	}
	else {
		a = a;
	}
	return a;
}


int main()
{
	unsigned char* pictureOnePixels;
	unsigned char* pictureTwoPixels;
	unsigned char* pictureThreePixels;
	unsigned char* combinedPixels;
	int size;
	//load all the images
	fileData layer1("input/layer1.tga");
	fileData pattern1("input/pattern1.tga");
	//part 1 multiply combine layer1 with pattern1
	size = layer1.getSize();
	pictureOnePixels = layer1.getPixelData();
	pictureTwoPixels = pattern1.getPixelData();
	combinedPixels = pictureTwoPixels;
	for (int i = 0; i < size; i++) {
		float pixel1 = (float)pictureOnePixels[i];
		float pixel2 = (float)pictureTwoPixels[i];
		pixel1 /= 255;
		pixel2 /= 255;
		float pixelCombo = (pixel1 * pixel2 * 255)+.5f;
		combinedPixels[i] = (unsigned char)pixelCombo;
	}
	layer1.writeFile("output/part1",combinedPixels);
	
	fileData layer2("input/layer2.tga");
	fileData car("input/car.tga");
	//part two 
	//subract layer2 and car 
	size = layer2.getSize();
	pictureOnePixels = layer2.getPixelData();
	combinedPixels = pictureOnePixels;
	pictureTwoPixels = car.getPixelData();

	for (int i = 0; i < size; i++) {
		int pixel1 = (int)pictureOnePixels[i];
		int pixel2 = (int)pictureTwoPixels[i];
		int pixelCombo = pixel2 - pixel1;
		pixelCombo = overFlow(pixelCombo);
		combinedPixels[i] = (unsigned char)pixelCombo;
	}
	layer2.writeFile("output/part2", combinedPixels);

	fileData layer1_2("input/layer1.tga");
	fileData pattern2("input/pattern2.tga");
	fileData text("input/text.tga");
	size = pattern2.getSize();
	//part3 
	//multiply layer1 and pattern2 combined with text screen blending 
	pictureOnePixels = layer1_2.getPixelData();
	pictureTwoPixels = pattern2.getPixelData();
	for (int i = 0; i < size; i++) {
		float pixel1 = (float)pictureOnePixels[i];
		float pixel2 = (float)pictureTwoPixels[i];
		pixel1 /= 255;
		pixel2 /= 255;
		float pixelCombo = (pixel1 * pixel2 * 255) + .5f;
		combinedPixels[i] = (unsigned char)pixelCombo;
	}
	//fileData text("text.tga");
	pictureThreePixels = text.getPixelData();
	for (int i = 0; i < size; i++) {
		float pixel1 = (float)combinedPixels[i];
		float pixel2 = (float)pictureThreePixels[i];
		pixel1 /= 255;
		pixel2 /= 255;
		float pixelCombo = ((1 - (1 - pixel1)*(1 - pixel2)) * 255)+.5f;
		combinedPixels[i] = (unsigned char)pixelCombo;
	}
	text.writeFile("output/part3", combinedPixels);

	fileData layer2_2("input/layer2.tga");
	fileData circles("input/circles.tga");
	fileData pattern2_2("input/pattern2.tga");
	size = circles.getSize();
	//part4 
	//multiply layer2 and circles use this new image and use subtract with pattern2
	pictureOnePixels = layer2_2.getPixelData();
	pictureTwoPixels = circles.getPixelData();
	for (int i = 0; i < size; i++) {
		float pixel1 = (float)pictureOnePixels[i];
		float pixel2 = (float)pictureTwoPixels[i];
		pixel1 /= 255;
		pixel2 /= 255;
		float pixelCombo = (pixel1 * pixel2 * 255) + .5f;
		combinedPixels[i] = (unsigned char)pixelCombo;
	}
	pictureThreePixels = pattern2_2.getPixelData();
	for (int i = 0; i < size; i++) {
		float pixel1 = (float)combinedPixels[i];
		float pixel2 = (float)pictureThreePixels[i];
		int pixelCombo = pixel1 - pixel2;
		pixelCombo = overFlow(pixelCombo);
		combinedPixels[i] = (unsigned char)pixelCombo;

	}
	pattern2_2.writeFile("output/part4", combinedPixels);
	fileData layer1_3("input/layer1.tga");
	fileData pattern1_2("input/pattern1.tga");
	size = pattern1_2.getSize();
	//part5
	//layer1 and pattern1 with overlay 
	pictureOnePixels = layer1_3.getPixelData();
	pictureTwoPixels = pattern1_2.getPixelData();

	float pixelCombo;
	for (int i = 0; i < size; i++) {
		float pixel1 = (float)pictureOnePixels[i];
		float pixel2 = (float)pictureTwoPixels[i];
		pixel1 /= 255;
		pixel2 /= 255;
		if (pixel2 <= .5) {
			pixelCombo = (2 * pixel1*pixel2 * 255)+.5f;
			pixelCombo = overFlow(pixelCombo);
			combinedPixels[i] = (unsigned char)pixelCombo;
		}
		else {
			pixelCombo = 1 - 2 * (1 - pixel1)*(1 - pixel2);
			pixelCombo *= 255;
			pixelCombo += .5f;
			pixelCombo = overFlow(pixelCombo);
			combinedPixels[i] = (unsigned char)pixelCombo;
		}
	}
	layer1_3.writeFile("output/part5", combinedPixels);

	//part6 add 200 to the green channel of car 
	fileData car_2("input/car.tga");
	size = car_2.getSize();
	pictureOnePixels = car_2.getPixelData();
	for (int i = 0; i < size; i++) {
		combinedPixels[i] = pictureOnePixels[i];
	}
	for (int i = 1; i < size; i += 3) {
		int pixel =pictureOnePixels[i];
		pixel += 200;
		pixel = overFlow(pixel);
		combinedPixels[i] = pixel;
	}
	car_2.writeFile("output/part6", combinedPixels);

	//part7
	//load car and scale red channel 4 and blue by 0 
	fileData car_3("input/car.tga");
	pictureOnePixels = car_3.getPixelData();
	//red
	for (int i = 0; i < size; i++) {
		combinedPixels[i] = pictureOnePixels[i];
	}
	for (int i = 2; i < size; i += 3) {
		int pixel = pictureOnePixels[i];
		pixel *= 4;
		pixel = overFlow(pixel);
		combinedPixels[i] = pixel;
	}
	//blue
	for (int i = 0; i < size; i += 3) {
		int pixel = combinedPixels[i];
		pixel *= 0;
		pixel = overFlow(pixel);
		combinedPixels[i] = pixel;
	}
	car_3.writeFile("output/part7", combinedPixels);
	//part8 load car and write each channel to a separate file red part8_r.tga 
	fileData car_4("input/car.tga");
	pictureOnePixels = car_3.getPixelData();
	unsigned char* pixel = new unsigned char[car_4.getSize()];
	int index = 0;
	for (unsigned int i = 0; i < car_4.getSize(); i += 3) {
		pixel[index] = pictureOnePixels[i];
		pixel[index + 1] = pictureOnePixels[i];
		pixel[index + 2] = pictureOnePixels[i];
		index += 3;
	}
	car_4.writeFile("output/part8_b", pixel);
	index = 0;
	for (unsigned int i = 1; i < car_4.getSize(); i += 3) {
		pixel[index] = pictureOnePixels[i];
		pixel[index + 1] = pictureOnePixels[i];
		pixel[index + 2] = pictureOnePixels[i];
		index += 3;
	}
	car_4.writeFile("output/part8_g", pixel);
	index = 0;
	for (unsigned int i = 2; i < car_4.getSize(); i += 3) {
		pixel[index] = pictureOnePixels[i];
		pixel[index + 1] = pictureOnePixels[i];
		pixel[index + 2] = pictureOnePixels[i];
		index += 3;
	}
	car_4.writeFile("output/part8_r", pixel);

	//part9 load layer_red layer_green and layer_blue and combine the three files 
	fileData layer_red("input/layer_red.tga");
	fileData layer_green("input/layer_green.tga");
	fileData layer_blue("input/layer_blue.tga");
	pictureOnePixels = layer_red.getPixelData();
	pictureTwoPixels = layer_green.getPixelData();
	pictureThreePixels = layer_blue.getPixelData();

	for (unsigned int i = 0; i < layer_red.getSize(); i+=3) {
		combinedPixels[i] = pictureThreePixels[i];
	}
	for (unsigned int i = 1; i < layer_red.getSize(); i += 3) {
		combinedPixels[i] = pictureTwoPixels[i];
	}
	for (unsigned int i = 2; i < layer_red.getSize(); i += 3) {
		combinedPixels[i] = pictureOnePixels[i];
	}
	layer_red.writeFile("output/part9", combinedPixels);
	
	//part10
	//load text2 and rotate it 180 
	fileData text2("input/text2.tga");
	pictureOnePixels = text2.getPixelData();
	index = 0;
	for (int i = text2.getSize()-1; i >=0; i--) {
		combinedPixels[i] = pictureOnePixels[index];
		index++;
	}
	text2.writeFile("output/part10", combinedPixels);

	//testing that they are all valid 
	unsigned char* pixel1;
	unsigned char*pixel2;
	string name;
	string name2;
	bool match = false;
	for (int i = 1; i < 8; i++) {
		name = "output/part" + to_string(i) + ".tga";
		fileData check(name);
		name = "examples/EXAMPLE_part" + to_string(i) + ".tga";
		fileData example(name);
		pixel1 = check.getPixelData();
		pixel2 = example.getPixelData();
		if (check.idLength == example.idLength) {
			match = true;
			if (check.colorMapType == example.colorMapType) {
				match = true;
				if (check.dataTypeCode == example.dataTypeCode) {
					match = true;
					if (check.dataTypeCode == example.dataTypeCode) {
						match = true;
						if (check.colorMapOrigin == example.colorMapOrigin) {
							match = true;
							if (check.colorMapLength == example.colorMapLength) {
								match = true;
								if (check.colorMapDepth == example.colorMapDepth) {
									match = true;
									if (check.xOrigin == example.xOrigin) {
										match = true;
										if (check.yOrigin == example.yOrigin) {
											match = true;
											if (check.width == example.width) {
												match = true;
												if (check.height == example.height) {
													match = true;
													if (check.bitsPerPixel == example.bitsPerPixel) {
														match = true;
														if (check.imageDescriptor == example.imageDescriptor) {
															match = true;
														}
														else
															match = false;
													}
													else
														match = false;
												}
												else
													match = false;
											}
											else
												match = false;
										}
										else
											match = false;
									}
									else
										match = false;
								}
								else
									match = false;
							}
							else
								match = false;
							}

							else
								match = false;
						}
						else
							match = false;
					}
					else
						match = false;
				}
				else
					match = false;
			}
			else
				match = false;	
		
		for (int i = 0; i < check.getSize(); i++) {
			if (pixel1[i] == pixel2[i]) {
				match = true;
			}
			else {
				match = false;
				break;
			}
		}
		if (match) {
			cout << "The desired and created images match" << endl;
		}
		else
			cout << "There is something wrong with you code as the desired image doesn't match your altered image" << endl;
		match = false;
		cout << "\n";
	}
	//case 8
	for (int i = 0; i < 3; i++) {
		if (i == 1) {
			name = "output/part8_r.tga";
			name2 = "examples/EXAMPLE_part8_r.tga";
		}
		else if (i == 2) {
			name = "output/part8_g.tga";
			name2 = "examples/EXAMPLE_part8_g.tga";
		}
		else {
			name = "output/part8_b.tga";
			name2 = "examples/EXAMPLE_part8_b.tga";
		}
		fileData eight(name);
		fileData example8(name2);
		pixel1 = eight.getPixelData();
		pixel2 = example8.getPixelData();
		if (eight.idLength == example8.idLength) {
			match = true;
			if (eight.colorMapType == example8.colorMapType) {
				match = true;
				if (eight.dataTypeCode == example8.dataTypeCode) {
					match = true;
					if (eight.dataTypeCode == example8.dataTypeCode) {
						match = true;
						if (eight.colorMapOrigin == example8.colorMapOrigin) {
							match = true;
							if (eight.colorMapLength == example8.colorMapLength) {
								match = true;
								if (eight.colorMapDepth == example8.colorMapDepth) {
									match = true;
									if (eight.xOrigin == example8.xOrigin) {
										match = true;
										if (eight.yOrigin == example8.yOrigin) {
											match = true;
											if (eight.width == example8.width) {
												match = true;
												if (eight.height == example8.height) {
													match = true;
													if (eight.bitsPerPixel == example8.bitsPerPixel) {
														match = true;
														if (eight.imageDescriptor == example8.imageDescriptor) {
															match = true;
														}
														else
															match = false;
													}
													else
														match = false;
												}
												else
													match = false;
											}
											else
												match = false;
										}
										else
											match = false;
									}
									else
										match = false;
								}
								else
									match = false;
							}
							else
								match = false;
						}

						else
							match = false;
					}
					else
						match = false;
				}
				else
					match = false;
			}
			else
				match = false;
		}
		else
			match = false;

		for (int i = 0; i < eight.getSize(); i++) {
			if (pixel1[i] == pixel2[i]) {
				match = true;
			}
			else {
				match = false;
				break;
			}
		}
		if (match) {
			cout << "The desired and created images match" << endl;
		}
		else
			cout << "There is something wrong with you code as the desired image doesn't match your altered image" << endl;
		match = false;
		cout << endl;
	}

	for (int i = 9; i < 11; i++) {
		name = "output/part" + to_string(i) + ".tga";
		fileData check(name);
		name = "examples/EXAMPLE_part" + to_string(i) + ".tga";
		fileData example(name);
		pixel1 = check.getPixelData();
		pixel2 = example.getPixelData();
		if (check.idLength == example.idLength) {
			match = true;
			if (check.colorMapType == example.colorMapType) {
				match = true;
				if (check.dataTypeCode == example.dataTypeCode) {
					match = true;
					if (check.dataTypeCode == example.dataTypeCode) {
						match = true;
						if (check.colorMapOrigin == example.colorMapOrigin) {
							match = true;
							if (check.colorMapLength == example.colorMapLength) {
								match = true;
								if (check.colorMapDepth == example.colorMapDepth) {
									match = true;
									if (check.xOrigin == example.xOrigin) {
										match = true;
										if (check.yOrigin == example.yOrigin) {
											match = true;
											if (check.width == example.width) {
												match = true;
												if (check.height == example.height) {
													match = true;
													if (check.bitsPerPixel == example.bitsPerPixel) {
														match = true;
														if (check.imageDescriptor == example.imageDescriptor) {
															match = true;
														}
														else
															match = false;
													}
													else
														match = false;
												}
												else
													match = false;
											}
											else
												match = false;
										}
										else
											match = false;
									}
									else
										match = false;
								}
								else
									match = false;
							}
							else
								match = false;
						}

						else
							match = false;
					}
					else
						match = false;
				}
				else
					match = false;
			}
			else
				match = false;
		}
		else
			match = false;

		for (int i = 0; i < check.getSize(); i++) {
			if (pixel1[i] == pixel2[i]) {
				match = true;
			}
			else {
				match = false;
				break;
			}
		}
		if (match) {
			cout << "The desired and created images match" << endl;
		}
		else
			cout << "There is something wrong with you code as the desired image doesn't match your altered image" << endl;
		match = false;
		cout << "\n";
	}


	return 0;
}

