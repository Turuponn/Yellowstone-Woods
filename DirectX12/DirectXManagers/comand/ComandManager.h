#pragma once

#include <memory>
#include <vector>
#include <wrl.h>

enum D3D_PRIMITIVE_TOPOLOGY;
enum D3D12_RESOURCE_STATES;

struct ID3D12DescriptorHeap;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;
struct D3D12_VIEWPORT;
struct CD3DX12_CPU_DESCRIPTOR_HANDLE;
struct ID3D12Resource;
struct tagRECT;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;


class VertexBufferManager;
class IndexBufferManager;
class ConstantManager;
class TextureManager;
class SwapChainManager;
class DepthManager;
class ResourceBarrier;
class D3D12DeviceManager;
class ComandCreate;
class FenceManager;
class PipelineStateManager;
class RootSignatureManager;

class ComandManager{
private:
	void Initialize();
public:
	ComandManager();
	~ComandManager();
	/// <summary>
	/// コマンドキューを作成します
	/// </summary>
	/// <param name="device"></param>
	void CreateComandQueue(std::shared_ptr<D3D12DeviceManager>& device);
	/// <summary>
	/// コマンドリストを作成します
	/// </summary>
	/// <param name="device"></param>
	void CreateComandList(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// コマンドアロケータをフレームバッファ総数分作成します
	/// </summary>
	/// <param name="device"></param>
	/// <param name="swapchain"></param>
	void CreateComandAllocators(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain);
	// バックバッファ描画完了までポーリングで待機する
	void ComandListWaitPorlling(std::shared_ptr<FenceManager>& fence);
	//コマンドをすべて閉じる
	void ComandClose();
	//ヒープに溜まっているコマンドをすべてリセットする
	void ComandReset(std::shared_ptr<SwapChainManager>& swapchain);
	//パイプラインをセットする
	void SetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate);
	//パイプラインをリセットする
	void ReSetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate, std::shared_ptr<SwapChainManager>& swapchain);
	//すべてのパイプラインをリセット
	void ReSetPipeline(std::shared_ptr<SwapChainManager>& swapchain);
	//ルートシグネチャをアタッチする
	void RootSignatureAttach(std::shared_ptr<RootSignatureManager>& rootsignature);
	//ビューポートの指定
	void ComandRSSetViewPorts(const int viewportnum, D3D12_VIEWPORT& viewport);
	//シザー矩形(見える範囲の指定
	void ComandRSSetScissorRects(const int scissorrectnum, tagRECT& scissorRect);
	//描画対象の指定
	void ComandOMSetRenderTargets(const int numrtv, ID3D12DescriptorHeap*& descheap, std::shared_ptr<DepthManager>& depth);
	//深度情報をクリア
	void ComandClearDepthStencilView(std::shared_ptr<DepthManager>& depth);
	//描画対象の色設定
	void ComandClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE& rtv, float* clearcolor);
	//リソースの状態を設定する
	void ComandRBarrier(D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource*& tergetresoce);
	/// <summary>
	/// リソースの状態を設定する : 配列版
	/// </summary>
	/// <param name="resocenum"> そのバッファ全体のリソース数</param>
	/// <param name="statebefore"></param>
	/// <param name="stateafter"></param>
	/// <param name="tergetresoce"></param>
	void ComandRBarrierArry(const int resocenum,D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource*& tergetresoce);
	//
	void ComandIASetVertexBuffers(std::shared_ptr<VertexBufferManager>& vbm);
	//トポロジ
	void ComandIASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);
	//
	void ComandIASetIndexBuffer(std::shared_ptr<IndexBufferManager>& indexm);
	//インデックスづけされた描画
	void ComandDrawIndexedInstanced(const int instancenum, const int fecenum);
	// インデックスづけされていない描画
	void ComandDrawInstanced(const int vertexnum, const int instancenum);
	//ヒープの設定
	void ComandSetDescriptorHeaps(const int descheapnum, ID3D12DescriptorHeap*&  heap);
	//ルートシグネチャのスロットと定数を同期させる
	void ComandSetGraphicsRootDescriptorTable(const int rootparamidx, ID3D12DescriptorHeap*& heap);
	//コマンドリストにためておいたコマンドをすべて実行させる
	void ComandExecuteCommandList();

	//キューを返す
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>& GetComandQueue();
	//アロケータを返す
	std::vector< Microsoft::WRL::ComPtr<ID3D12CommandAllocator>>& GetComandAllocators();
	//リストを返す
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList>& GetGraphicsCommandList();
private:
	std::shared_ptr<ComandCreate> _comandcreate;
	std::shared_ptr<ResourceBarrier> _rb;
	std::vector< Microsoft::WRL::ComPtr<ID3D12CommandAllocator>> _comandAllocators;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> _comandQueue;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> _comandList;
};
