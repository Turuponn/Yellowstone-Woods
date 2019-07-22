#pragma once


#include <string>
#include <memory>

struct ID3D12Resource;
struct ID3D12Device;


struct IMAGESUBRESOCEINFO {
	const void* imagedata;//データ部　imageWidth * imageHeight
	long long rowpitch;//sizeof(uint32)*width;
	long long slicepitch;//sizeof(uint32)*width*height;
};

class WICTexTextureCreate {
public:
	WICTexTextureCreate();
	virtual ~WICTexTextureCreate();
	/// <summary>
	/// テクスチャ作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="filename"></param>
	/// <param name="imagesubresoceinfo"></param>
	/// <param name="decodeddata"></param>
	/// <param name="texresoce">[out]</param>
	void CreateTexture(ID3D12Device* device, const std::string& filename, IMAGESUBRESOCEINFO& imagesubresoceinfo, std::unique_ptr<uint8_t[]>& decodeddata, ID3D12Resource** texresoce);
	

private:
};
