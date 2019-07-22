#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "Library\GameError.h"
#include "constance.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "Library\DirectX12Create\RootSignatureCreate.h"
#include "Library\DirectX12Create\SamplerCreate.h"
#include <d3d12.h>
#include <vector>



RootSignatureManager::RootSignatureManager() {
}
RootSignatureManager::~RootSignatureManager() {
}


void RootSignatureManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<RootSignatureCreate> rs(new RootSignatureCreate());
	_rangeType.resize(ROOT_PARAM_MAX);
	_numParameters.resize(ROOT_PARAM_MAX);
	InitStaticRengeType();
	InitRootParameters();
	InitSmpler();
	rs->SilializeRootsignature(_staticSamplers, _numParameters, &_signatureblob);
	rs->CreateRootSigneture(device->GetDevice().Get(), _signatureblob.Get(), &_rootSignature);
	 
}
void RootSignatureManager::InitSmpler() {
	std::shared_ptr<SamplerCreate> sm(new SamplerCreate());
	AddressingMode mode;

	_staticSamplers.push_back(sm->StaticSampTexture(_rangeType[ROOT_PARAM_TEXTURE].BaseShaderRegister));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_DEPTH].BaseShaderRegister, mode));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_DR].BaseShaderRegister, mode));
	const int ANI_DEFAULTNUM = 0;
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	D3D12_FILTER filter = D3D12_FILTER_MIN_MAG_MIP_POINT;//フィルタリング付きサンプラ
	D3D12_COMPARISON_FUNC comparison = D3D12_COMPARISON_FUNC_ALWAYS;
	_staticSamplers.push_back(sm->StaticSampTextureFilltering(_rangeType[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].BaseShaderRegister, mode, filter, comparison, ANI_DEFAULTNUM));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_DR_COLOR].BaseShaderRegister, mode));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_DR_NORMAL].BaseShaderRegister, mode));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_DR_POS].BaseShaderRegister, mode));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_DL_COLOR].BaseShaderRegister, mode));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_PP_COLOR].BaseShaderRegister, mode));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_CANVAS_COLOR].BaseShaderRegister, mode));
	mode.addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	mode.addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticSamplers.push_back(sm->StaticSampTexture2(_rangeType[ROOT_PARAM_TEXTURE_UAV_TEST].BaseShaderRegister, mode));
	
}

