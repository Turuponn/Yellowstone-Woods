#include "FenceCreate.h"
#include <d3d12.h>
#include "../GameError.h"
FenceCreate::FenceCreate() {

}
FenceCreate::~FenceCreate() {

}


void FenceCreate::CreateFance(ID3D12Device* device, UINT64 initializefenceValue, ID3D12Fence** fence) {

	HRESULT result = E_FAIL;

	//基本的には同じValueを使用します、マルチスレッドのミューテックスのような
	//排他制御に使用する　と思われます。
	result = device->CreateFence(initializefenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("FenceCreate::CreateFance() result != S_OK")));
	}
}