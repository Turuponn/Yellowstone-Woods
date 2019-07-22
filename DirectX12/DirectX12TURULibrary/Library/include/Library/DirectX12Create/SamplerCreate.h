#pragma once

struct D3D12_STATIC_SAMPLER_DESC;
enum D3D12_TEXTURE_ADDRESS_MODE;
enum D3D12_FILTER;
enum D3D12_COMPARISON_FUNC;

struct AddressingMode {
	D3D12_TEXTURE_ADDRESS_MODE addressU;
	D3D12_TEXTURE_ADDRESS_MODE addressV;
	D3D12_TEXTURE_ADDRESS_MODE addressW;
};

class SamplerCreate {
public:
	SamplerCreate();
	virtual ~SamplerCreate();
	/// <summary>
	/// �T���v�����쐬����
	/// </summary>
	/// <param name="registerslotnum"> ���[�g�V�O�l�`���ɓo�^�����T���v���̃��W�X�^�ԍ�</param>
	/// <returns>[out] �T���v���f�X�N���v�^��Ԃ�</returns>
	D3D12_STATIC_SAMPLER_DESC StaticSampTexture(const unsigned int registerslotnum);
	/// <summary>
	/// �T���v�����쐬
	/// </summary>
	/// <param name="registerslotnum"> ���[�g�V�O�l�`���ɓo�^�����T���v���̃��W�X�^�ԍ� </param>
	/// <param name="mode">D3D12_TEXTURE_ADDRESS_MODE </param>
	/// <returns>�T���v���f�X�N���v�^��Ԃ�</returns>
	D3D12_STATIC_SAMPLER_DESC StaticSampTexture2(const unsigned int registerslotnum, AddressingMode& mode);
	/// <summary>
	/// �t�B���^�����O����
	/// </summary>
	/// <param name="registerslotnum"></param>
	/// <param name="mode"></param>
	/// <param name="filltermode"> �t�B���^�[���[�h������</param>
	/// <param name="maxmaxAnisotropy">�ő�ٕ����l</param>
	/// <returns></returns>
	D3D12_STATIC_SAMPLER_DESC StaticSampTextureFilltering(const unsigned int registerslotnum, AddressingMode& mode, D3D12_FILTER& filltermode, int maxmaxAnisotropy);
	D3D12_STATIC_SAMPLER_DESC StaticSampTextureFilltering(const unsigned int registerslotnum, AddressingMode& mode, D3D12_FILTER& filltermode, D3D12_COMPARISON_FUNC&  comparison, int maxmaxAnisotropy);

private:

};
