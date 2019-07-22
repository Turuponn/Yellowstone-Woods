#include "PipelineStateCreate.h"
#include <d3d12.h>
#include "../d3dx12.h"
#include "../GameError.h"


PipelineStateCreate::PipelineStateCreate() {

}
PipelineStateCreate::~PipelineStateCreate() {
	
}


void PipelineStateCreate::CreatePipelineStateObj(PSTATE& pstate, ID3D12PipelineState** pipelineobj) {
	HRESULT result = E_FAIL;


	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d12_gpsd = {};
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();//ルートシグネチャ
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
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


	d3d12_gpsd.DepthStencilState.StencilEnable = false;
	d3d12_gpsd.InputLayout.NumElements = pstate.inputlayoutelement;
	d3d12_gpsd.InputLayout.pInputElementDescs = pstate.inputlaout;
	d3d12_gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形
	d3d12_gpsd.NumRenderTargets = 1;//レンダーターゲットの数
	d3d12_gpsd.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//レンダーターゲットのフォーマット
	d3d12_gpsd.SampleDesc.Count = 1;//アンチエイリアシング用

	//深度バッファ情報を追加する
	d3d12_gpsd.DepthStencilState.DepthEnable = true;//深度バッファ使用
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//全部通す
	d3d12_gpsd.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3d12_gpsd.DSVFormat = DXGI_FORMAT_D32_FLOAT;



	result = pstate.device.Get()->CreateGraphicsPipelineState(&d3d12_gpsd, IID_PPV_ARGS(pipelineobj));
	if (result != S_OK) {
		throw(1);
	}
}
void PipelineStateCreate::CreatePipelineStateObjShadowMap(PSTATE& pstate, ID3D12PipelineState** pipelineobj) {

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_state_desc{};
	HRESULT result = E_FAIL;

	//シェーダーの設定
	pipeline_state_desc.VS.pShaderBytecode = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).pShaderBytecode;
	pipeline_state_desc.VS.BytecodeLength = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).BytecodeLength;


	//インプットレイアウトの設定
	pipeline_state_desc.InputLayout.pInputElementDescs = pstate.inputlaout;
	pipeline_state_desc.InputLayout.NumElements = pstate.inputlayoutelement;


	//サンプル系の設定
	pipeline_state_desc.SampleDesc.Count = 1;
	pipeline_state_desc.SampleDesc.Quality = 0;
	pipeline_state_desc.SampleMask = UINT_MAX;

	//三角形に設定
	pipeline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	//ルートシグネチャ
	pipeline_state_desc.pRootSignature = pstate.rootsignature.Get();


	//ラスタライザステートの設定
	pipeline_state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	pipeline_state_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	pipeline_state_desc.RasterizerState.FrontCounterClockwise = FALSE;
	pipeline_state_desc.RasterizerState.DepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthBiasClamp = 0;
	pipeline_state_desc.RasterizerState.SlopeScaledDepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthClipEnable = TRUE;
	pipeline_state_desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	pipeline_state_desc.RasterizerState.AntialiasedLineEnable = FALSE;
	pipeline_state_desc.RasterizerState.MultisampleEnable = FALSE;


	//ブレンドステートの設定
	pipeline_state_desc.BlendState.RenderTarget[0].BlendEnable = FALSE;
	pipeline_state_desc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	pipeline_state_desc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	pipeline_state_desc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	pipeline_state_desc.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	pipeline_state_desc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	pipeline_state_desc.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	pipeline_state_desc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	pipeline_state_desc.BlendState.RenderTarget[0].LogicOpEnable = FALSE;
	pipeline_state_desc.BlendState.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_CLEAR;

	pipeline_state_desc.BlendState.AlphaToCoverageEnable = FALSE;
	pipeline_state_desc.BlendState.IndependentBlendEnable = FALSE;


	//デプスステンシルステートの設定
	pipeline_state_desc.DepthStencilState.DepthEnable = TRUE;								//深度テストあり
	pipeline_state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	pipeline_state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipeline_state_desc.DepthStencilState.StencilEnable = FALSE;							//ステンシルテストなし
	pipeline_state_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
	pipeline_state_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

	pipeline_state_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	pipeline_state_desc.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	pipeline_state_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	result = pstate.device.Get()->CreateGraphicsPipelineState(&pipeline_state_desc, IID_PPV_ARGS(pipelineobj));
	if (result != S_OK) {
		throw(1);
	}
}

