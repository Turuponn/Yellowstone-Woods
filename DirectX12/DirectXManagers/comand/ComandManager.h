#pragma once

#include <memory>
#include <wrl.h>

class D3D12DeviceManager;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;
class ComandCreate;
class FenceManager;
class PipelineStateManager;
class RootSignatureManager;
struct D3D12_VIEWPORT;

struct CD3DX12_CPU_DESCRIPTOR_HANDLE;
class DepthManager;
class ResourceBarrier;
enum D3D12_RESOURCE_STATES;
struct ID3D12Resource;

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

struct tagRECT;

class VertexBufferManager;
class IndexBufferManager;
class ConstantManager;
class TextureManager;
enum D3D_PRIMITIVE_TOPOLOGY;

struct ID3D12DescriptorHeap;

class ComandManager{
protected:
	
public:
	ComandManager();
	virtual ~ComandManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device);
	// バックバッファ描画完了までポーリングで待機する
	void ComandListWaitPorlling(std::shared_ptr<FenceManager>& fence);
	//コマンドをすべて閉じる
	void ComandClose();
	//ヒープに溜まっているコマンドをすべてリセットする
	void ComandReset();
	//パイプラインをセットする
	void SetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate);
	//パイプラインをリセットする
	void ReSetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate);
	//すべてのパイプラインをリセット
	void ReSetPipeline();
	//ルートシグネチャをアタッチする
	void RootSignatureAttach(std::shared_ptr<RootSignatureManager>& rootsignature);
	//ビューポートの指定
	void ComandRSSetViewPorts(const int viewportnum, D3D12_VIEWPORT& viewport);
	//シザー矩形(見える範囲の指定
	void ComandRSSetScissorRects(const int scissorrectnum, tagRECT& scissorRect);
	//描画対象の指定
	void ComandOMSetRenderTargets(const int numrtv, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descheap, std::shared_ptr<DepthManager>& depth);
	//深度情報をクリア
	void ComandClearDepthStencilView(std::shared_ptr<DepthManager>& depth);
	//描画対象の色設定
	void ComandClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE& rtv, float* clearcolor);
	//リソースの状態を設定する
	void ComandRBarrier(D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource* tergetresoce);
	/// <summary>
	/// リソースの状態を設定する : 配列版
	/// </summary>
	/// <param name="resocenum"> そのバッファ全体のリソース数</param>
	/// <param name="statebefore"></param>
	/// <param name="stateafter"></param>
	/// <param name="tergetresoce"></param>
	void ComandRBarrierArry(const int resocenum,D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource* tergetresoce);
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
	void ComandSetDescriptorHeaps(const int descheapnum, ID3D12DescriptorHeap*  heap);
	//ルートシグネチャのスロットと定数を同期させる
	void ComandSetGraphicsRootDescriptorTable(const int rootparamidx, ID3D12DescriptorHeap* heap);
	//コマンドリストにためておいたコマンドをすべて実行させる
	void ComandExecuteCommandList();

	//キューを返す
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>& GetComandQueue();
	//アロケータを返す
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>& GetComandAllocator();
	//リストを返す
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& GetGraphicsCommandList();
private:
	std::shared_ptr<ComandCreate> _comandcreate;
	std::shared_ptr<ResourceBarrier> _rb;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _comandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _comandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> _comand_queue;
};
