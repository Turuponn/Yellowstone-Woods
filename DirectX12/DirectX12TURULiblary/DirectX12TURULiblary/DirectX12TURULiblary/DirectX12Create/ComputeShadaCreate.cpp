#include "ComputeShadaCreate.h"
#include <d3d12.h>
#include "d3dx12.h"

ComputeShadaCreate::ComputeShadaCreate() {

}
ComputeShadaCreate::~ComputeShadaCreate() {

}
void ComputeShadaCreate::CreateBuffer(ID3D12Device* device, const int aligndescsize, D3D12_RESOURCE_STATES r_startstate, ID3D12Resource** buffer) {
	D3D12_HEAP_PROPERTIES heapprop = {};
	heapprop.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;//リソースを書き込み可能に
	heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;//1は書き込み出来なくなる用
	heapprop.CreationNodeMask = 1;
	heapprop.VisibleNodeMask = 1;

	HRESULT result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(heapprop),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(aligndescsize, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, 0),
		r_startstate,//D3D12_RESOURCE_STATE_COMMON
		nullptr,
		IID_PPV_ARGS(buffer)
	);
	if (result != S_OK) {
		throw(1);
	}
}