#include "Graphics.h"
#include <d3d12.h>
#include "constance.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\swapchain\SwapChainManager.h"
#include "DirectXManagers\DepthStencil\Depth\DepthManager.h"
#include "DirectXManagers\RenderTarget\RenderTargetManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\DxGI\DxGIManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "WindowInit.h"
#include <dxgi1_4.h>

Graphics::Graphics() {
	
}
Graphics::~Graphics() {
	
}
void Graphics::Initialize(std::shared_ptr<ComandManager>& comand, std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<DxGIManager>& dxgi, std::shared_ptr<SwapChainManager>& swapchain) {
	std::shared_ptr<DepthManager> depth(new DepthManager());
	_depth = depth;
	std::shared_ptr<RootSignatureManager> rs(new RootSignatureManager());
	_rootsignature = rs;
	RenderTargetManager::Initialize(device,comand, swapchain);
	_depth->Initialize(device);
	_rootsignature->Initialize(device);
}
void Graphics::RTVUpdata(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain, D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap, const int heapnum) {
	RenderTargetManager::UpdataRTVs(device,comand, _depth, swapchain, startdescheap,heapnum);
}
void Graphics::RTVSwapChainUpdate(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand,std::shared_ptr<SwapChainManager>& swapchain) {
	RenderTargetManager::UpdataRTV(swapchain,comand,_depth);
}
void Graphics::ScreenFlip(std::shared_ptr<ComandManager>& comand,std::shared_ptr<FenceManager>& fence,std::shared_ptr<SwapChainManager>& swapchain) {
	comand->ComandClose();
	comand->ComandExecuteCommandList();
	comand->ComandListWaitPorlling(fence);
	comand->ComandReset(swapchain);
	comand->ReSetPipeline(swapchain);
	if (swapchain->GetSwapChain()->Present(0, 0) != S_OK) { throw(1); }
}
void Graphics::D2DFlip(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<SwapChainManager>& swapchain) {
	RenderTargetManager::RenderUI(swapchain,comand);
	
	comand->ComandClose();
	comand->ComandExecuteCommandList();
	comand->ComandListWaitPorlling(fence);
}
void Graphics::PreRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain) {
	RenderTargetManager::PreRTV(comand, swapchain);
}
void Graphics::PostRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain) {
	RenderTargetManager::PostRTV(comand, swapchain);
}
std::shared_ptr<RootSignatureManager>& Graphics::GetRootSignature() {
	return _rootsignature;
}
std::shared_ptr<DepthManager>& Graphics::GetDepth() {
	return _depth;
}
