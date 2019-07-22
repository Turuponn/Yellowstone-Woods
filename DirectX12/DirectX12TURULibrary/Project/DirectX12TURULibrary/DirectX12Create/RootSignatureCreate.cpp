#include "RootSignatureCreate.h"
#include "../GameError.h"
#include <d3d12.h>


RootSignatureCreate::RootSignatureCreate() {
	_errorblob = nullptr;
}
RootSignatureCreate::~RootSignatureCreate() {
	if (_errorblob != NULL) {
		_errorblob->Release();
	}
}

void RootSignatureCreate::CreateRootSigneture(ID3D12Device* device, ID3DBlob* signature, ID3D12RootSignature** rootsignature) {
	// ���[�g�V�O�j�`���𐶐�
	HRESULT result = E_FAIL;
	result = device->CreateRootSignature(
		0, // GPU operation, set this to zero
		signature->GetBufferPointer(),//�u���u�̎w��
		signature->GetBufferSize(),//�u���u�T�C�Y
		IID_PPV_ARGS(rootsignature)
	);

	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("RootSignatureCreate::CreateRootSignetur() result != S_OK")));
	}
}

void RootSignatureCreate::SilializeRootsignature(const  std::vector<D3D12_STATIC_SAMPLER_DESC>& StaticSamplers, std::vector<D3D12_ROOT_PARAMETER>& numParameters, ID3DBlob** signature) {
	D3D12_ROOT_SIGNATURE_DESC root_signature_desc = {};

	HRESULT result = E_FAIL;
	D3D12_ROOT_PARAMETER* paramarry = &numParameters[0];
	root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	root_signature_desc.NumStaticSamplers = (UINT)StaticSamplers.size();//�ÓI�T���v����
	root_signature_desc.NumParameters = (UINT)numParameters.size();//�p�����[�^��
	root_signature_desc.pStaticSamplers = &StaticSamplers[0];//�e�N�X�`���T���v��
	root_signature_desc.pParameters = paramarry;


	// �V���A���C�Y����
	result = D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, signature, &_errorblob);
	if (result != S_OK) {
		if (_errorblob != NULL) {
			OutputDebugStringA((char*)_errorblob->GetBufferPointer());
		}
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("RootSignatureCreate::SilializeRootsignature() result != S_OK")));
	}

}