void PipelineStateCreate::CreatePipelineStateObjShadowMap2(PSTATE& pstate, ID3D12PipelineState** pipelineobj) {

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_state_desc{};
	HRESULT result = E_FAIL;

	//シェーダーの設定
	pipeline_state_desc.VS.pShaderBytecode = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).pShaderBytecode;
	pipeline_state_desc.VS.BytecodeLength = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).BytecodeLength;
	pipeline_state_desc.PS.pShaderBytecode = CD3DX12_SHADER_BYTECODE(pstate.ps.Get()).pShaderBytecode;
	pipeline_state_desc.PS.BytecodeLength = CD3DX12_SHADER_BYTECODE(pstate.ps.Get()).BytecodeLength;

	//インプットレイアウトの設定
	pipeline_state_desc.InputLayout.pInputElementDescs = pstate.inputlaout;
	pipeline_state_desc.InputLayout.NumElements = pstate.inputlayoutelement;


	//サンプル系の設定
	pipeline_state_desc.SampleDesc.Count = 1;
	pipeline_state_desc.SampleDesc.Quality = 0;
	pipeline_state_desc.SampleMask = UINT_MAX;

	//三角形に設定
	pipeline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	//ルートシグネチャ
	pipeline_state_desc.pRootSignature = pstate.rootsignature.Get();


	//ラスタライザステートの設定
	pipeline_state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//D3D12_CULL_MODE_BACK;
	pipeline_state_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	pipeline_state_desc.RasterizerState.FrontCounterClockwise = FALSE;
	pipeline_state_desc.RasterizerState.DepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthBiasClamp = 0;
	pipeline_state_desc.RasterizerState.SlopeScaledDepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthClipEnable = TRUE;
	pipeline_state_desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	pipeline_state_desc.RasterizerState.AntialiasedLineEnable = FALSE;
	pipeline_state_desc.RasterizerState.MultisampleEnable = FALSE;


	//ブレンドステートの設定
	pipeline_state_desc.BlendState.RenderTarget[0].BlendEnable = FALSE;
	pipeline_state_desc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	pipeline_state_desc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	pipeline_state_desc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	pipeline_state_desc.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	pipeline_state_desc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	pipeline_state_desc.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	pipeline_state_desc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	pipeline_state_desc.BlendState.RenderTarget[0].LogicOpEnable = FALSE;
	pipeline_state_desc.BlendState.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_CLEAR;

	pipeline_state_desc.BlendState.AlphaToCoverageEnable = FALSE;
	pipeline_state_desc.BlendState.IndependentBlendEnable = FALSE;


	//デプスステンシルステートの設定
	pipeline_state_desc.DepthStencilState.DepthEnable = TRUE;								//深度テストあり
	pipeline_state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	pipeline_state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipeline_state_desc.DepthStencilState.StencilEnable = FALSE;							//ステンシルテストなし
	pipeline_state_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
	pipeline_state_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

	pipeline_state_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	pipeline_state_desc.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	pipeline_state_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	result = pstate.device.Get()->CreateGraphicsPipelineState(&pipeline_state_desc, IID_PPV_ARGS(pipelineobj));
	if (result != S_OK) {
		throw(1);
	}
}

