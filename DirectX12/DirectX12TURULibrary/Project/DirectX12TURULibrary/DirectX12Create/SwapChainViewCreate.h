#pragma once


struct ID3D12Device;
struct ID3D12DescriptorHeap;

class SwapChainViewCreate {
public:
	SwapChainViewCreate();
	virtual ~SwapChainViewCreate();
	/// <summary>
	///スワップチェインビューを作成する 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="swapchainscreencount">スワップチェインに登録済みの画面の数</param>
	/// <param name="descriptorHeap">[out]</param>
	void CreateSwapChainViewDesc(ID3D12Device* device, const unsigned int swapchainscreencount, ID3D12DescriptorHeap** descriptorHeap);
};