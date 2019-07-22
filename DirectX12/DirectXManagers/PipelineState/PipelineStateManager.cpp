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
}
PipelineStateManager::~PipelineStateManager() {
}

void PipelineStateManager::CreatePipelineState(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur, D3D12_INPUT_ELEMENT_DESC* inputlaout, const unsigned int inputLayoutNumElements, std::shared_ptr<VertexShadaManager>& vartexshada, std::shared_ptr<PixcelShadaManager>& pixelshada) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	PSTATE pstate = {
		device->GetDevice(),
		rootsignetur->GetRootSignature(),
		vartexshada->GetVertexShada(),
		pixelshada->GetPixelShada(),
		nullptr,
		inputlaout,
		inputLayoutNumElements,
	};
	pipe->CreatePipelineStateObj(pstate, &_pipelinestate);
}
void PipelineStateManager::CreatePipelineStateCubeMap(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur, D3D12_INPUT_ELEMENT_DESC* inputlaout, const unsigned int inputLayoutNumElements, std::shared_ptr<VertexShadaManager>& vartexshada, std::shared_ptr<PixcelShadaManager>& pixelshada) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	PSTATE pstate = {
		device->GetDevice(),
		rootsignetur->GetRootSignature(),
		vartexshada->GetVertexShada(),
		pixelshada->GetPixelShada(),
		nullptr,
		inputlaout,
		inputLayoutNumElements,
	};
	pipe->CreatePipelineStateCubeMap(
		pstate,
		&_pipelinestate,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		false,
		0
	);
}
void PipelineStateManager::CreatePStateDeferred(PSTATEM& pstate, std::vector<DXGI_FORMAT>& rtv_formats) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	PSTATE p = {
	pstate.device->GetDevice().Get(),
	pstate.rootsignature->GetRootSignature().Get(),
	pstate.vartexshada->GetVertexShada().Get(),
	pstate.pixelshada->GetPixelShada().Get(),
	pstate.geometryshada->GetBlob().Get(),
	pstate.inputlaout,
	pstate.inputLayoutNumElements,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE
	};
	pipe->CreatePStateObjDeferred(p, rtv_formats, &_pipelinestate);
}
void PipelineStateManager::CreatePipeline2D(PSTATEM& pstate) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	PSTATE pstates = {
		pstate.device->GetDevice(),
		pstate.rootsignature->GetRootSignature(),
		pstate.vartexshada->GetVertexShada(),
		pstate.pixelshada->GetPixelShada(),
		nullptr,
		pstate.inputlaout,
		pstate.inputLayoutNumElements,
	};
	/*pipe->CreatePipelineStateObj2D(
		pstates,
		&_pipelinestate
	);*/
	HRESULT result = E_FAIL;


	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d12_gpsd = {};
	d3d12_gpsd.pRootSignature = pstates.rootsignature.Get();//ルートシグネチャ
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstates.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstates.ps.Get());
	d3d12_gpsd.SampleMask = UINT_MAX;//レジスタ数最大を通す


	//ラスタライザステートの設定
	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//カリングを使用しません
	d3d12_gpsd.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	d3d12_gpsd.RasterizerState.FrontCounterClockwise = FALSE;
	d3d12_gpsd.RasterizerState.DepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthBiasClamp = 0;
	d3d12_gpsd.RasterizerState.SlopeScaledDepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthClipEnable = TRUE;
	d3d12_gpsd.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	d3d12_gpsd.RasterizerState.AntialiasedLineEnable = FALSE;
	d3d12_gpsd.RasterizerState.MultisampleEnable = FALSE;



	//ブレンドステートの設定
	//合成として表示させるなら全て描画後、G-buffer内で行う
	for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
		d3d12_gpsd.BlendState.RenderTarget[i].BlendEnable = TRUE;
		d3d12_gpsd.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_SRC_ALPHA;
		d3d12_gpsd.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;//加算合成
	}

	d3d12_gpsd.DepthStencilState.StencilEnable = false;
	d3d12_gpsd.InputLayout.NumElements = pstates.inputlayoutelement;
	d3d12_gpsd.InputLayout.pInputElementDescs = pstates.inputlaout;
	d3d12_gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形
	d3d12_gpsd.NumRenderTargets = 1;//レンダーターゲットの数
	d3d12_gpsd.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//レンダーターゲットのフォーマット
	d3d12_gpsd.SampleDesc.Count = 1;//アンチエイリアシング用

	//深度バッファ情報を追加する
	d3d12_gpsd.DepthStencilState.DepthEnable = true;//深度バッファ使用
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//全部通す
	d3d12_gpsd.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3d12_gpsd.DSVFormat = DXGI_FORMAT_D32_FLOAT;



	result = pstates.device.Get()->CreateGraphicsPipelineState(&d3d12_gpsd, IID_PPV_ARGS(&_pipelinestate));
	if (result != S_OK) {
		throw(1);
	}
}
void PipelineStateManager::CreateComputeShadaPipeline(PSTATEM_COMPUTE& compute) {
	std::shared_ptr<PipelineStateCreate> pipe(new PipelineStateCreate());
	D3D12_COMPUTE_PIPELINE_STATE_DESC desc{};
	desc.CS = CD3DX12_SHADER_BYTECODE(compute.csm->GetCSShada());
	desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.pRootSignature = compute.rootsignetur->GetRootSignature().Get();
	if (compute.device->GetDevice()->CreateComputePipelineState(&desc, IID_PPV_ARGS(&_pipelinestate)) != S_OK) {
		throw(1);
	}
}
void PipelineStateManager::SetPipeline(std::shared_ptr<ComandManager>& comand) {
	comand->GetGraphicsCommandList()->SetPipelineState(_pipelinestate.Get());
}
void PipelineStateManager::ReSetPipeline(std::shared_ptr<ComandManager>& comand,std::shared_ptr<SwapChainManager>& swapchain) {
	comand->GetGraphicsCommandList()->Reset(comand->GetComandAllocators()[swapchain->GetFrameBufferIndex()].Get(), _pipelinestate.Get());
}

Microsoft::WRL::ComPtr<ID3D12PipelineState>& PipelineStateManager::GetPipelineState() {
	return _pipelinestate;
}