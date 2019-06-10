#include "ConstanceBufferCreate.h"
#include <d3d12.h>
#include "../d3dx12.h"
#include "GameError.h"


ConstanceBufferCreate::ConstanceBufferCreate() {

}
ConstanceBufferCreate::~ConstanceBufferCreate() {

}


void ConstanceBufferCreate::CreateConstanceBuffer(ID3D12Device* device,const int aligndescsize, ID3D12Resource** constantbuffer) {
	HRESULT result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(aligndescsize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(constantbuffer)
	);

	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("ConstanceBufferCreate::CreateConstanceBuffer() result != S_OK")));
	}
}