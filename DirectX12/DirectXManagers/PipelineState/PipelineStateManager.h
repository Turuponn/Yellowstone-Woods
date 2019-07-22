#pragma once

#include <memory>
#include <vector>
#include <wrl.h>

class PipelineStateCreate;
class RootSignatureManager;
class ComandManager;
class SwapChainManager;
class D3D12DeviceManager;
class VertexShadaManager;
class PixcelShadaManager;
class ComputeShadaManager;
class GSManager;

struct D3D12_INPUT_ELEMENT_DESC;
struct ID3D12PipelineState;
struct ID3D12RootSignature;

enum DXGI_FORMAT;




struct PSTATEM {
	std::shared_ptr<D3D12DeviceManager> device;
	std::shared_ptr<RootSignatureManager> rootsignature;
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


/*
1マテリアル 1PSO
*/
class PipelineStateManager {
private:

public:
	PipelineStateManager();
	~PipelineStateManager();
	/// <summary>
	///パイプラインステートを作る 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rootsignetur"></param>
	/// <param name="inputlaout"></param>
	/// <param name="inputLayoutNumElements"></param>
	/// <param name="vartexshada"></param>
	/// <param name="pixelshada"></param>
    void CreatePipelineState(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<RootSignatureManager>& rootsignetur,
		D3D12_INPUT_ELEMENT_DESC* inputlaout, 
		const unsigned int inputLayoutNumElements,
		std::shared_ptr<VertexShadaManager>& vartexshada,
		std::shared_ptr<PixcelShadaManager>& pixelshada
	);
	/// <summary>
	/// CubeMap用パイプラインステートを作成する
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rootsignetur"></param>
	/// <param name="inputlaout"></param>
	/// <param name="inputLayoutNumElements"></param>
	/// <param name="vartexshada"></param>
	/// <param name="pixelshada"></param>
	void CreatePipelineStateCubeMap(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<RootSignatureManager>& rootsignetur,
		D3D12_INPUT_ELEMENT_DESC* inputlaout,
		const unsigned int inputLayoutNumElements,
		std::shared_ptr<VertexShadaManager>& vartexshada,
		std::shared_ptr<PixcelShadaManager>& pixelshada
	);
	/// <summary>
	/// ディファード用パイプラインの作成
	/// </summary>
	/// <param name="pstate"></param>
	/// <param name="rtv_formats"> レンダーターゲットのそれぞれの型</param>
	void CreatePStateDeferred(
		PSTATEM& pstate,
		std::vector<DXGI_FORMAT>& rtv_formats
	);
	/// <summary>
	/// 2D用パイプラインステートを作成する
	/// </summary>
	/// <param name="pstate"></param>
	void CreatePipeline2D(PSTATEM& pstate);
	/// <summary>
	/// コンピュートシェーダ用パイプラインの作成
	/// </summary>
	/// <param name="compute"></param>
	void CreateComputeShadaPipeline(
		PSTATEM_COMPUTE& compute
	);
	//パイプラインをセットする
	void SetPipeline(std::shared_ptr<ComandManager>& comand);
	//パイプラインをリセットする
	void ReSetPipeline(std::shared_ptr<ComandManager>& comand, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// パイプラインを返す
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D12PipelineState>& GetPipelineState();


private:
	Microsoft::WRL::ComPtr<ID3D12PipelineState> _pipelinestate;//パイプライン
};
