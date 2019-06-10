#pragma once

#include <vector>
struct ID3D12Device;
struct D3D12_ROOT_PARAMETER;
struct D3D12_STATIC_SAMPLER_DESC;
struct ID3D12RootSignature;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

class RootSignatureCreate {
public:
	RootSignatureCreate();
	virtual ~RootSignatureCreate();
	/// <summary>
	/// ���[�g�V�O�l�`���쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="signature">�V���A���C�Y�������V�O�l�`��������</param>
	/// <param name="rootsignature">[out]�@���[�g�V�O�l�`����Ԃ�</param>
	void CreateRootSigneture(ID3D12Device* device, ID3DBlob* signature, ID3D12RootSignature** rootsignature);
	/// <summary>
	/// ���[�g�V�O�l�`�����V���A���C�Y������
	/// </summary>
	/// <param name="staticsamplers">�T���v��</param>
	/// <param name="numparameters">���[�g�p�����[�^</param>
	/// <param name="signature">[out]�V���A���C�Y�������V�O�l�`����Ԃ�</param>
	void SilializeRootsignature(const  std::vector<D3D12_STATIC_SAMPLER_DESC>& staticsamplers, std::vector<D3D12_ROOT_PARAMETER>& numparameters, ID3DBlob** signature);
private:
	ID3DBlob* _errorblob;//�G���[�p
};
