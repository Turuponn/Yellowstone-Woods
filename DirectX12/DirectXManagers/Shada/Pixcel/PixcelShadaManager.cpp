#include "PixcelShadaManager.h"
#include <d3d12.h>
#include "Library\GameError.h"
#include "Library\DirectX12Create\ShadaCreate.h"
#include "constance.h"

PixcelShadaManager::PixcelShadaManager() {

}
PixcelShadaManager::~PixcelShadaManager() {
	
}

void PixcelShadaManager::CreatePixelShada(wchar_t* filename, char* funcname) {
	std::shared_ptr<ShadaCreate> sc(new ShadaCreate());
	_shadacreate = sc;
	_shadacreate->CreatePixelShada(filename, funcname, &_pixcelshada);
}
void PixcelShadaManager::CreatePixelShada(const std::string& filepath, const std::string& funcname) {
	
}


Microsoft::WRL::ComPtr<ID3DBlob>& PixcelShadaManager::GetPixelShada() {
	return _pixcelshada;
}