void PipelineStateCreate::CreatePipelineStateObj(
	PSTATE& pstate,
	ID3D12PipelineState** pipelineobj,
	DXGI_FORMAT rtv_format
) {
	HRESULT result = E_FAIL;


	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d12_gpsd = {};
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
	d3d12_gpsd.SampleMask = UINT_MAX;


									 
	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	d3d12_gpsd.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	d3d12_gpsd.RasterizerState.FrontCounterClockwise = FALSE;
	d3d12_gpsd.RasterizerState.DepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthBiasClamp = 0;
	d3d12_gpsd.RasterizerState.SlopeScaledDepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthClipEnable = TRUE;
	d3d12_gpsd.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	d3d12_gpsd.RasterizerState.AntialiasedLineEnable = FALSE;
	d3d12_gpsd.RasterizerState.MultisampleEnable = FALSE;


	d3d12_gpsd.DepthStencilState.StencilEnable = false;
	d3d12_gpsd.InputLayout.NumElements = pstate.inputlayoutelement;
	d3d12_gpsd.InputLayout.pInputElementDescs = pstate.inputlaout;
	d3d12_gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3d12_gpsd.NumRenderTargets = 1;
	d3d12_gpsd.RTVFormats[0] = rtv_format;
	d3d12_gpsd.SampleDesc.Count = 1;

	d3d12_gpsd.DepthStencilState.DepthEnable = true;
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3d12_gpsd.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3d12_gpsd.DSVFormat = DXGI_FORMAT_D32_FLOAT;



	result = pstate.device.Get()->CreateGraphicsPipelineState(&d3d12_gpsd, IID_PPV_ARGS(pipelineobj));
	if (result != S_OK) {
		throw(1);
	}
}


