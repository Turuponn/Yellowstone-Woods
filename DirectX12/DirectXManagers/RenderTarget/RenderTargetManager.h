#pragma once

#include <vector>
#include <memory>
#include <wrl.h>


struct ID3D12Resource;
struct ID3D12RootSignature;
struct ID3D12DescriptorHeap;
struct D3D12_CPU_DESCRIPTOR_HANDLE;

class D3D12DeviceManager;
class SwapChainManager;
class ComandManager;
class FenceManager;
class DepthManager;
class RenderTargetCreate;
class D2DManager;
class D3D11On12DeviceManager;


enum DXGI_FORMAT;
enum D3D12_RESOURCE_FLAGS;



struct CD3DX12_CPU_DESCRIPTOR_HANDLE;


class RenderTargetManager {
private:
	void RenderTargetViewPort();
	void RenderTargetScissorRect();
protected:
	RenderTargetManager();
	virtual ~RenderTargetManager();
	
	void Initialize(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<SwapChainManager>& swapchain
	);
	/// /// <summary>
	/// RTVの更新 : DescNum数用に対応
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="depth"></param>
	/// <param name="rootsignature"></param>
	/// <param name="startdescheap"></param>
	/// <param name="heapnum"> descnum</param>
	void UpdataRTVs(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<DepthManager>& depth,
		std::shared_ptr<SwapChainManager>& swapchain,
		D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap,
		const int heapnum
	);
	/// <summary>
	/// スワップチェイン用に作成したRTVを更新します
	/// </summary>
	/// <param name="swapchain"></param>
	/// <param name="comand"></param>
	/// <param name="depth"></param>
	void UpdataRTV(
		std::shared_ptr<SwapChainManager>& swapchain,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<DepthManager>& depth
	);
	void PreRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain);
	void PostRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain);

	void RenderUI(std::shared_ptr<SwapChainManager>& swapchain, std::shared_ptr<ComandManager>& comand);
private:
	std::vector<ID3D12Resource*> _renderTargets;//not D2D RTV
	std::shared_ptr<RenderTargetCreate> _rtc;
	std::shared_ptr<D2DManager> _d2d;
	std::shared_ptr<D3D11On12DeviceManager> _dx11on12device;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvdescheap;



};