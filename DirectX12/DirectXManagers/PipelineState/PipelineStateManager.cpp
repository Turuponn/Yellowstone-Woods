#include "PipelineStateManager.h"
#include <d3d12.h>
#include "d3dx12.h"
#include "Library\GameError.h"
#include "constance.h"
#include "Library\DirectX12Create\PipelineStateCreate.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Shada\Vertex\VertexShadaManager.h"
#include "DirectXManagers\Shada\Pixcel\PixcelShadaManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\Shada\CS\ComputeShadaManager.h"
#include "DirectXManagers\swapchain\SwapChainManager.h"
#include "DirectXManagers\Shada\GS\GSManager.h"

PipelineStateManager::PipelineStateManager() {
	_pipelinestate = nullptr;
	
}
PipelineStateManager::~PipelineStateManager() {
	SAFE_RELEASE(_pipelinestate);
}

void PipelineStateManager::CreatePiplineState(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur, D3D12_INPUT_ELEMENT_DESC* inputlaout, const unsigned int inputLayoutNumElements, std::shared_ptr<VertexShadaManager>& vartexshada, std::shared_ptr<PixcelShadaManager>& pixelshada) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	pipe->CreatePipelineStateObj(device->GetDevice(), rootsignetur->GetRootSignature(), vartexshada->GetVertexShada().Get(), pixelshada->GetPixelShada().Get(), inputlaout, inputLayoutNumElements, &_pipelinestate);
}
void PipelineStateManager::CreatePiplineStateCubeMap(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur, D3D12_INPUT_ELEMENT_DESC* inputlaout, const unsigned int inputLayoutNumElements, std::shared_ptr<VertexShadaManager>& vartexshada, std::shared_ptr<PixcelShadaManager>& pixelshada) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	pipe->CreatePipelineStateCubeMap(
		device->GetDevice(),
		rootsignetur->GetRootSignature(),
		vartexshada->GetVertexShada().Get(),
		pixelshada->GetPixelShada().Get(),
		inputlaout, inputLayoutNumElements,
		&_pipelinestate,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		false,
		0
	);
}
void PipelineStateManager::CreatePStateDeferred(PSTATEM& pstate, std::vector<DXGI_FORMAT>& rtv_formats) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	PSTATE p = {
	pstate.device->GetDevice(),
	pstate.rootsignetur->GetRootSignature(),
	pstate.vartexshada->GetVertexShada().Get(),
	pstate.pixelshada->GetPixelShada().Get(),
	pstate.geometryshada->GetBlob().Get(),
	pstate.inputlaout,
	pstate.inputLayoutNumElements,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE
	};
	

	pipe->CreatePStateObjDeferred(p, rtv_formats, &_pipelinestate);
}
void PipelineStateManager::CreateComputeShadaPipeline(PSTATEM_COMPUTE& compute) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	D3D12_COMPUTE_PIPELINE_STATE_DESC desc{};
	desc.CS = CD3DX12_SHADER_BYTECODE(compute.csm->GetCSShada().Get());
	desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.pRootSignature = compute.rootsignetur->GetRootSignature();
	if (compute.device->GetDevice()->CreateComputePipelineState(&desc, IID_PPV_ARGS(&_pipelinestate)) != S_OK) {
		throw(1);
	}
}
void PipelineStateManager::SetPipeline(std::shared_ptr<ComandManager>& comand) {
	comand->GetGraphicsCommandList()->SetPipelineState(_pipelinestate);
}
void PipelineStateManager::ReSetPipeline(std::shared_ptr<ComandManager>& comand,std::shared_ptr<SwapChainManager>& swapchain) {
	comand->GetGraphicsCommandList()->Reset(comand->GetComandAllocators()[swapchain->GetFrameBufferIndex()].Get(), _pipelinestate);
}

ID3D12PipelineState*& PipelineStateManager::GetPipelineState() {
	return _pipelinestate;
}