void PipelineStateCreate::CreatePipelineStateCubeMap(
	PSTATE& pstate,
	ID3D12PipelineState** pipelineobj,
	DXGI_FORMAT rtv_format,
	bool m4xMsaaState,
	int m4xMsaaQuality

) {
	HRESULT result = E_FAIL;


	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d12_gpsd = {};
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
	d3d12_gpsd.SampleMask = UINT_MAX;



	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//カメラを中に入れるためoff
	d3d12_gpsd.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	d3d12_gpsd.RasterizerState.FrontCounterClockwise = FALSE;
	d3d12_gpsd.RasterizerState.DepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthBiasClamp = 0;
	d3d12_gpsd.RasterizerState.SlopeScaledDepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthClipEnable = TRUE;
	d3d12_gpsd.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	d3d12_gpsd.RasterizerState.AntialiasedLineEnable = FALSE;
	d3d12_gpsd.RasterizerState.MultisampleEnable = FALSE;


	d3d12_gpsd.DepthStencilState.StencilEnable = false;
	d3d12_gpsd.InputLayout.NumElements = pstate.inputlayoutelement;
	d3d12_gpsd.InputLayout.pInputElementDescs = pstate.inputlaout;
	d3d12_gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3d12_gpsd.NumRenderTargets = 1;
	d3d12_gpsd.RTVFormats[0] = rtv_format;
	d3d12_gpsd.SampleDesc.Count = 1;

	d3d12_gpsd.DepthStencilState.DepthEnable = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3d12_gpsd.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3d12_gpsd.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	d3d12_gpsd.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	d3d12_gpsd.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;

	result = pstate.device.Get()->CreateGraphicsPipelineState(&d3d12_gpsd, IID_PPV_ARGS(pipelineobj));
	if (result != S_OK) {
		throw(1);
	}
}
void PipelineStateCreate::CreatePipelineStateObj2D(
	PSTATE& pstate,
	ID3D12PipelineState** pipelineobj
) {
	HRESULT result = E_FAIL;


	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d12_gpsd = {};
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();//ルートシグネチャ
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
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
	d3d12_gpsd.BlendState.RenderTarget[0].BlendEnable = TRUE;
	d3d12_gpsd.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3d12_gpsd.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_DEST_COLOR;
	d3d12_gpsd.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3d12_gpsd.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3d12_gpsd.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3d12_gpsd.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3d12_gpsd.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	d3d12_gpsd.BlendState.RenderTarget[0].LogicOpEnable = FALSE;
	d3d12_gpsd.BlendState.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_CLEAR;
	d3d12_gpsd.BlendState.AlphaToCoverageEnable = FALSE;
	d3d12_gpsd.BlendState.IndependentBlendEnable = FALSE;

	d3d12_gpsd.DepthStencilState.StencilEnable = false;
	d3d12_gpsd.InputLayout.NumElements = pstate.inputlayoutelement;
	d3d12_gpsd.InputLayout.pInputElementDescs = pstate.inputlaout;
	d3d12_gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形
	d3d12_gpsd.NumRenderTargets = 1;//レンダーターゲットの数
	d3d12_gpsd.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//レンダーターゲットのフォーマット
	d3d12_gpsd.SampleDesc.Count = 1;//アンチエイリアシング用

	//深度バッファ情報を追加する
	d3d12_gpsd.DepthStencilState.DepthEnable = true;//深度バッファ使用
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//全部通す
	d3d12_gpsd.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3d12_gpsd.DSVFormat = DXGI_FORMAT_D32_FLOAT;



	result = pstate.device.Get()->CreateGraphicsPipelineState(&d3d12_gpsd, IID_PPV_ARGS(pipelineobj));
	if (result != S_OK) {
		throw(1);
	}
}
void PipelineStateCreate::CreatePStateObjDeferred(PSTATE& pstate, std::vector<DXGI_FORMAT>& rtv_formats, ID3D12PipelineState** pipelineobj) {
	HRESULT result = E_FAIL;


	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d12_gpsd = {};
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();//ルートシグネチャ
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
	d3d12_gpsd.GS = CD3DX12_SHADER_BYTECODE(pstate.gs.Get());
	d3d12_gpsd.SampleMask = UINT_MAX;


	//ラスタライザステートの設定
	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//カリングしない
	d3d12_gpsd.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	d3d12_gpsd.RasterizerState.FrontCounterClockwise = FALSE;
	d3d12_gpsd.RasterizerState.DepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthBiasClamp = 0;
	d3d12_gpsd.RasterizerState.SlopeScaledDepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthClipEnable = TRUE;
	d3d12_gpsd.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	d3d12_gpsd.RasterizerState.AntialiasedLineEnable = FALSE;
	d3d12_gpsd.RasterizerState.MultisampleEnable = FALSE;


	d3d12_gpsd.DepthStencilState.StencilEnable = false;
	d3d12_gpsd.InputLayout.NumElements = pstate.inputlayoutelement;
	d3d12_gpsd.InputLayout.pInputElementDescs = pstate.inputlaout;
	d3d12_gpsd.PrimitiveTopologyType = pstate.ptype;
	d3d12_gpsd.NumRenderTargets = rtv_formats.size();//レンダーターゲットの数
	int rtvindex = 0;
	for (auto& f : rtv_formats) {
		d3d12_gpsd.RTVFormats[rtvindex++] = f;
	}

	
	
	d3d12_gpsd.SampleDesc.Count = 1;

	d3d12_gpsd.DepthStencilState.DepthEnable = true;
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3d12_gpsd.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3d12_gpsd.DSVFormat = DXGI_FORMAT_D32_FLOAT;



	result = pstate.device->CreateGraphicsPipelineState(&d3d12_gpsd, IID_PPV_ARGS(pipelineobj));
	if (result != S_OK) {
		throw(1);
	}
}


void PipelineStateCreate::CreateComputePipelineState(PSTATE_CS& cstate, ID3D12PipelineState** pipelineobj) {
	D3D12_COMPUTE_PIPELINE_STATE_DESC desc{};//グラフィックパイプラインとは違う所に存在する（又は別のパイプライン）
	desc.CS = CD3DX12_SHADER_BYTECODE(cstate.cs.Get());
	desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.pRootSignature = cstate.rootsignature.Get();
	if (cstate.device->CreateComputePipelineState(&desc, IID_PPV_ARGS(pipelineobj)) != S_OK) {
		throw(1);
	}
}