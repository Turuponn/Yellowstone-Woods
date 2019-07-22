#include "DirectXManagers\index\IndexBufferManager.h"
#include "Library\GameError.h"
#include "Library\DirectX12Create\IndexBufferCreate.h"
#include "Library\DirectX12Create\IndexBufferView.h"
#include "constance.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include <d3d12.h>
#include "Library\DirectX12Create\ResoceMapUnmap.h"


IndexBufferManager::IndexBufferManager() {
	_indexbufferview = nullptr;
}
IndexBufferManager::~IndexBufferManager() {
	SAFE_DELETE(_indexbufferview);
	
}

void IndexBufferManager::CreateIndexBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allindexsize, const size_t oneindexsize) {
	std::shared_ptr<ResoceMapUnmap> rmU(new ResoceMapUnmap());
	_resocemapunmap = rmU;
	CreateBuffer(device, allindexsize, oneindexsize);
}
void IndexBufferManager::CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allindexsize, const size_t oneindexsize) {
	std::shared_ptr<IndexBufferCreate> ib(new IndexBufferCreate());
	ib->CreateIndexBuffer(device->GetDevice().Get(), allindexsize, (const int)oneindexsize, &_indexbuffer);
}

void IndexBufferManager::CreateBufferView(const int allindexsize, const size_t oneindexsize, const int vertexnum) {
	std::shared_ptr<IndexBufferView> ibv(new IndexBufferView());
	ibv->CreateIndexView(_indexbuffer.Get(), allindexsize, oneindexsize, vertexnum, &_indexbufferview);
}
void IndexBufferManager::CreateBufferViewR16(const int allindexsize, const size_t oneindexsize) {
	std::shared_ptr<IndexBufferView> ibv(new IndexBufferView());
	ibv->CreateIndexViewR16(_indexbuffer.Get(), allindexsize, oneindexsize, 0, &_indexbufferview);
}
void IndexBufferManager::CreateBufferViewR32(const int allindexsize, const size_t oneindexsize) {
	std::shared_ptr<IndexBufferView> ibv(new IndexBufferView());
	ibv->CreateIndexViewR32(_indexbuffer.Get(), allindexsize, oneindexsize, 0, &_indexbufferview);
}
D3D12_INDEX_BUFFER_VIEW*& IndexBufferManager::GetIndexBufferView() {
	return _indexbufferview;
}
void IndexBufferManager::ResoceMap(void* indexaddress) {
	//アドレスと紐づける
	_resocemapunmap->Buffer_Map(indexaddress, _indexbuffer.Get());
}
void IndexBufferManager::ResoceUnmap() {
	//バッファは読み込み専用にする
	_resocemapunmap->Buffer_Unmap(_indexbuffer.Get());
}
