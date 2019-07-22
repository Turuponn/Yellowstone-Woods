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
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();//���[�g�V�O�l�`��
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
	d3d12_gpsd.SampleMask = UINT_MAX;//���W�X�^���ő��ʂ�


	//���X�^���C�U�X�e�[�g�̐ݒ�
	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//�J�����O���g�p���܂���
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
	d3d12_gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//�O�p�`
	d3d12_gpsd.NumRenderTargets = 1;//�����_�[�^�[�Q�b�g�̐�
	d3d12_gpsd.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//�����_�[�^�[�Q�b�g�̃t�H�[�}�b�g
	d3d12_gpsd.SampleDesc.Count = 1;//�A���`�G�C���A�V���O�p

	//�[�x�o�b�t�@����ǉ�����
	d3d12_gpsd.DepthStencilState.DepthEnable = true;//�[�x�o�b�t�@�g�p
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//�S���ʂ�
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

	//�V�F�[�_�[�̐ݒ�
	pipeline_state_desc.VS.pShaderBytecode = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).pShaderBytecode;
	pipeline_state_desc.VS.BytecodeLength = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).BytecodeLength;


	//�C���v�b�g���C�A�E�g�̐ݒ�
	pipeline_state_desc.InputLayout.pInputElementDescs = pstate.inputlaout;
	pipeline_state_desc.InputLayout.NumElements = pstate.inputlayoutelement;


	//�T���v���n�̐ݒ�
	pipeline_state_desc.SampleDesc.Count = 1;
	pipeline_state_desc.SampleDesc.Quality = 0;
	pipeline_state_desc.SampleMask = UINT_MAX;

	//�O�p�`�ɐݒ�
	pipeline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	//���[�g�V�O�l�`��
	pipeline_state_desc.pRootSignature = pstate.rootsignature.Get();


	//���X�^���C�U�X�e�[�g�̐ݒ�
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


	//�u�����h�X�e�[�g�̐ݒ�
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


	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
	pipeline_state_desc.DepthStencilState.DepthEnable = TRUE;								//�[�x�e�X�g����
	pipeline_state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	pipeline_state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipeline_state_desc.DepthStencilState.StencilEnable = FALSE;							//�X�e���V���e�X�g�Ȃ�
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

	//�V�F�[�_�[�̐ݒ�
	pipeline_state_desc.VS.pShaderBytecode = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).pShaderBytecode;
	pipeline_state_desc.VS.BytecodeLength = CD3DX12_SHADER_BYTECODE(pstate.vs.Get()).BytecodeLength;
	pipeline_state_desc.PS.pShaderBytecode = CD3DX12_SHADER_BYTECODE(pstate.ps.Get()).pShaderBytecode;
	pipeline_state_desc.PS.BytecodeLength = CD3DX12_SHADER_BYTECODE(pstate.ps.Get()).BytecodeLength;

	//�C���v�b�g���C�A�E�g�̐ݒ�
	pipeline_state_desc.InputLayout.pInputElementDescs = pstate.inputlaout;
	pipeline_state_desc.InputLayout.NumElements = pstate.inputlayoutelement;


	//�T���v���n�̐ݒ�
	pipeline_state_desc.SampleDesc.Count = 1;
	pipeline_state_desc.SampleDesc.Quality = 0;
	pipeline_state_desc.SampleMask = UINT_MAX;

	//�O�p�`�ɐݒ�
	pipeline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	//���[�g�V�O�l�`��
	pipeline_state_desc.pRootSignature = pstate.rootsignature.Get();


	//���X�^���C�U�X�e�[�g�̐ݒ�
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


	//�u�����h�X�e�[�g�̐ݒ�
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


	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
	pipeline_state_desc.DepthStencilState.DepthEnable = TRUE;								//�[�x�e�X�g����
	pipeline_state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	pipeline_state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipeline_state_desc.DepthStencilState.StencilEnable = FALSE;							//�X�e���V���e�X�g�Ȃ�
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



	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//�J�����𒆂ɓ���邽��off
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
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();//���[�g�V�O�l�`��
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
	d3d12_gpsd.SampleMask = UINT_MAX;//���W�X�^���ő��ʂ�


	//���X�^���C�U�X�e�[�g�̐ݒ�
	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//�J�����O���g�p���܂���
	d3d12_gpsd.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	d3d12_gpsd.RasterizerState.FrontCounterClockwise = FALSE;
	d3d12_gpsd.RasterizerState.DepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthBiasClamp = 0;
	d3d12_gpsd.RasterizerState.SlopeScaledDepthBias = 0;
	d3d12_gpsd.RasterizerState.DepthClipEnable = TRUE;
	d3d12_gpsd.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	d3d12_gpsd.RasterizerState.AntialiasedLineEnable = FALSE;
	d3d12_gpsd.RasterizerState.MultisampleEnable = FALSE;


	
	//�u�����h�X�e�[�g�̐ݒ�
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
	d3d12_gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//�O�p�`
	d3d12_gpsd.NumRenderTargets = 1;//�����_�[�^�[�Q�b�g�̐�
	d3d12_gpsd.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//�����_�[�^�[�Q�b�g�̃t�H�[�}�b�g
	d3d12_gpsd.SampleDesc.Count = 1;//�A���`�G�C���A�V���O�p

	//�[�x�o�b�t�@����ǉ�����
	d3d12_gpsd.DepthStencilState.DepthEnable = true;//�[�x�o�b�t�@�g�p
	d3d12_gpsd.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//�S���ʂ�
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
	d3d12_gpsd.pRootSignature = pstate.rootsignature.Get();//���[�g�V�O�l�`��
	d3d12_gpsd.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	d3d12_gpsd.VS = CD3DX12_SHADER_BYTECODE(pstate.vs.Get());
	d3d12_gpsd.PS = CD3DX12_SHADER_BYTECODE(pstate.ps.Get());
	d3d12_gpsd.GS = CD3DX12_SHADER_BYTECODE(pstate.gs.Get());
	d3d12_gpsd.SampleMask = UINT_MAX;


	//���X�^���C�U�X�e�[�g�̐ݒ�
	d3d12_gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//�J�����O���Ȃ�
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
	d3d12_gpsd.NumRenderTargets = rtv_formats.size();//�����_�[�^�[�Q�b�g�̐�
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
	D3D12_COMPUTE_PIPELINE_STATE_DESC desc{};//�O���t�B�b�N�p�C�v���C���Ƃ͈Ⴄ���ɑ��݂���i���͕ʂ̃p�C�v���C���j
	desc.CS = CD3DX12_SHADER_BYTECODE(cstate.cs.Get());
	desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.pRootSignature = cstate.rootsignature.Get();
	if (cstate.device->CreateComputePipelineState(&desc, IID_PPV_ARGS(pipelineobj)) != S_OK) {
		throw(1);
	}
}