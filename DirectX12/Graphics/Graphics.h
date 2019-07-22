#pragma once

#include <memory>
#include "DirectXManagers\RenderTarget\RenderTargetManager.h"


class D3D12DeviceManager;
class ComandManager;
class SwapChainManager;
class RenderTargetManager;
class DepthManager;
class FenceManager;
struct ID3D12RootSignature;
class RootSignatureManager;
class WindowInit;
class DxGIManager;

class Graphics : public RenderTargetManager {
public:
	Graphics();
	~Graphics();
	void Initialize(
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<DxGIManager>& dxgi,
		std::shared_ptr<SwapChainManager>& swapchain
	);
	/// <summary>
	/// �����_�[�^�[�Q�b�g�̍X�V���s���܂��B
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="swapchain"></param>
	/// <param name="startdescheap">�q�[�v�̏ꏊ</param>
	/// <param name="heapnum">�q�[�v�I�t�Z�b�g�p</param>
	void RTVUpdata(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<SwapChainManager>& swapchain,
		D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap,
		const int heapnum
	);
	void RTVSwapChainUpdate(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<SwapChainManager>& swapchain
	);
	/// <summary>
	/// RTV���N���A�J���[�Ń��Z�b�g���܂�
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="startdescheap"></param>
	void RTVClear(std::shared_ptr<ComandManager>& comand, D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap);
	/// <summary>
	/// ���\�[�X�̏�ԑJ�ڂ��s���܂� : �ŏ�
	/// </summary>
	void PreRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// ���\�[�X�̏�ԑJ�ڂ��s���܂� : �Ō�
	/// </summary>
	void PostRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@���������܂�
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="fence"></param>
	/// <param name="swapchain"></param>
	void ScreenFlip(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// ���[�g�V�O�l�`����Ԃ��܂��B
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<RootSignatureManager>& GetRootSignature();
	
	std::shared_ptr<DepthManager>& GetDepth();


	void D2DFlip(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<SwapChainManager>& swapchain);

private:
	std::shared_ptr<DepthManager> _depth;
	std::shared_ptr<RootSignatureManager> _rootsignature;
	
};
