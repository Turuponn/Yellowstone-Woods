#pragma once


#include <memory>

class D3D12DeviceManager;
class ComandManager;
class ComputeShadaManager;
class PipelineStateManager;
class RootSignatureManager;
class FenceManager;
class SwapChainManager;

struct ID3D12PipelineState;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;



class GPGPUManager {
private:
	void InitShada(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur);
	void CreateCSPipeline(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur);
	void CreateCShada();
private:
	void CreateUAVView(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateUAVHeap(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateUAVBuffer(std::shared_ptr<D3D12DeviceManager>& device);
public:
	GPGPUManager();
	~GPGPUManager();

	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur, std::shared_ptr<ComandManager>& comand);

	void Update(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<SwapChainManager>& swapchain);


private:
	std::shared_ptr<ComputeShadaManager> _csm;
	std::shared_ptr<PipelineStateManager> _pmanager;

	ID3D12PipelineState* _pipelinestate;//
	float* _address;
};
