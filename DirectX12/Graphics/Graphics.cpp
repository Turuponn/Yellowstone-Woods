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
void Graphics::Initialize(std::shared_ptr<ComandManager>& comand, std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<DxGIManager>& dxgi, HWND& hwnd) {
	std::shared_ptr<DepthManager> depth(new DepthManager());
	_depth = depth;
	std::shared_ptr<SwapChainManager> sc(new SwapChainManager());
	_swapchain = sc;
	std::shared_ptr<RenderTargetManager> rt(new RenderTargetManager());
	_rendertargetmanager = rt;
	std::shared_ptr<RootSignatureManager> rs(new RootSignatureManager());
	_rootsignature = rs;

	_swapchain->Initialize(device, comand, dxgi, hwnd);
	_rendertargetmanager->Initialize(device, _swapchain);
	_depth->Initialize(device);
	_rootsignature->Initialize(device);
}
void Graphics::Updata(std::shared_ptr<ComandManager>& comand) {
	_rendertargetmanager->Updata(_swapchain,comand, _depth);
}
void Graphics::ScreenFlip(std::shared_ptr<ComandManager>& comand,std::shared_ptr<FenceManager>& fence) {
	comand->ComandClose();
	comand->ComandExecuteCommandList();
	comand->ComandListWaitPorlling(fence);
	comand->ComandReset();
	comand->ReSetPipeline();
	if (_swapchain->GetSwapChain()->Present(0, 0) != S_OK) { throw(1); }	
}

std::shared_ptr<RootSignatureManager>& Graphics::GetRootSignature() {
	return _rootsignature;
}

std::shared_ptr<SwapChainManager>& Graphics::GetSwapChain() {
	return _swapchain;
}

std::shared_ptr<DepthManager>& Graphics::GetDepth() {
	return _depth;
}
std::shared_ptr<RenderTargetManager>& Graphics::GetRTV() {
	return _rendertargetmanager;
}