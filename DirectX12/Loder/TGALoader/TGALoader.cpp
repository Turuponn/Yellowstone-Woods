#include "TGALoader.h"
#include <stdio.h>




TGALoader::TGALoader() {

}
TGALoader::~TGALoader() {

}

void TGALoader::LoadImageTGA(const std::string& filepath, TGAImageData** tgaimagedata) {
	FILE* fp = NULL;
	printf("\n");
	fp = fopen(filepath.c_str(),"rb");
	if (fp == nullptr) {
		printf("%s: notfile\n", filepath.c_str());
	}

	TGAHeader header;
	TGAImageData tgadata;


	fread(&header,sizeof(TGAHeader),1,fp);
	tgadata.header = header;

	TGAFormat format;
	//�@24 bit
	if (header.bitperpixel == 24)
	{
		format = TGAFormat::TGA_RGB;
	}
	//�@32 bit
	else if (header.bitperpixel = 32)
	{
		format = TGAFormat::TGA_RGBA;
	}
	tgadata.format = format;
	//1pix������̃T�C�Y
	int bytePerPixel = header.bitperpixel / 8;
	//�@�f�[�^�T�C�Y�̌��� (�s�N�Z���f�[�^�̃T�C�Y)��(�摜�̕�)�~(�摜�̍���)�~(1�s�N�Z��������̃o�C�g��)
	int imageSize = header.imagewidth[0] * header.imageheight[0] * bytePerPixel;
	tgadata.pixdataList.resize(imageSize);
	fread(&tgadata.pixdataList[0], sizeof(char), imageSize, fp);
	//�@BGR(A)��RGB(A)�ɃR���o�[�g
	for (int i = 0; i<(int)imageSize; i += bytePerPixel)
	{
		auto temp = tgadata.pixdataList[i];
		tgadata.pixdataList[i + 0] = tgadata.pixdataList[i + 2];
		tgadata.pixdataList[i + 2] = temp;
	}
	*tgaimagedata = new TGAImageData();
	**tgaimagedata = tgadata;

	fclose(fp);
}