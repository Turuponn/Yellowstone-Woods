#include "WICTexTextureCreate.h"
#include "GameError.h"
#include "Microsoftheder\WICTextureLoader\WICTextureLoader12.h"
#include <d3d12.h>
#include "d3dx12.h"
#include <wrl.h>//ComPtr

WICTexTextureCreate::WICTexTextureCreate() {
	
}
WICTexTextureCreate::~WICTexTextureCreate() {

}

void  WICTexTextureCreate::CreateTexture(ID3D12Device* device, const std::string& filename, IMAGESUBRESOCEINFO& imagesubresoceinfo, std::unique_ptr<uint8_t[]>& decodeddata, ID3D12Resource** texresoce) {
	HRESULT result = E_FAIL;
	D3D12_SUBRESOURCE_DATA subresoce;
	subresoce.pData = imagesubresoceinfo.imagedata;
	subresoce.RowPitch = imagesubresoceinfo.rowpitch;
	subresoce.SlicePitch = imagesubresoceinfo.slicepitch;
	std::wstring path(filename.begin(), filename.end());
	result = DirectX::LoadWICTextureFromFile(device, path.c_str(), texresoce, decodeddata, subresoce);
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR,_T("PNGTextureManager::CreateTexture() result != S_OK")));
	}
}
