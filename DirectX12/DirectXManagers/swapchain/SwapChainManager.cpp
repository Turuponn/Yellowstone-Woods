#include "SwapChainManager.h"
#include "constance.h"
#include "Library\GameError.h"
#include "Library\DirectX12Create\SwapChainCreate.h"
#include "Library\DirectX12Create\SwapChainViewCreate.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\DxGI\DxGIManager.h"
#include <dxgi1_4.h>
#include <d3d12.h>


SwapChainManager::SwapChainManager() {

}
SwapChainManager::~SwapChainManager() {
	
}
void SwapChainManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DxGIManager>& dxgi, HWND& hwnd) {
	CreateSwapChain(device, comand, dxgi, hwnd);
	CreateSwapChainView(device);
}
void SwapChainManager::CreateSwapChain(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand,std::shared_ptr<DxGIManager>& dxgi, HWND& hwnd) {
	HRESULT result = E_FAIL;
	std::shared_ptr<SwapChainCreate> scC(new SwapChainCreate());
	scC->CreateSwapChain(SCREEN_SIZE_X, SCREEN_SIZE_Y, dxgi->GetDxGIFac().Get(), hwnd, device->GetDevice(), comand->GetComandQueue().Get(), &_swapchain);
}

void SwapChainManager::CreateSwapChainView(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<SwapChainViewCreate> scV(new SwapChainViewCreate());
	DXGI_SWAP_CHAIN_DESC swcDesc = {};
	_swapchain->GetDesc(&swcDesc);
	int renderTargetsNum = swcDesc.BufferCount;
	scV->CreateSwapChainViewDesc(device->GetDevice(), renderTargetsNum, &_descheap);
}
int SwapChainManager::GetFrameBufferCount() {
	DXGI_SWAP_CHAIN_DESC swcDesc = {};
	_swapchain->GetDesc(&swcDesc);
	return swcDesc.BufferCount;
}
int SwapChainManager::GetFrameBufferIndex() {
	return (UINT)_swapchain->GetCurrentBackBufferIndex();
}
Microsoft::WRL::ComPtr<IDXGISwapChain3>& SwapChainManager::GetSwapChain() {
	return _swapchain;
}
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& SwapChainManager::GetSwapChainDescHeap() {
	return _descheap;
}