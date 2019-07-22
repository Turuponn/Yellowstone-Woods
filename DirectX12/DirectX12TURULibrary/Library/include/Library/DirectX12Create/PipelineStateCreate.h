#pragma once



#include <vector>
#include <wrl.h>

struct ID3D12Device;
struct ID3D12RootSignature;
struct D3D12_INPUT_ELEMENT_DESC;
struct ID3D12PipelineState;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;
enum DXGI_FORMAT;
enum D3D12_PRIMITIVE_TOPOLOGY_TYPE;

struct PSTATE {
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
	Microsoft::WRL::ComPtr<ID3DBlob> vs;
	Microsoft::WRL::ComPtr<ID3DBlob> ps;
	Microsoft::WRL::ComPtr<ID3DBlob> gs;
	D3D12_INPUT_ELEMENT_DESC* inputlaout;
	const unsigned int inputlayoutelement;
	D3D12_PRIMITIVE_TOPOLOGY_TYPE ptype;
};
struct PSTATE_CS {
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
	Microsoft::WRL::ComPtr<ID3DBlob> cs;//ComputeShada
};

class PipelineStateCreate {
public:
	PipelineStateCreate();
	virtual ~PipelineStateCreate();
	/// <summary>
	/// �p�C�v���C���X�e�[�g�쐬
	/// </summary>
	/// <param name="pipelineobj"> [out] �p�C�v���C����Ԃ�</param>
	void CreatePipelineStateObj(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);
	//SVTarget���������VS�����ł��w�肪�\
	void CreatePipelineStateObjShadowMap(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);
	//���ǔ�
	void PipelineStateCreate::CreatePipelineStateObjShadowMap2(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);
	//rtv�̃t�H�[�}�b�g��
	void CreatePipelineStateObj(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj,
		DXGI_FORMAT rtv_format
	);
	/// <summary>
	/// 2D�p�p�C�v���C���X�e�[�g���쐬���܂��B2D�p�ɉ��Z�������T�|�[�g���܂���B
	/// </summary>
	/// <param name="pipelineobj"></param>
	void CreatePipelineStateObj2D(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);

	/// <summary>
	/// CubeMap�p�p�C�v���C���쐬���܂�
	/// </summary>
	/// <param name="pipelineobj">[out]</param>
	/// <param name="rtv_format"></param>
	/// <param name="m4xMsaaState"> Msaa���g�p���邩 true:4 false:1</param>
	/// <param name="m4xMsaaQuality"> </param>
	void CreatePipelineStateCubeMap(
		PSTATE& pstate,
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