#include "SamplerCreate.h"
#include <d3d12.h>
#include "../GameError.h"


SamplerCreate::SamplerCreate() {
}
SamplerCreate::~SamplerCreate() {
}

D3D12_STATIC_SAMPLER_DESC SamplerCreate::StaticSampTexture(const unsigned int registerslotnum) {

	D3D12_STATIC_SAMPLER_DESC _staticsamplerdesc = {};

	//�T���v���̐ݒ�
	_staticsamplerdesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;//���ʂȃt�B���^���g�p���Ȃ�
	_staticsamplerdesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticsamplerdesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticsamplerdesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_staticsamplerdesc.MipLODBias = 0.0f;//MIPMAP�̃o�C�A�X 
	_staticsamplerdesc.MaxAnisotropy = 0;//Filter �� Anisotropy �̎��̂ݗL��
	_staticsamplerdesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;//���ɔ�r���Ȃ�
	_staticsamplerdesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;//�G�b�W�̐F(������) 
	_staticsamplerdesc.MinLOD = 0.0f;//MIPMAP�����Ȃ�
	_staticsamplerdesc.MaxLOD = D3D12_FLOAT32_MAX;//MIPMAP����Ȃ�
	_staticsamplerdesc.ShaderRegister = registerslotnum;//�g�p����V�F�[�_���W�X�^(�X���b�g)
	_staticsamplerdesc.RegisterSpace = 0;//0�ł���
	_staticsamplerdesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�ǂ̂��炢�̃f�[�^���V�F�[�_�Ɍ����邩(�S��)

	return _staticsamplerdesc;
}


D3D12_STATIC_SAMPLER_DESC SamplerCreate::StaticSampTexture2(const unsigned int registerslotnum, AddressingMode& mode) {

	D3D12_STATIC_SAMPLER_DESC _staticsamplerdesc = {};

	//�T���v���̐ݒ�
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


	_staticsamplerdesc.Filter = filltermode;//�t�B���^�����O����Ƃ��̃��[�h
	_staticsamplerdesc.AddressU = mode.addressU;
	_staticsamplerdesc.AddressV = mode.addressV;
	_staticsamplerdesc.AddressW = mode.addressW;
	_staticsamplerdesc.MipLODBias = 0.0f;
	_staticsamplerdesc.MaxAnisotropy = maxmaxAnisotropy;//�ő�ٕ����t�B���^�l
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


	_staticsamplerdesc.Filter = filltermode;//�t�B���^�����O����Ƃ��̃��[�h
	_staticsamplerdesc.AddressU = mode.addressU;
	_staticsamplerdesc.AddressV = mode.addressV;
	_staticsamplerdesc.AddressW = mode.addressW;
	_staticsamplerdesc.MipLODBias = 0.0f;
	_staticsamplerdesc.MaxAnisotropy = maxmaxAnisotropy;//�ő�ٕ����t�B���^�l
	_staticsamplerdesc.ComparisonFunc = comparison;
	_staticsamplerdesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	_staticsamplerdesc.MinLOD = 0.0f;
	_staticsamplerdesc.MaxLOD = D3D12_FLOAT32_MAX;
	_staticsamplerdesc.ShaderRegister = registerslotnum;
	_staticsamplerdesc.RegisterSpace = 0;
	_staticsamplerdesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	return _staticsamplerdesc;
}