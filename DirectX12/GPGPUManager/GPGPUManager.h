#pragma once


#include <memory>
#include <wrl.h>

class D3D12DeviceManager;
class ComandManager;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
class ComputeShadaManager;
class PipelineStateManager;
class RootSignatureManager;
struct ID3D12PipelineState;
class FenceManager;

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
	virtual ~GPGPUManager();

	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur, std::shared_ptr<ComandManager>& comand);

	void Update(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);


private:
	std::shared_ptr<ComputeShadaManager> _csm;
	std::shared_ptr<PipelineStateManager> _pmanager;

	ID3D12PipelineState* _pipelinestate;//
	float* _address;
};
