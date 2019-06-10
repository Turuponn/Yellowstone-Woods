#pragma once

#include <vector>
#include <memory>
#include <wrl.h>


class RenderTargetCreate;
struct ID3D12Resource;
class D3D12DeviceManager;
class SwapChainManager;
class ResourceBarrier;
class ComandManager;
class FenceManager;
class DepthManager;
struct ID3D12RootSignature;
struct ID3D12DescriptorHeap;
struct D3D12_CPU_DESCRIPTOR_HANDLE;
typedef unsigned int        UINT;


enum DXGI_FORMAT;
enum D3D12_RESOURCE_FLAGS;



struct CD3DX12_CPU_DESCRIPTOR_HANDLE;


class RenderTargetManager {
private:
	void RenderTargetViewPort();
	void RenderTargetScissorRect();
public:
	RenderTargetManager();
	virtual ~RenderTargetManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain);
	void Updata(std::shared_ptr<SwapChainManager>& swapchain, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DepthManager>& depth);
	/// <summary>
	/// RTVÇÃçXêV : DescNumêîópÇ…ëŒâû
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="depth"></param>
	/// <param name="rootsignature"></param>
	/// <param name="startdescheap"></param>
	/// <param name="heapnum"> descnum</param>
	void UpdataRTVs(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<DepthManager>& depth, D3D12_CPU_DESCRIPTOR_HANDLE& startdescheap, const int heapnum);
	UINT& Getbbidx();
	void PreRTV(std::shared_ptr<ComandManager>& comand);
	void PostRTV(std::shared_ptr<ComandManager>& comand);
	void CreateRTVHeap(std::shared_ptr<D3D12DeviceManager>& device, ID3D12DescriptorHeap** heap);
	void CreateRTVView(std::shared_ptr<D3D12DeviceManager>& device, ID3D12Resource* buffer, ID3D12DescriptorHeap* rtvheap);
	/// <summary>
	/// RTVdescheapÇï‘Ç∑
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& GetRTVDescHeap();

private:

	std::vector<ID3D12Resource*> _renderTargets;
	std::shared_ptr<RenderTargetCreate> _rtc;
	UINT _bbIndex;
	ResourceBarrier* _resocebarrier;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvdescheap;



};