#pragma once

#include <Windows.h>


struct IDXGIFactory4;
struct ID3D12Device;
struct ID3D12CommandQueue;
struct IDXGISwapChain3;


class SwapChainCreate {
public:
	SwapChainCreate();
	virtual ~SwapChainCreate();
	/// <summary>
	/// スワップチェインを作成する
	/// </summary>
	/// <param name="screensize_x">画面サイズ</param>
	/// <param name="screensize_y"></param>
	/// <param name="dxgifac4"></param>
	/// <param name="windowhwnd">ウインドウハンドル</param>
	/// <param name="device"></param>
	/// <param name="comand_queue"></param>
	/// <param name="swap_chain">[out]  スワップチェインを返す</param>
	void CreateSwapChain(
		const unsigned int screensize_x,
		const unsigned int screensize_y,
		IDXGIFactory4* dxgifac4,
		HWND& windowhwnd,
		ID3D12Device* device,
		ID3D12CommandQueue* comand_queue,
		IDXGISwapChain3** swap_chain
	);

};