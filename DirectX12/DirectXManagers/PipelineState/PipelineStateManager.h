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

	
	//パイプラインステートを作る
	//@  テクスチャマネージャーを入れる
	//@inputlaout      レイアウト
	//@inputLayoutNumElements 頂点レイアウトの要素数
	//@device          DX12デバイズ
	//@vartexshada     頂点シェーダ
	//@pixelshada      ピクセルシェーダ
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
	/// ディファード用パイプラインの作成
	/// </summary>
	/// <param name="pstate"></param>
	/// <param name="rtv_formats"> レンダーターゲットのそれぞれの型</param>
	void CreatePStateDeferred(
		PSTATEM& pstate,
		std::vector<DXGI_FORMAT>& rtv_formats
	);
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
	void ReSetPipeline(std::shared_ptr<ComandManager>& comand);
	/// <summary>
	/// パイプラインを返す TODO？: グラフィックス用かそれ以外も含めている
	/// </summary>
	/// <returns></returns>
	ID3D12PipelineState*& GetPipelineState();


private:
	ID3D12PipelineState* _pipelinestate;//パイプライン
};
