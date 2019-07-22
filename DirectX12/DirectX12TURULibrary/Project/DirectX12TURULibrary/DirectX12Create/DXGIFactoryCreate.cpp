#include "DXGIFactoryCreate.h"
#include <dxgi1_4.h>
#include "../GameError.h"


DXGIFactoryCreate::DXGIFactoryCreate() {

}
DXGIFactoryCreate::~DXGIFactoryCreate() {

}

void DXGIFactoryCreate::CreateDXGIFactory(IDXGIFactory4** dxgifac4) {
	HRESULT result = E_FAIL;

	//DXGIFActory4の作成 スワップチェイン用のdeviceの生成
	result = CreateDXGIFactory1(IID_PPV_ARGS(dxgifac4));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("SwapChainCreate::CreateSwapChain() result != S_OK")));
	}
}