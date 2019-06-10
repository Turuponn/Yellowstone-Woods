#pragma once


#include <string>
#include <vector>

enum TGAFormat {
	TGA_RGB,
	TGA_RGBA
};

struct TGAHeader {
	char idfieldlength;//	ID�t�B�[���h��
	char Colormaptype;//�J���[�}�b�v�^�C�v(�J���[�}�b�v�̗L��)
	char imagetype;//�摜�^�C�v
	char colormapindex[2];// 	�J���[�}�b�v���_ Low,Hight�̏���
	char colormaplength[2];//	�J���[�}�b�v�� Low,Hight�̏���
	char colormapsize;//�J���[�}�b�v�[�x
	char colororiginX[2];//�摜X�������_ Low,Hight�̏���
	char colororiginY[2];//�摜Y�������_ Low,Hight�̏���
	char imagewidth[2];//�摜�� Low,Hight�̏���
	char imageheight[2];// �摜���� Low,Hight�̏���
	char bitperpixel;//�摜�[�x(�摜�s�N�Z���T�C�Y) 1pix 24bit�@���@32bit��
	char discripter;//	�摜�f�X�N���v�^
};

struct TGAImageData {
	TGAHeader header;
	TGAFormat format;
	std::vector<char> pixdataList;
};

class TGALoader {
public:
	TGALoader();
	virtual ~TGALoader();

	void LoadImageTGA(const std::string& filepath, TGAImageData** tgaimagedata);

private:
	
};