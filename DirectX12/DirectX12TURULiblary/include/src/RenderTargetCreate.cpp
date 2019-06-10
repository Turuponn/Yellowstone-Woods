#include "RenderTargetCreate.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "../d3dx12.h"
#include "GameError.h"

RenderTargetCreate::RenderTargetCreate() {

}
RenderTargetCreate::~RenderTargetCreate() {

}

std::vector<ID3D12Resource*> RenderTargetCreate::CreateRenderTargetView(ID3D12Device* device, ID3D12DescriptorHeap* descriptorHeap, IDXGISwapChain3* swapchain) {
	//ディスクリプタハンドルの作成
	CD3DX12_CPU_DESCRIPTOR_HANDLE descriptorHandle_cpu(descriptorHeap->GetCPUDescriptorHandleForHeapStart());
	std::vector<ID3D12Resource*> rendertarget;																	 
	DXGI_SWAP_CHAIN_DESC swcDesc = {};
	swapchain->GetDesc(&swcDesc);//スワップチェインの情報
	int renderTargetsNum = swcDesc.BufferCount;//レンダーターゲットの値をもらう
	rendertarget.resize(renderTargetsNum);
	for (int i = 0; i < renderTargetsNum; ++i) {
		HRESULT result = E_FAIL;
		result = swapchain->GetBuffer(i, IID_PPV_ARGS(&rendertarget[i]));//スワップチェインから「キャンバス」を取得
		if (result != S_OK) {
			throw(1);
		}
		device->CreateRenderTargetView(rendertarget[i], nullptr, descriptorHandle_cpu);//キャンバスと職人を紐づける　
		descriptorHandle_cpu.Offset(device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	}
	return rendertarget;
}

//RTV用ヒープを作成する
void RenderTargetCreate::RTVCreateHeap(ID3D12Device* device, ID3D12DescriptorHeap** _rtvdescheap) {
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descHeapDesc.NodeMask = 0;
	descHeapDesc.NumDescriptors = 1;
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	auto result = device->CreateDescriptorHeap(
		&descHeapDesc,
		IID_PPV_ARGS(_rtvdescheap)
	);
	if (result != S_OK) {
		throw(1);
	}
}
void RenderTargetCreate::RTVCreateHeaps(ID3D12Device* device,const int numdesc, ID3D12DescriptorHeap** _rtvdescheap) {
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descHeapDesc.NodeMask = 0;
	descHeapDesc.NumDescriptors = numdesc;
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	auto result = device->CreateDescriptorHeap(
		&descHeapDesc,
		IID_PPV_ARGS(_rtvdescheap)
	);
	if (result != S_OK) {
		throw(1);
	}
}
void RenderTargetCreate::CreateRTVView(ID3D12Device* device,ID3D12DescriptorHeap* rtvdescheap, ID3D12Resource *pResource, DXGI_FORMAT format) {
	CD3DX12_CPU_DESCRIPTOR_HANDLE heapcpu = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvdescheap->GetCPUDescriptorHandleForHeapStart(), 0, 1);
	D3D12_RENDER_TARGET_VIEW_DESC rtvdesc = {};
	rtvdesc.Format = format;
	rtvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(pResource, &rtvdesc, heapcpu);
}
void RenderTargetCreate::CreateRTVViews(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE& rtvdescheap, ID3D12Resource *pResource, DXGI_FORMAT format) {
	D3D12_RENDER_TARGET_VIEW_DESC rtvdesc = {};
	rtvdesc.Format = format;
	rtvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(pResource, &rtvdesc, rtvdescheap);
}
void RenderTargetCreate::CreateRTBuffer(ID3D12Device* device,const int sizex,const int sizey, D3D12_RESOURCE_STATES resocestate, DXGI_FORMAT format, ID3D12Resource** pResource) {
		HRESULT result = E_FAIL;
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_CUSTOM;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
		heapprop.CreationNodeMask = 1;
		heapprop.VisibleNodeMask = 1;


		D3D12_RESOURCE_DESC resDesc = {};
		resDesc.Format = format;
		resDesc.Width = sizex;
		resDesc.Height = sizey;
		resDesc.DepthOrArraySize = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.SampleDesc.Quality = 0;
		resDesc.MipLevels = 1;
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		D3D12_CLEAR_VALUE value = {};//クリアカラーのデフォルト値
		value.Color[0] = 0;
		value.Color[1] = 0;
		value.Color[2] = 0;
		value.Color[3] = 1;
		value.Format = format;
		result = device->CreateCommittedResource(
			&heapprop,
			D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
			&resDesc,
			resocestate,//最初の状態
			&value,
			IID_PPV_ARGS(pResource)
		);
		if (result != S_OK) {
			throw(1);
		}
}