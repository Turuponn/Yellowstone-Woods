#include "BMP_Loader.h"
#include <stdio.h> 
#include "Library\GameError.h"

#ifdef _MSC_VER
#define DISABLE_C4996   __pragma(warning(push)) __pragma(warning(disable:4996))
#define ENABLE_C4996    __pragma(warning(pop))
#else
#define DISABLE_C4996
#define ENABLE_C4996
#endif

BMP_Loader::BMP_Loader() {

}
BMP_Loader::~BMP_Loader() {

}

void BMP_Loader::LoadFlie_24bit(const std::string& filename, BMPData& bmp) {
	FILE* fp = nullptr;

	DISABLE_C4996
		fp = fopen(filename.c_str(), "rb");
	ENABLE_C4996
		if (fp == nullptr) {
			printf("%s: notfile\n", filename.c_str());
		}

	fread(&bmp.bmpheder.bmpfileheader, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&bmp.bmpheder.bmpinfoheader, sizeof(BITMAPINFOHEADER), 1, fp);
	bmp.data.resize(bmp.bmpheder.bmpinfoheader.biWidth* bmp.bmpheder.bmpinfoheader.biHeight * 4);																				 
	for (int line = bmp.bmpheder.bmpinfoheader.biHeight - 1; line >= 0; --line) {
		for (int count = 0; count < bmp.bmpheder.bmpinfoheader.biWidth * 4; count += 4) {
			unsigned int address = line*bmp.bmpheder.bmpinfoheader.biWidth * 4;
			bmp.data[address + count] = 0;
			fread(&bmp.data[address + count + 1], sizeof(unsigned char), 3, fp);
		}
	}
	fclose(fp);

}

