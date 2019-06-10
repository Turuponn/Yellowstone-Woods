#pragma once


#include <memory>
#include <wrl.h>

class IndexBufferCreate;
struct ID3D12Resource;
struct D3D12_INDEX_BUFFER_VIEW;
class D3D12DeviceManager;
class IndexBufferView;
class ResoceMapUnmap;






class IndexBufferManager {
private:
	//インデックスバッファ作成
	//@param allindexsize　全インデックスサイズを入れる　インデックス数*1頂点番号サイズ
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allindexsize, const size_t oneindexsize);
public:

	IndexBufferManager();
	virtual ~IndexBufferManager();
	//初期化
	//@param allindexsize　全インデックスサイズを入れる　インデックス数*1頂点番号サイズ
	//@param  oneindexsize　一インデックスのサイズ
	void CreateIndexBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allindexsize, const size_t oneindexsize);
	//インデックスビューの作成
	//@param allindexsize　全インデックスサイズを入れる　インデックス数*1頂点番号サイズ
	//@param  oneindexsize　一インデックスのサイズ
	void CreateBufferView(const int allindexsize, const size_t oneindexsize, const int vertexnum);
	void CreateBufferViewR16(const int allindexsize, const size_t oneindexsize);
	void CreateBufferViewR32(const int allindexsize, const size_t oneindexsize);
	D3D12_INDEX_BUFFER_VIEW*& GetIndexBufferView();
	/// <summary>
	/// リソースをマップする
	/// </summary>
	/// <param name="indexaddress"> &をつかってデータのアドレスを入れる</param>
	void ResoceMap(void* indexaddress);
	//リソースをアンマップする
	void ResoceUnmap();

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> _indexbuffer;
	D3D12_INDEX_BUFFER_VIEW* _indexbufferview;
	std::shared_ptr<ResoceMapUnmap> _resocemapunmap;
};