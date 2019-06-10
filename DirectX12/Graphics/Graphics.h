#pragma once


#include <Windows.h>
#include <memory>

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

class Graphics {
public:
	Graphics();
	virtual ~Graphics();
	void Initialize(std::shared_ptr<ComandManager>& comand, std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<DxGIManager>& dxgi, HWND& hwnd);
	void Updata(std::shared_ptr<ComandManager>& comand);
	std::shared_ptr<RootSignatureManager>& GetRootSignature();
	void ScreenFlip(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);
	std::shared_ptr<SwapChainManager>& GetSwapChain();
	/// <summary>
	/// 深度を返す
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<DepthManager>& GetDepth();
	/// <summary>
	/// 現在使用しているリサイクル可能なRTVmanagerを返す
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<RenderTargetManager>& GetRTV();
private:
	std::shared_ptr<DepthManager> _depth;
	std::shared_ptr<SwapChainManager> _swapchain;
	std::shared_ptr<RenderTargetManager> _rendertargetmanager;
	std::shared_ptr<RootSignatureManager> _rootsignature;
	
};
