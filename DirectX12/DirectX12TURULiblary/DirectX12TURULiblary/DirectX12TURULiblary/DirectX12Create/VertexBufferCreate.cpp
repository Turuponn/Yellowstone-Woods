#include "VertexBufferCreate.h"
#include <d3d12.h>
#include "../d3dx12.h"
#include "GameError.h"

VertexBufferCreate::VertexBufferCreate() {

}
VertexBufferCreate::~VertexBufferCreate() {

}

void VertexBufferCreate::CreateBuffer(ID3D12Device* device, const int buffersize, ID3D12Resource** buffer) {
	//頂点リソース
	HRESULT result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//リソースをUPLOADとして使用
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((int)(buffersize)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(buffer)
	);

	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("VertexCreateBuffer() result != S_OK")));
	}
}