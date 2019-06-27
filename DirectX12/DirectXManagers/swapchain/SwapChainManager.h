#pragma once


#include <Windows.h>
#include <memory>
#include <wrl.h>

class SwapChainCreate;
class D3D12DeviceManager;
class ComandManager;
struct IDXGISwapChain3;
struct ID3D12DescriptorHeap;
class SwapChainViewCreate;
class DxGIManager;


class SwapChainManager {
private:
	void CreateSwapChain(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DxGIManager>& dxgi, HWND& hwnd);
	void CreateSwapChainView(std::shared_ptr<D3D12DeviceManager>& device);
public:
	SwapChainManager();
	virtual ~SwapChainManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DxGIManager>& dxgi, HWND& hwnd);
	Microsoft::WRL::ComPtr<IDXGISwapChain3>& GetSwapChain();
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& GetSwapChainDescHeap();
	/// <summary>
	/// �X���b�v�`�F�C���p�t���[���o�b�t�@�̑�����Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	int GetFrameBufferCount();
	/// <summary>
	/// ���݂̃t���[���Ŏg���Ă���t���[���o�b�t�@�̃C���f�b�N�X��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	int GetFrameBufferIndex();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain3> _swapchain;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _descheap;
};
