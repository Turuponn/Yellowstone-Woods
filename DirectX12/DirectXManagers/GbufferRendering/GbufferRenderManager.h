#pragma once


#include <vector>
#include <wrl.h>
#include <memory>



struct ID3D12DescriptorHeap;
class D3D12DeviceManager;
struct ID3D12Resource;
class TextureManager;
class DepthManager;
class PipelineStateManager;
class RootSignatureManager;
class PixcelShadaManager;
class VertexShadaManager;
enum DXGI_FORMAT;
class ComandManager;
class RenderTargetManager;
class FenceManager;
class GSManager;

class GbufferRenderManager {
private:
	void CreateRT(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateSRV(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand);
	void CreatePipeline(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature);
	void CreateVS();
	void CreatePS();
	void CreateGS();
public:
	GbufferRenderManager();
	virtual ~GbufferRenderManager();

	/// <summary>
	/// オフスクリーンバッファを作成する
	/// </summary>
	/// <param name="device"></param>
	void CreateGbuffer(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature);
	/// <summary>
	/// 遅延レンダリング開始
	/// </summary>
	void PreRender(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RenderTargetManager>& rtvmanager, std::shared_ptr<DepthManager>& depth);
	/// <summary>
	/// 遅延レンダリング終了
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="fence"></param>
	/// <param name="usetex"></param>
	void PostRender(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);
	/// <summary>
	/// キューブマップ用パイプラインに変更
	/// </summary>
	void SetCMapPipeline(std::shared_ptr<ComandManager>& comand);
	/// <summary>
	/// 通常描画用パイプラインへ変更
	/// </summary>
	/// <param name="comand"></param>
	void SetDrawPipeline(std::shared_ptr<ComandManager>& comand);
private:
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> _rtvbuffer;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvheap;
	std::vector<std::shared_ptr<TextureManager>> _texMs;
	std::vector<DXGI_FORMAT> _rtvformats;



	std::shared_ptr<PipelineStateManager> _mrtPipeline;
	std::shared_ptr<PipelineStateManager> _cmapP;
	std::shared_ptr<VertexShadaManager> _vs;
	std::shared_ptr<VertexShadaManager> _cmapvs;
	std::shared_ptr<PixcelShadaManager> _ps;
	std::shared_ptr<PixcelShadaManager> _cmapps;
	std::shared_ptr<GSManager> _gs;


};