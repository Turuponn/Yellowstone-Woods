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
	/// レンダーターゲットの更新を行います。
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="swapchain"></param>
	/// <param name="startdescheap">ヒープの場所</param>
	/// <param name="heapnum">ヒープオフセット用</param>
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
	/// RTVをクリアカラーでリセットします
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="startdescheap"></param>
	void RTVClear(std::shared_ptr<ComandManager>& comand, D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap);
	/// <summary>
	/// リソースの状態遷移を行います : 最初
	/// </summary>
	void PreRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// リソースの状態遷移を行います : 最後
	/// </summary>
	void PostRTV(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// フロントバッファとバックバッファを交換します
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="fence"></param>
	/// <param name="swapchain"></param>
	void ScreenFlip(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// ルートシグネチャを返します。
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<RootSignatureManager>& GetRootSignature();
	
	std::shared_ptr<DepthManager>& GetDepth();


	void D2DFlip(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<SwapChainManager>& swapchain);

private:
	std::shared_ptr<DepthManager> _depth;
	std::shared_ptr<RootSignatureManager> _rootsignature;
	
};
