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
	/// パイプラインステート作成
	/// </summary>
	/// <param name="pipelineobj"> [out] パイプラインを返す</param>
	void CreatePipelineStateObj(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);
	//SVTargetさえあればVSだけでも指定が可能
	void CreatePipelineStateObjShadowMap(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);
	//改良版
	void PipelineStateCreate::CreatePipelineStateObjShadowMap2(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);
	//rtvのフォーマットつき
	void CreatePipelineStateObj(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj,
		DXGI_FORMAT rtv_format
	);
	/// <summary>
	/// 2D用パイプラインステートを作成します。2D用に加算合成をサポートしません。
	/// </summary>
	/// <param name="pipelineobj"></param>
	void CreatePipelineStateObj2D(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj
	);

	/// <summary>
	/// CubeMap用パイプライン作成します
	/// </summary>
	/// <param name="pipelineobj">[out]</param>
	/// <param name="rtv_format"></param>
	/// <param name="m4xMsaaState"> Msaaを使用するか true:4 false:1</param>
	/// <param name="m4xMsaaQuality"> </param>
	void CreatePipelineStateCubeMap(
		PSTATE& pstate,
		ID3D12PipelineState** pipelineobj,
		DXGI_FORMAT rtv_format,
		bool m4xMsaaState,
		int m4xMsaaQuality
	);
	/// <summary>
	/// MRTに対応したディファード用PSO
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
	/// コンピュートシェーダ用のパイプラインの作成
	/// </summary>
	/// <param name="cstate">[out]</param>
	void CreateComputePipelineState(PSTATE_CS& cstate, ID3D12PipelineState** pipelineobj);
};