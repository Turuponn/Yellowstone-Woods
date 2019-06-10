#pragma once

#include <memory>
#include <vector>

class PipelineStateCreate;
class RootSignatureManager;
class ComandManager;
struct D3D12_INPUT_ELEMENT_DESC;
class D3D12DeviceManager;
class VertexShadaManager;
class PixcelShadaManager;
struct ID3D12PipelineState;
struct ID3D12RootSignature;
enum DXGI_FORMAT;
class ComputeShadaManager;
class GSManager;



struct PSTATEM {
	std::shared_ptr<D3D12DeviceManager> device;
	std::shared_ptr<RootSignatureManager> rootsignetur;
	D3D12_INPUT_ELEMENT_DESC* inputlaout;
	const unsigned int inputLayoutNumElements;
	std::shared_ptr<VertexShadaManager> vartexshada;
	std::shared_ptr<PixcelShadaManager> pixelshada;
	std::shared_ptr<GSManager> geometryshada;
};
struct PSTATEM_COMPUTE {
	std::shared_ptr<D3D12DeviceManager> device;
	std::shared_ptr<RootSignatureManager> rootsignetur;
	std::shared_ptr<ComputeShadaManager> csm;
};



class PipelineStateManager {
private:

public:
	PipelineStateManager();
	virtual ~PipelineStateManager();

	
	//�p�C�v���C���X�e�[�g�����
	//@  �e�N�X�`���}�l�[�W���[������
	//@inputlaout      ���C�A�E�g
	//@inputLayoutNumElements ���_���C�A�E�g�̗v�f��
	//@device          DX12�f�o�C�Y
	//@vartexshada     ���_�V�F�[�_
	//@pixelshada      �s�N�Z���V�F�[�_
    void CreatePiplineState(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<RootSignatureManager>& rootsignetur,
		D3D12_INPUT_ELEMENT_DESC* inputlaout, 
		const unsigned int inputLayoutNumElements,
		std::shared_ptr<VertexShadaManager>& vartexshada,
		std::shared_ptr<PixcelShadaManager>& pixelshada
	);
	
	void CreatePiplineStateCubeMap(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<RootSignatureManager>& rootsignetur,
		D3D12_INPUT_ELEMENT_DESC* inputlaout,
		const unsigned int inputLayoutNumElements,
		std::shared_ptr<VertexShadaManager>& vartexshada,
		std::shared_ptr<PixcelShadaManager>& pixelshada
	);
	/// <summary>
	/// �f�B�t�@�[�h�p�p�C�v���C���̍쐬
	/// </summary>
	/// <param name="pstate"></param>
	/// <param name="rtv_formats"> �����_�[�^�[�Q�b�g�̂��ꂼ��̌^</param>
	void CreatePStateDeferred(
		PSTATEM& pstate,
		std::vector<DXGI_FORMAT>& rtv_formats
	);
	/// <summary>
	/// �R���s���[�g�V�F�[�_�p�p�C�v���C���̍쐬
	/// </summary>
	/// <param name="compute"></param>
	void CreateComputeShadaPipeline(
		PSTATEM_COMPUTE& compute
	);
	//�p�C�v���C�����Z�b�g����
	void SetPipeline(std::shared_ptr<ComandManager>& comand);
	//�p�C�v���C�������Z�b�g����
	void ReSetPipeline(std::shared_ptr<ComandManager>& comand);
	/// <summary>
	/// �p�C�v���C����Ԃ� TODO�H: �O���t�B�b�N�X�p������ȊO���܂߂Ă���
	/// </summary>
	/// <returns></returns>
	ID3D12PipelineState*& GetPipelineState();


private:
	ID3D12PipelineState* _pipelinestate;//�p�C�v���C��
};
