#include "DepthCreate.h"
#include <d3d12.h>
#include "GameError.h"


DepthCreate::DepthCreate() {

}
DepthCreate::~DepthCreate() {

}

void DepthCreate::CreateDepthBuffer(ID3D12Device* device,const unsigned int screensize_x, const unsigned int screensize_y,ID3D12Resource** depthbuffer) {
	HRESULT result = E_FAIL;

	//深度バッファの作成												
	D3D12_CLEAR_VALUE _depthClearValue = {};
	_depthClearValue.DepthStencil.Depth = 1.0f;//深さ最大値は１
	_depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	//テクスチャとして使う
	D3D12_HEAP_PROPERTIES depthHeapProp = {};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;//デフォルト
	depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	//深度バッファリソース
	D3D12_RESOURCE_DESC depthResourceDesc = {};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;//テクスチャらしい
	depthResourceDesc.Width = screensize_x;//画面幅
	depthResourceDesc.Height = screensize_y;//画面高さ
	depthResourceDesc.DepthOrArraySize = 1;//配列のサイズ
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthResourceDesc.SampleDesc.Count = 1;//アンチエイリアシング用
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;



	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE, //デプス書き込みに使います
		&_depthClearValue,
		IID_PPV_ARGS(depthbuffer)
	);
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("DepthCreate::CreateBuffer() result != S_OK")));
	}
}
void DepthCreate::CreateDepthBufferView(ID3D12Device* device, ID3D12Resource* depthbuffer, ID3D12DescriptorHeap* depthheapedesc) {
	D3D12_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};
	//深度バッファのビュー設定
	//ビューを利用するときの送り方のイメージ
	depthViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Flags = D3D12_DSV_FLAG_NONE;
	device->CreateDepthStencilView(depthbuffer, &depthViewDesc, depthheapedesc->GetCPUDescriptorHandleForHeapStart());
}
void DepthCreate::CreateDepthDescHeap(ID3D12Device* device, ID3D12DescriptorHeap** depthheapedesc) {
	//ディスクリプター
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC _dsvHeapDesc = {};
	_dsvHeapDesc.NumDescriptors = 1;
	_dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//DSVで深度として区別させる

	result = device->CreateDescriptorHeap(&_dsvHeapDesc, IID_PPV_ARGS(depthheapedesc));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("DepthCreate::CreateDepthDescHeap() result != S_OK")));
	}
}