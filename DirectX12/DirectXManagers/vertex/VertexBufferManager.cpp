#include "VertexBufferManager.h"
#include "Library\GameError.h"
#include "Library\DirectX12Create\VertexBufferCreate.h"
#include "Library\DirectX12Create\VertexBufferView.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "Library\DirectX12Create\ResoceMapUnmap.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "constance.h"
#include <d3d12.h>



VertexBufferManager::VertexBufferManager() {
	buffsize = 0;
	_vertexview = nullptr;
}
VertexBufferManager::~VertexBufferManager() {
	SAFE_DELETE(_vertexview);
}

void VertexBufferManager::CreateVertexBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int vertexarryysize, const int onevertexsize) {
	std::shared_ptr<ResoceMapUnmap> rmU(new ResoceMapUnmap());
	_resocemapunmap = rmU;
	
	CreateBuffer(device, vertexarryysize*onevertexsize);//要素数*1頂点のサイズ＝全頂点サイズ
	CreateView(onevertexsize);
}

void VertexBufferManager::CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device,const int allvertexsize) {
	std::shared_ptr<VertexBufferCreate> vb(new VertexBufferCreate());
	buffsize = allvertexsize;
	vb->CreateBuffer(device->GetDevice().Get(), allvertexsize, &_vertexbuffer);
}
void VertexBufferManager::CreateView(const int onevertexsize) {
	if (buffsize == 0) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR,_T("buffsize == 0")));
	}
	std::shared_ptr<VertexBufferView> vbv(new VertexBufferView());
	vbv->CreateVertexBufferView(_vertexbuffer.Get(), buffsize, onevertexsize, &_vertexview);
}

D3D12_VERTEX_BUFFER_VIEW*& VertexBufferManager::GetVertexBufferView() {
	return _vertexview;
}


void VertexBufferManager::ResoceMap(void* vertexaddress) {
	//アドレスと紐づける
	_resocemapunmap->Buffer_Map(vertexaddress, _vertexbuffer.Get());
}
void VertexBufferManager::ResoceUnmap() {
	//バッファは読み込み専用みたいにする
	_resocemapunmap->Buffer_Unmap(_vertexbuffer.Get());
}
void VertexBufferManager::ResoceGPUWait(std::shared_ptr<FenceManager>& fence,std::shared_ptr<ComandManager>& comand) {
	auto rb = _vertexbuffer.Get();
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ, rb);
	comand->ComandClose();
	comand->ComandExecuteCommandList();
	comand->ComandListWaitPorlling(fence);
}
