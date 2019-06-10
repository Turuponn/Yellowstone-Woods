#pragma once



#include <memory>
#include <vector>
#include <wrl.h>

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
class Layer;
class Camera;

class DeferredShading {
private:
	void CreateRT(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateSRV(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand);
	void CreatePipeline(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature);
	void CreateGbuffer(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature);
	void CreateVS();
	void CreatePS();
	void CreateGS();
	void Draw(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);
public:
	DeferredShading();
	virtual ~DeferredShading();

	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature);

	
	/// <summary>
	/// 遅延レンダリング
	/// </summary>
	void PreRender(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<RenderTargetManager>& rtvmanager, 
		std::shared_ptr<DepthManager>& depth,
		std::shared_ptr< Camera>& camera,
		std::shared_ptr< FenceManager>& fence
	);
	void PostRender(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);

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


	std::shared_ptr<Layer> _layer;
	std::shared_ptr<PipelineStateManager> _mrtPipeline;
	std::shared_ptr<VertexShadaManager> _vs;
	std::shared_ptr<PixcelShadaManager> _ps;
	std::shared_ptr<GSManager> _gs;

};