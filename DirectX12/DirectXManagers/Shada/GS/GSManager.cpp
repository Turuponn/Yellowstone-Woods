#include "GSManager.h"
#include "Library/DirectX12Create/ShadaCreate.h"
#include <d3d12.h>
#include "constance.h"

GSManager::GSManager() {

}
GSManager::~GSManager() {

}



void GSManager::CreateShada(wchar_t* filename, char* funcname) {
	std::shared_ptr<ShadaCreate> sc(new ShadaCreate());
	sc->CreateGeometryShada(filename, funcname, &_gs);
}

Microsoft::WRL::ComPtr<ID3DBlob>& GSManager::GetBlob() {
	return _gs;
}