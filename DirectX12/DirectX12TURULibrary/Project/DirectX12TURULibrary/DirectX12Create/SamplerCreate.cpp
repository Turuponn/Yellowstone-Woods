#include "SamplerCreate.h"
#include <d3d12.h>
#include "../GameError.h"


SamplerCreate::SamplerCreate() {
}
SamplerCreate::~SamplerCreate() {
}

D3D12_STATIC_SAMPLER_DESC SamplerCreate::StaticSampTexture(const unsigned int registerslotnum) {

	D3D12_STATIC_SAMPLER_DESC _staticsamplerdesc = {};

	//サンプラの設定
	_staticsamplerdesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;//特別なフィルタを使用しない
	_staticsamplerdesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticsamplerdesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticsamplerdesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticsamplerdesc.MipLODBias = 0.0f;//MIPMAPのバイアス 
	_staticsamplerdesc.MaxAnisotropy = 0;//Filter が Anisotropy の時のみ有効
	_staticsamplerdesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;//特に比較しない
	_staticsamplerdesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;//エッジの色(黒透明) 
	_staticsamplerdesc.MinLOD = 0.0f;//MIPMAP下限なし
	_staticsamplerdesc.MaxLOD = D3D12_FLOAT32_MAX;//MIPMAP上限なし
	_staticsamplerdesc.ShaderRegister = registerslotnum;//使用するシェーダレジスタ(スロット)
	_staticsamplerdesc.RegisterSpace = 0;//0でいい
	_staticsamplerdesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//どのくらいのデータをシェーダに見せるか(全部)

	return _staticsamplerdesc;
}


D3D12_STATIC_SAMPLER_DESC SamplerCreate::StaticSampTexture2(const unsigned int registerslotnum, AddressingMode& mode) {

	D3D12_STATIC_SAMPLER_DESC _staticsamplerdesc = {};

	//サンプラの設定
	_staticsamplerdesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	_staticsamplerdesc.AddressU = mode.addressU;
	_staticsamplerdesc.AddressV = mode.addressV;
	_staticsamplerdesc.AddressW = mode.addressW;
	_staticsamplerdesc.MipLODBias = 0.0f;
	_staticsamplerdesc.MaxAnisotropy = 0;
	_staticsamplerdesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	_staticsamplerdesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	_staticsamplerdesc.MinLOD = 0.0f;
	_staticsamplerdesc.MaxLOD = D3D12_FLOAT32_MAX;
	_staticsamplerdesc.ShaderRegister = registerslotnum;
	_staticsamplerdesc.RegisterSpace = 0;
	_staticsamplerdesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	return _staticsamplerdesc;
}


D3D12_STATIC_SAMPLER_DESC SamplerCreate::StaticSampTextureFilltering(const unsigned int registerslotnum, AddressingMode& mode, D3D12_FILTER& filltermode,int maxmaxAnisotropy) {

	D3D12_STATIC_SAMPLER_DESC _staticsamplerdesc = {};


	_staticsamplerdesc.Filter = filltermode;//フィルタリングするときのモード
	_staticsamplerdesc.AddressU = mode.addressU;
	_staticsamplerdesc.AddressV = mode.addressV;
	_staticsamplerdesc.AddressW = mode.addressW;
	_staticsamplerdesc.MipLODBias = 0.0f;
	_staticsamplerdesc.MaxAnisotropy = maxmaxAnisotropy;//最大異方性フィルタ値
	_staticsamplerdesc.ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	_staticsamplerdesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	_staticsamplerdesc.MinLOD = 0.0f;
	_staticsamplerdesc.MaxLOD = D3D12_FLOAT32_MAX;
	_staticsamplerdesc.ShaderRegister = registerslotnum;
	_staticsamplerdesc.RegisterSpace = 0;
	_staticsamplerdesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	return _staticsamplerdesc;
}

D3D12_STATIC_SAMPLER_DESC SamplerCreate::StaticSampTextureFilltering(const unsigned int registerslotnum, AddressingMode& mode, D3D12_FILTER& filltermode, D3D12_COMPARISON_FUNC&  comparison,int maxmaxAnisotropy) {

	D3D12_STATIC_SAMPLER_DESC _staticsamplerdesc = {};


	_staticsamplerdesc.Filter = filltermode;//フィルタリングするときのモード
	_staticsamplerdesc.AddressU = mode.addressU;
	_staticsamplerdesc.AddressV = mode.addressV;
	_staticsamplerdesc.AddressW = mode.addressW;
	_staticsamplerdesc.MipLODBias = 0.0f;
	_staticsamplerdesc.MaxAnisotropy = maxmaxAnisotropy;//最大異方性フィルタ値
	_staticsamplerdesc.ComparisonFunc = comparison;
	_staticsamplerdesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	_staticsamplerdesc.MinLOD = 0.0f;
	_staticsamplerdesc.MaxLOD = D3D12_FLOAT32_MAX;
	_staticsamplerdesc.ShaderRegister = registerslotnum;
	_staticsamplerdesc.RegisterSpace = 0;
	_staticsamplerdesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	return _staticsamplerdesc;
}