#pragma region RootParameters
void RootSignatureManager::InitRootParameters() {
	
	//テクスチャ用
	_numParameters[ROOT_PARAM_TEXTURE].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE];
	_numParameters[ROOT_PARAM_TEXTURE].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//テクスチャ: Depth
	_numParameters[ROOT_PARAM_TEXTURE_DEPTH].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_DEPTH].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_DEPTH].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_DEPTH];
	_numParameters[ROOT_PARAM_TEXTURE_DEPTH].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//テクスチャ : DR
	_numParameters[ROOT_PARAM_TEXTURE_DR].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_DR].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_DR].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_DR];
	_numParameters[ROOT_PARAM_TEXTURE_DR].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//テクスチャ: サンプラ
	_numParameters[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP];
	_numParameters[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//DR: メインカラー
	_numParameters[ROOT_PARAM_TEXTURE_DR_COLOR].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_DR_COLOR].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_DR_COLOR].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_DR_COLOR];
	_numParameters[ROOT_PARAM_TEXTURE_DR_COLOR].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//DR: 法線マップ
	_numParameters[ROOT_PARAM_TEXTURE_DR_NORMAL].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_DR_NORMAL].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_DR_NORMAL].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_DR_NORMAL];
	_numParameters[ROOT_PARAM_TEXTURE_DR_NORMAL].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//DR: ポジションマップ
	_numParameters[ROOT_PARAM_TEXTURE_DR_POS].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_DR_POS].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_DR_POS].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_DR_POS];
	_numParameters[ROOT_PARAM_TEXTURE_DR_POS].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//DL: color
	_numParameters[ROOT_PARAM_TEXTURE_DL_COLOR].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_DL_COLOR].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_DL_COLOR].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_DL_COLOR];
	_numParameters[ROOT_PARAM_TEXTURE_DL_COLOR].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//PP: color
	_numParameters[ROOT_PARAM_TEXTURE_PP_COLOR].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_PP_COLOR].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_PP_COLOR].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_PP_COLOR];
	_numParameters[ROOT_PARAM_TEXTURE_PP_COLOR].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//Canvas: color
	_numParameters[ROOT_PARAM_TEXTURE_CANVAS_COLOR].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_CANVAS_COLOR].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_CANVAS_COLOR].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_CANVAS_COLOR];
	_numParameters[ROOT_PARAM_TEXTURE_CANVAS_COLOR].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	//UAV用
	_numParameters[ROOT_PARAM_TEXTURE_UAV_TEST].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_TEXTURE_UAV_TEST].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_TEXTURE_UAV_TEST].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_TEXTURE_UAV_TEST];
	_numParameters[ROOT_PARAM_TEXTURE_UAV_TEST].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//だれでも使用可能に　一応
	

	//定数: ディレクショナルライト、ポイントライト
	_numParameters[ROOT_PARAM_CONSTANT_LIGHT].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_CONSTANT_LIGHT].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_CONSTANT_LIGHT].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_CONSTANT_LIGHT];
	_numParameters[ROOT_PARAM_CONSTANT_LIGHT].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//定数: Camera
	_numParameters[ROOT_PARAM_CONSTANT_CAMERA].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_CONSTANT_CAMERA].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_CONSTANT_CAMERA].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_CONSTANT_CAMERA];
	_numParameters[ROOT_PARAM_CONSTANT_CAMERA].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//定数: Layer
	_numParameters[ROOT_PARAM_CONSTANT_LAYER].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_CONSTANT_LAYER].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_CONSTANT_LAYER].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_CONSTANT_LAYER];
	_numParameters[ROOT_PARAM_CONSTANT_LAYER].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//定数: Diffead
	_numParameters[ROOT_PARAM_CONSTANT_DR].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_CONSTANT_DR].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_CONSTANT_DR].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_CONSTANT_DR];
	_numParameters[ROOT_PARAM_CONSTANT_DR].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//定数: TestBone
	_numParameters[ROOT_PARAM_CONSTANT_TESTBONE].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_CONSTANT_TESTBONE].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_CONSTANT_TESTBONE].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_CONSTANT_TESTBONE];
	_numParameters[ROOT_PARAM_CONSTANT_TESTBONE].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//定数: Canvas
	_numParameters[ROOT_PARAM_CONSTANT_CANVAS].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_CONSTANT_CANVAS].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_CONSTANT_CANVAS].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_CONSTANT_CANVAS];
	_numParameters[ROOT_PARAM_CONSTANT_CANVAS].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//UAV: Test
	_numParameters[ROOT_PARAM_UAV_TEST].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_numParameters[ROOT_PARAM_UAV_TEST].DescriptorTable.NumDescriptorRanges = 1;
	_numParameters[ROOT_PARAM_UAV_TEST].DescriptorTable.pDescriptorRanges = &_rangeType[ROOT_PARAM_UAV_TEST];
	_numParameters[ROOT_PARAM_UAV_TEST].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	
}
#pragma endregion

