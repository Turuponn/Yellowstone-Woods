#include "SwapChainCreate.h"
#include <d3d12.h>
#include <dxgi1_4.h>//dxgi用
#include "GameError.h"



SwapChainCreate::SwapChainCreate() {

}

SwapChainCreate::~SwapChainCreate() {

}

void SwapChainCreate::CreateSwapChain(const unsigned int screensize_x,const unsigned int screensize_y, IDXGIFactory4* dxgifac4, HWND& windowhwnd, ID3D12Device* device, ID3D12CommandQueue* comand_queue, IDXGISwapChain3** swap_chain) {
	//スワップチェイン作成
	HRESULT result = E_FAIL;

	result = E_FAIL;
	DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
	swap_chain_desc.Width = screensize_x;
	swap_chain_desc.Height = screensize_y;
	swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.Stereo = false;
	swap_chain_desc.SampleDesc.Count = 1;//アンチエイリアシング用　1で使わない
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//Usage使用方法
	swap_chain_desc.BufferCount = 2;//スクリーンバッファ数
	swap_chain_desc.Scaling = DXGI_SCALING_STRETCH;//画面の縮尺をいじられたらどう対応するか
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_chain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;//指定しない
	swap_chain_desc.Flags = 0;//回転でどうかわるかの設定
	result = dxgifac4->CreateSwapChainForHwnd(
		comand_queue,//コマンドキューを入れる
		windowhwnd,
		&swap_chain_desc,
		nullptr,//フルスクリーン
		nullptr,
		(IDXGISwapChain1**)(swap_chain)
	);

	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("SwapChainCreate::CreateSwapChain result != S_OK")));
	}
}
