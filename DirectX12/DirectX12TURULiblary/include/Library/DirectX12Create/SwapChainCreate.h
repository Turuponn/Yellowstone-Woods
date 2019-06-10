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
	/// �X���b�v�`�F�C�����쐬����
	/// </summary>
	/// <param name="screensize_x">��ʃT�C�Y</param>
	/// <param name="screensize_y"></param>
	/// <param name="dxgifac4"></param>
	/// <param name="windowhwnd">�E�C���h�E�n���h��</param>
	/// <param name="device"></param>
	/// <param name="comand_queue"></param>
	/// <param name="swap_chain">[out]  �X���b�v�`�F�C����Ԃ�</param>
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