#pragma once


struct ID3D12Device;
struct ID3D12DescriptorHeap;

class SwapChainViewCreate {
public:
	SwapChainViewCreate();
	virtual ~SwapChainViewCreate();
	/// <summary>
	///�X���b�v�`�F�C���r���[���쐬���� 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="swapchainscreencount">�X���b�v�`�F�C���ɓo�^�ς݂̉�ʂ̐�</param>
	/// <param name="descriptorHeap">[out]</param>
	void CreateSwapChainViewDesc(ID3D12Device* device, const unsigned int swapchainscreencount, ID3D12DescriptorHeap** descriptorHeap);
};