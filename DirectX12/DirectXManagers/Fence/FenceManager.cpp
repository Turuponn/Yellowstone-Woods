#include "FenceManager.h"
#include "Library\GameError.h"
#include "constance.h"
#include "Library\DirectX12Create\FenceCreate.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include <d3d12.h>

UINT64 fenceValue;

FenceManager::FenceManager() {
	fenceValue = 0;
}
FenceManager::~FenceManager() {
}
void FenceManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<FenceCreate> f(new FenceCreate());
	_fencecreate = f;
	_fencecreate->CreateFance(device->GetDevice().Get(), fenceValue, &_fence);

}

Microsoft::WRL::ComPtr<ID3D12Fence>& FenceManager::GetFence() {
	return _fence;
}