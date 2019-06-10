#pragma once


#include <memory>
#include <wrl.h>

class VertexBufferCreate;
class VertexBufferView;
struct ID3D12Resource;
struct D3D12_VERTEX_BUFFER_VIEW;
class D3D12DeviceManager;
class ResoceMapUnmap;
class FenceManager;
class ComandManager;

class VertexBufferManager {
private:
	//頂点バッファ作成
	//@param allvertexsize 全頂点サイズ
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allvertexsize);
	//ビュー作成
	//@param onevertexsize 一頂点あたりのサイズ
	void CreateView(const int onevertexsize);
public:
	VertexBufferManager();
	virtual ~VertexBufferManager();

	//初期化
	//@param allvertexsize 全頂点サイズ
	//@param onevertexsize 一頂点あたりのサイズ
	void CreateVertexBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allvertexsize, const int onevertexsize);

	//マップ
	void ResoceMap(void* vertexaddress);
	//アンマップ
	void ResoceUnmap();
	//GPUに送られるまで待つ処理
	void ResoceGPUWait(std::shared_ptr<FenceManager>& fence, std::shared_ptr<ComandManager>& comand);

	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW*& GetVertexBufferView();



private:
	std::shared_ptr<ResoceMapUnmap> _resocemapunmap;
	Microsoft::WRL::ComPtr<ID3D12Resource> _vertexbuffer;
	D3D12_VERTEX_BUFFER_VIEW* _vertexview;
};
