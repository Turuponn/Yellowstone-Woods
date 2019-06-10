#include "DepthManager.h"
#include "Library\GameError.h"
#include "constance.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "Library\DirectX12Create\DepthCreate.h"
#include <d3d12.h>

DepthManager::DepthManager() {
	

}
DepthManager::~DepthManager() {
	
}
void DepthManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<DepthCreate> d(new DepthCreate());
	d->CreateDepthBuffer(device->GetDevice(), SCREEN_SIZE_X, SCREEN_SIZE_Y, &_depthbuffer);
	d->CreateDepthDescHeap(device->GetDevice(), &_depthHeapDesc);
	d->CreateDepthBufferView(device->GetDevice(), _depthbuffer.Get(), _depthHeapDesc.Get());
}
void DepthManager::CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device,const int screensize_x, const int screensize_y) {
	std::shared_ptr<DepthCreate> d(new DepthCreate());
	d->CreateDepthBuffer(device->GetDevice(), SCREEN_SIZE_X, SCREEN_SIZE_Y, &_depthbuffer);
}
void DepthManager::CreateHeap(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<DepthCreate> d(new DepthCreate());
	d->CreateDepthDescHeap(device->GetDevice(), &_depthHeapDesc);
}
void DepthManager::CreateView(std::shared_ptr<D3D12DeviceManager>& device, Microsoft::WRL::ComPtr<ID3D12Resource>& pResoce) {
	std::shared_ptr<DepthCreate> d(new DepthCreate());
	d->CreateDepthBufferView(device->GetDevice(), pResoce.Get(), _depthHeapDesc.Get());
}
Microsoft::WRL::ComPtr<ID3D12Resource>& DepthManager::GetDepthBuffer() {
	return _depthbuffer;
}
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& DepthManager::GetDescriptorHeap() {
	return _depthHeapDesc;
}