#pragma region RengeType
void RootSignatureManager::InitStaticRengeType() {
	//テクスチャ用
	_rangeType[ROOT_PARAM_TEXTURE].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;//範囲種別
	_rangeType[ROOT_PARAM_TEXTURE].NumDescriptors = 1;//デスクリプタ数
	_rangeType[ROOT_PARAM_TEXTURE].BaseShaderRegister = 0;//シェーダレジスタ(スロットに相当) 
	_rangeType[ROOT_PARAM_TEXTURE].RegisterSpace = 0;//レジスタの範囲 通常は0　　
	_rangeType[ROOT_PARAM_TEXTURE].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//テクスチャ: Depth
	_rangeType[ROOT_PARAM_TEXTURE_DEPTH].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_DEPTH].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_DEPTH].BaseShaderRegister = 1;
	_rangeType[ROOT_PARAM_TEXTURE_DEPTH].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_DEPTH].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//テクスチャ : ModelTex
	_rangeType[ROOT_PARAM_TEXTURE_DR].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_DR].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_DR].BaseShaderRegister = 2;
	_rangeType[ROOT_PARAM_TEXTURE_DR].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_DR].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//テクスチャ : CubeMap
	_rangeType[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].BaseShaderRegister = 3;
	_rangeType[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//DR: メインカラー
	_rangeType[ROOT_PARAM_TEXTURE_DR_COLOR].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_DR_COLOR].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_DR_COLOR].BaseShaderRegister = 4;
	_rangeType[ROOT_PARAM_TEXTURE_DR_COLOR].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_DR_COLOR].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//DR:　法線マップ
	_rangeType[ROOT_PARAM_TEXTURE_DR_NORMAL].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_DR_NORMAL].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_DR_NORMAL].BaseShaderRegister = 5;
	_rangeType[ROOT_PARAM_TEXTURE_DR_NORMAL].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_DR_NORMAL].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//DR:　ポジションマップ
	_rangeType[ROOT_PARAM_TEXTURE_DR_POS].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_DR_POS].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_DR_POS].BaseShaderRegister = 6;
	_rangeType[ROOT_PARAM_TEXTURE_DR_POS].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_DR_POS].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//DL: color
	_rangeType[ROOT_PARAM_TEXTURE_DL_COLOR].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_DL_COLOR].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_DL_COLOR].BaseShaderRegister = 7;
	_rangeType[ROOT_PARAM_TEXTURE_DL_COLOR].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_DL_COLOR].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//PP: color
	_rangeType[ROOT_PARAM_TEXTURE_PP_COLOR].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_PP_COLOR].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_PP_COLOR].BaseShaderRegister = 8;
	_rangeType[ROOT_PARAM_TEXTURE_PP_COLOR].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_PP_COLOR].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//Canvas : color
	_rangeType[ROOT_PARAM_TEXTURE_CANVAS_COLOR].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_CANVAS_COLOR].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_CANVAS_COLOR].BaseShaderRegister = 9;
	_rangeType[ROOT_PARAM_TEXTURE_CANVAS_COLOR].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_CANVAS_COLOR].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;


	//UAV：Test
	_rangeType[ROOT_PARAM_TEXTURE_UAV_TEST].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_rangeType[ROOT_PARAM_TEXTURE_UAV_TEST].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_TEXTURE_UAV_TEST].BaseShaderRegister = 10;
	_rangeType[ROOT_PARAM_TEXTURE_UAV_TEST].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_TEXTURE_UAV_TEST].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;





	//ライト: ディレクショナルライト、ポイントライト
	_rangeType[ROOT_PARAM_CONSTANT_LIGHT].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	_rangeType[ROOT_PARAM_CONSTANT_LIGHT].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_CONSTANT_LIGHT].BaseShaderRegister = 0;
	_rangeType[ROOT_PARAM_CONSTANT_LIGHT].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_CONSTANT_LIGHT].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//コンスタントバッファ:　カメラ
	_rangeType[ROOT_PARAM_CONSTANT_CAMERA].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	_rangeType[ROOT_PARAM_CONSTANT_CAMERA].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_CONSTANT_CAMERA].BaseShaderRegister = 1;
	_rangeType[ROOT_PARAM_CONSTANT_CAMERA].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_CONSTANT_CAMERA].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//定数: Layer
	_rangeType[ROOT_PARAM_CONSTANT_LAYER].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	_rangeType[ROOT_PARAM_CONSTANT_LAYER].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_CONSTANT_LAYER].BaseShaderRegister = 2;
	_rangeType[ROOT_PARAM_CONSTANT_LAYER].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_CONSTANT_LAYER].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//定数: ディファード
	_rangeType[ROOT_PARAM_CONSTANT_DR].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	_rangeType[ROOT_PARAM_CONSTANT_DR].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_CONSTANT_DR].BaseShaderRegister = 3;
	_rangeType[ROOT_PARAM_CONSTANT_DR].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_CONSTANT_DR].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//定数: ボーン
	_rangeType[ROOT_PARAM_CONSTANT_TESTBONE].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	_rangeType[ROOT_PARAM_CONSTANT_TESTBONE].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_CONSTANT_TESTBONE].BaseShaderRegister = 4;
	_rangeType[ROOT_PARAM_CONSTANT_TESTBONE].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_CONSTANT_TESTBONE].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	//定数: Canvas
	_rangeType[ROOT_PARAM_CONSTANT_CANVAS].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	_rangeType[ROOT_PARAM_CONSTANT_CANVAS].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_CONSTANT_CANVAS].BaseShaderRegister = 5;
	_rangeType[ROOT_PARAM_CONSTANT_CANVAS].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_CONSTANT_CANVAS].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//UAV: Test
	_rangeType[ROOT_PARAM_UAV_TEST].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	_rangeType[ROOT_PARAM_UAV_TEST].NumDescriptors = 1;
	_rangeType[ROOT_PARAM_UAV_TEST].BaseShaderRegister = 0;//u0
	_rangeType[ROOT_PARAM_UAV_TEST].RegisterSpace = 0;
	_rangeType[ROOT_PARAM_UAV_TEST].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;



}
#pragma endregion
Microsoft::WRL::ComPtr<ID3D12RootSignature>& RootSignatureManager::GetRootSignature() {
	return _rootSignature;
}

std::vector<D3D12_DESCRIPTOR_RANGE>& RootSignatureManager::GetRengeType() {
	return _rangeType;
}