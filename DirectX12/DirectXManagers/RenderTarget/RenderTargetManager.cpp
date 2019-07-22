#include "RenderTargetManager.h"
#include "Library\GameError.h"
#include "constance.h"
#include "Library\DirectX12Create\RenderTargetCreate.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\swapchain\SwapChainManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "Library\DirectX12Create\ResourceBarrier.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\DepthStencil\Depth\DepthManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "d3dx12.h"
#include <dxgi1_4.h>

namespace {
	unsigned int heapeIncrementSize = 0;
	D3D12_VIEWPORT _viewport = {};
	D3D12_RECT _scissorRect = {};
	float clearColor[4] = { 0.0f,0.0f,0.0f,1.0f };

}



RenderTargetManager::RenderTargetManager() {
	
}
RenderTargetManager::~RenderTargetManager() {
	for (auto& ptr : _renderTargets) {
		SAFE_RELEASE(ptr);
	}
}



void RenderTargetManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain) {
	std::shared_ptr<RenderTargetCreate> rtc(new RenderTargetCreate());
	_rtc = rtc;
	
	RenderTargetViewPort();
	RenderTargetScissorRect();
	_renderTargets = _rtc->CreateRenderTargetView(device->GetDevice().Get(), swapchain->GetSwapChainDescHeap().Get(), swapchain->GetSwapChain().Get());
	
	////Dx11on12device
	//std::shared_ptr<D3D11On12DeviceManager> dx11on12device(new D3D11On12DeviceManager());
	//_dx11on12device = dx11on12device;
	//_dx11on12device->Create11On12Device(device, comand);
	////d2d
	//std::shared_ptr<D2DManager> d2d(new D2DManager());
	//_d2d = d2d;
	//_d2d->Initialize(device, _dx11on12device, swapchain);
	
	
	heapeIncrementSize = device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	
}
void RenderTargetManager::UpdataRTV(std::shared_ptr<SwapChainManager>& swapchain, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DepthManager>& depth) {
	

	comand->GetGraphicsCommandList()->RSSetViewports(1, &_viewport);//ビューポートの指定
	comand->GetGraphicsCommandList()->RSSetScissorRects(1, &_scissorRect);//矩形の特徴

	PreRTV(comand,swapchain);
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtv(swapchain->GetSwapChainDescHeap()->GetCPUDescriptorHandleForHeapStart(), swapchain->GetFrameBufferIndex(), heapeIncrementSize);//レンダーターゲットビュー(RTV)用の深度バッファの設定
	comand->GetGraphicsCommandList()->ClearDepthStencilView(depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);//毎フレーム深度バッファを無限大に更新
	comand->GetGraphicsCommandList()->OMSetRenderTargets(1, &rtv, false, &depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());//描画対象の設定
	comand->GetGraphicsCommandList()->ClearRenderTargetView(rtv, clearColor, 0, nullptr);
}
void RenderTargetManager::UpdataRTVs(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DepthManager>& depth, std::shared_ptr<SwapChainManager>& swapchain, D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap, const int heapnum) {
	comand->GetGraphicsCommandList()->RSSetViewports(1, &_viewport);
	comand->GetGraphicsCommandList()->RSSetScissorRects(1, &_scissorRect);
	comand->GetGraphicsCommandList()->OMSetRenderTargets(
		heapnum,
		&startdescheap,
		true,//Zソートの効果が欲しいため、Zバッファを有効にします。
		&depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart()
	);
	comand->GetGraphicsCommandList()->ClearDepthStencilView(
		depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		D3D12_CLEAR_FLAG_DEPTH,
		1.0f,
		0,
		0,
		nullptr
	);
	

}
void RenderTargetManager::ResetRTV(std::shared_ptr<ComandManager>& comand,D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap) {
	comand->GetGraphicsCommandList()->ClearRenderTargetView(startdescheap, clearColor, 0, nullptr);
}
void RenderTargetManager::RenderUI(std::shared_ptr<SwapChainManager>& swapchain, std::shared_ptr<ComandManager>& comand) {
	//_d2d->RenderUI(_dx11on12device, swapchain, comand);
}
void RenderTargetManager::RenderTargetViewPort() {
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	_viewport.Height = SCREEN_SIZE_Y;
	_viewport.Width = SCREEN_SIZE_X;
	_viewport.MaxDepth = 1.0f;
	_viewport.MinDepth = 0.0f;
}

void RenderTargetManager::RenderTargetScissorRect() {
	_scissorRect.top = 0;
	_scissorRect.left = 0;
	_scissorRect.right = SCREEN_SIZE_X;
	_scissorRect.bottom = SCREEN_SIZE_Y;
}
void RenderTargetManager::PreRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain) {
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, _renderTargets[swapchain->GetFrameBufferIndex()]);
	//D2DはRTVではなく、書き込み用としてリソースを遷移TODO:
	//comand->ComandRBarrier(D3D12_RESOURCE_STATE_PRESENT,D3D12_RESOURCE_STATE_RENDER_TARGET, _d2d->GetRTVResoce()[swapchain->GetFrameBufferIndex()].Get());
}
void RenderTargetManager::PostRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain) {
	//comand->ComandRBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, _d2d->GetRTVResoce()[swapchain->GetFrameBufferIndex()].Get());
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, _renderTargets[swapchain->GetFrameBufferIndex()]);
}

