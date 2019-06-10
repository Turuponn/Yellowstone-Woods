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
#include "d3dx12.h"
#include <dxgi1_4.h>


float clearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
unsigned int heapeIncrementSize = 0;

D3D12_VIEWPORT _viewport = {};
D3D12_RECT _scissorRect = {};




RenderTargetManager::RenderTargetManager() {
	_resocebarrier = nullptr;
}
RenderTargetManager::~RenderTargetManager() {
	SAFE_DELETE(_resocebarrier);
}



void RenderTargetManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain) {
	std::shared_ptr<RenderTargetCreate> rtc(new RenderTargetCreate());
	_rtc = rtc;
	
	RenderTargetViewPort();
	RenderTargetScissorRect();
	_renderTargets = _rtc->CreateRenderTargetView(device->GetDevice(), swapchain->GetSwapChainDescHeap().Get(), swapchain->GetSwapChain().Get());
	heapeIncrementSize = device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	
}

void RenderTargetManager::Updata(std::shared_ptr<SwapChainManager>& swapchain, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DepthManager>& depth) {
	
	//現在のバックバッファの番号を入れる
	_bbIndex = swapchain->GetSwapChain()->GetCurrentBackBufferIndex();

	comand->GetGraphicsCommandList()->RSSetViewports(1, &_viewport);//ビューポートの指定
	comand->GetGraphicsCommandList()->RSSetScissorRects(1, &_scissorRect);//矩形の特徴

	PreRTV(comand);
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtv(swapchain->GetSwapChainDescHeap()->GetCPUDescriptorHandleForHeapStart(), _bbIndex, heapeIncrementSize);//レンダーターゲットビュー(RTV)用の深度バッファの設定
	comand->GetGraphicsCommandList()->ClearDepthStencilView(depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);//毎フレーム深度バッファを無限大に更新
	comand->GetGraphicsCommandList()->OMSetRenderTargets(1, &rtv, false, &depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());//描画対象の設定
 	
}

void RenderTargetManager::UpdataRTVs(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand, std::shared_ptr<DepthManager>& depth,  D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap,const int heapnum) {
	//G-bufferに書き込むための下準備をします
	comand->GetGraphicsCommandList()->RSSetViewports(1, &_viewport);
	comand->GetGraphicsCommandList()->RSSetScissorRects(1, &_scissorRect);
	comand->GetGraphicsCommandList()->OMSetRenderTargets(heapnum, &startdescheap, true, &depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());//Zソートの効果が欲しいため、Zバッファを有効にします。
	comand->GetGraphicsCommandList()->ClearDepthStencilView(depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	SIZE_T ptr = startdescheap.ptr;
	SIZE_T offsetted = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE heapstart = {};
	for (int i = 0; i < heapnum; i++) {
		offsetted = ptr + static_cast<SIZE_T>(i * device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		heapstart.ptr = offsetted;
	}
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
void RenderTargetManager::CreateRTVHeap(std::shared_ptr<D3D12DeviceManager>& device,ID3D12DescriptorHeap** heap) {
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descHeapDesc.NodeMask = 0;
	descHeapDesc.NumDescriptors = 1;
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	auto result = device->GetDevice()->CreateDescriptorHeap(
		&descHeapDesc,
		IID_PPV_ARGS(heap)
	);
	if (result != S_OK) {
		throw(1);
	}
}
void RenderTargetManager::CreateRTVView(std::shared_ptr<D3D12DeviceManager>& device, ID3D12Resource* buffer, ID3D12DescriptorHeap* rtvheap) {
	device->GetDevice()->CreateRenderTargetView(buffer, nullptr, rtvheap->GetCPUDescriptorHandleForHeapStart());
}
void RenderTargetManager::PreRTV(std::shared_ptr<ComandManager>& comand) {
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_PRESENT,D3D12_RESOURCE_STATE_RENDER_TARGET, _renderTargets[_bbIndex]);
}
void RenderTargetManager::PostRTV(std::shared_ptr<ComandManager>& comand) {
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, _renderTargets[_bbIndex]);
}

UINT& RenderTargetManager::Getbbidx() {
	return _bbIndex;
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& RenderTargetManager::GetRTVDescHeap() {
	return _rtvdescheap;
}