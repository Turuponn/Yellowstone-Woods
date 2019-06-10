#pragma once


#include <string>
#include <vector>

enum TGAFormat {
	TGA_RGB,
	TGA_RGBA
};

struct TGAHeader {
	char idfieldlength;//	IDフィールド長
	char Colormaptype;//カラーマップタイプ(カラーマップの有無)
	char imagetype;//画像タイプ
	char colormapindex[2];// 	カラーマップ原点 Low,Hightの順番
	char colormaplength[2];//	カラーマップ長 Low,Hightの順番
	char colormapsize;//カラーマップ深度
	char colororiginX[2];//画像X方向原点 Low,Hightの順番
	char colororiginY[2];//画像Y方向原点 Low,Hightの順番
	char imagewidth[2];//画像幅 Low,Hightの順番
	char imageheight[2];// 画像高さ Low,Hightの順番
	char bitperpixel;//画像深度(画像ピクセルサイズ) 1pix 24bit　か　32bitか
	char discripter;//	画像デスクリプタ
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