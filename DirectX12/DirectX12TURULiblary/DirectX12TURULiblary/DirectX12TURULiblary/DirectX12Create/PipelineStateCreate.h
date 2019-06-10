#pragma once



#include <vector>

struct ID3D12Device;
struct ID3D12RootSignature;
struct D3D12_INPUT_ELEMENT_DESC;
struct ID3D12PipelineState;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;
enum DXGI_FORMAT;
enum D3D12_PRIMITIVE_TOPOLOGY_TYPE;

struct PSTATE {
	ID3D12Device* device;
	ID3D12RootSignature* rootsignature;
	ID3DBlob* vs;
	ID3DBlob* ps;
	ID3DBlob* gs;
	D3D12_INPUT_ELEMENT_DESC* inputlaout;
	const unsigned int inputlayoutelement;
	D3D12_PRIMITIVE_TOPOLOGY_TYPE ptype;
};
struct PSTATE_CS {
	ID3D12Device* device;
	ID3D12RootSignature* rootsignature;
	ID3DBlob* cs;//ComputeShada
};

class PipelineStateCreate {
public:
	PipelineStateCreate();
	virtual ~PipelineStateCreate();
	/// <summary>
	/// �p�C�v���C���X�e�[�g�쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rootsignature"></param>
	/// <param name="vs"> ���_�V�F�[�_</param>
	/// <param name="ps"> �s�N�Z���V�F�[�_</param>
	/// <param name="inputlaout">  IA���͗p�Z�}���e�B�N�X�̔z�������</param>
	/// <param name="inputlayoutelement"> IA���͗p�Z�}���e�B�N�X�̔z��̗v�f��</param>
	/// <param name="pipelineobj"> [out] �p�C�v���C����Ԃ�</param>
	void CreatePipelineStateObj(
		ID3D12Device* device,
		ID3D12RootSignature* rootsignature,
		ID3DBlob* vs,
		ID3DBlob* ps,
		D3D12_INPUT_ELEMENT_DESC* inputlaout,
		const unsigned int inputlayoutelement,
		ID3D12PipelineState** pipelineobj
	);
	//SVTarget���������VS�����ł��w�肪�\
	void CreatePipelineStateObjShadowMap(
		ID3D12Device* device,
		ID3D12RootSignature* rootsignature, 
		ID3DBlob* vs,
		D3D12_INPUT_ELEMENT_DESC* inputlaout,
		const unsigned int inputlayoutelement,
		ID3D12PipelineState** pipelineobj
	);
	//���ǔ�
	void PipelineStateCreate::CreatePipelineStateObjShadowMap2(
		ID3D12Device* device,
		ID3D12RootSignature* rootsignature,
		ID3DBlob* vs,
		ID3DBlob* ps,
		D3D12_INPUT_ELEMENT_DESC* inputlaout,
		const unsigned int inputlayoutelement,
		ID3D12PipelineState** pipelineobj
	);
	//rtv�̃t�H�[�}�b�g��
	void CreatePipelineStateObj(
		ID3D12Device* device,
		ID3D12RootSignature* rootsignature,
		ID3DBlob* vs,
		ID3DBlob* ps,
		D3D12_INPUT_ELEMENT_DESC* inputlaout,
		const unsigned int inputlayoutelement,
		ID3D12PipelineState** pipelineobj,
		DXGI_FORMAT rtv_format
	);
	/// <summary>
	/// CubeMap�p�p�C�v���C���쐬���܂�
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rootsignature"></param>
	/// <param name="vs"></param>
	/// <param name="ps"></param>
	/// <param name="inputlaout"></param>
	/// <param name="inputlayoutelement"></param>
	/// <param name="pipelineobj">[out]</param>
	/// <param name="rtv_format"></param>
	/// <param name="m4xMsaaState"> Msaa���g�p���邩 true:4 false:1</param>
	/// <param name="m4xMsaaQuality"> </param>
	void CreatePipelineStateCubeMap(
		ID3D12Device* device,
		ID3D12RootSignature* rootsignature,
		ID3DBlob* vs,
		ID3DBlob* ps,
		D3D12_INPUT_ELEMENT_DESC* inputlaout,
		const unsigned int inputlayoutelement,
		ID3D12PipelineState** pipelineobj,
		DXGI_FORMAT rtv_format,
		bool m4xMsaaState,
		int m4xMsaaQuality
	);
	/// <summary>
	/// MRT�ɑΉ������f�B�t�@�[�h�pPSO
	/// </summary>
	/// <param name="pstate"></param>
	/// <param name="rtv_formats"></param>
	/// <param name="pipelineobj">[out]</param>
	void CreatePStateObjDeferred(
		PSTATE& pstate,
		std::vector<DXGI_FORMAT>& rtv_formats,
		ID3D12PipelineState** pipelineobj
	);
	/// <summary>
	/// �R���s���[�g�V�F�[�_�p�̃p�C�v���C���̍쐬
	/// </summary>
	/// <param name="cstate">[out]</param>
	void CreateComputePipelineState(PSTATE_CS& cstate, ID3D12PipelineState** pipelineobj);
};