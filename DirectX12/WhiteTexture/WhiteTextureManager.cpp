#include "WhiteTextureManager.h"
#include "constance.h"
#include <d3d12.h>
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "Library/DirectX12Create/TextureCreate.h"



WhiteTextureManager::WhiteTextureManager() {
	_writetexbuff = nullptr;
	_writetexheap = nullptr;
}
WhiteTextureManager::~WhiteTextureManager() {
	SAFE_RELEASE(_writetexbuff);
	SAFE_RELEASE(_writetexheap);
}


void WhiteTextureManager::CreateWhiteTexture(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand) {
	std::shared_ptr<TextureManager> texm(new TextureManager());
	_texm = texm;
	_texm->SRVCreateHeap(device);
	std::vector<char> data(4 * 4 * 4);//白テクスチャデータ
	std::fill(data.begin(), data.end(), 0xff);
	_texm->SRVBuffer(device, &data[0],4,4);
	_texm->SRVCreateView(device, DXGI_FORMAT_R8G8B8A8_UNORM);

}

void WhiteTextureManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand) {
	CreateWhiteTexture(device,comand);
}
void WhiteTextureManager::TexregisterDraw(std::shared_ptr<ComandManager>& comand, TEXTURE_REGISTER texture_register) {
	_texm->DrawImage(comand,1, texture_register);
}