#include "DxGIManager.h"
#include "constance.h"
#include <dxgi1_4.h>

DxGIManager::DxGIManager() {
}
DxGIManager::~DxGIManager() {

}

void DxGIManager::CreateDxGiFactory() {
	HRESULT result = E_FAIL;
	result = CreateDXGIFactory1(IID_PPV_ARGS(&_dxgifac4));
	if (result != S_OK) {
		throw(1);
	}

}
Microsoft::WRL::ComPtr<IDXGIFactory4>& DxGIManager::GetDxGIFac() {
	return _dxgifac4;
}