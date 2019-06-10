#pragma once
#include <Windows.h>
#include <string>
#include <vector>


struct BMPHeder {
	BITMAPFILEHEADER bmpfileheader;
	BITMAPINFOHEADER bmpinfoheader;
};

struct BMPData{
	BMPHeder bmpheder;
	std::vector<char> data;
};

class BMP_Loader {
public:
	BMP_Loader();
	virtual ~BMP_Loader();

	void LoadFlie_24bit(const std::string& filename, BMPData& bmp);

private:

};