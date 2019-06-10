#include "SwapChainViewCreate.h"
#include <d3d12.h>
#include "GameError.h"

SwapChainViewCreate::SwapChainViewCreate() {

}
SwapChainViewCreate::~SwapChainViewCreate() {

}

void SwapChainViewCreate::CreateSwapChainViewDesc(ID3D12Device* device, const unsigned int swapchainscreencount, ID3D12DescriptorHeap** descriptorHeap) {
	//ディスクリプタを作成する
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC heap_descripta;
	heap_descripta.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビューとして使う
	heap_descripta.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//デフォルト使う
	heap_descripta.NodeMask = 0;//複数画面用
	heap_descripta.NumDescriptors = swapchainscreencount;//既に設定している画面のバッファ数
	result = device->CreateDescriptorHeap(&heap_descripta, IID_PPV_ARGS(descriptorHeap));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("SwapChainCreate::CreateSwapChain result != S_OK")));
	}
}