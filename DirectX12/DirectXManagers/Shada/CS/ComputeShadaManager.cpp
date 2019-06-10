#include "ComputeShadaManager.h"
#include "Library\DirectX12Create\ShadaCreate.h"
#include <d3d12.h>
#include "Library\DirectX12Create\ResoceMapUnmap.h"
#include "Library\DirectX12Create\ComputeShadaCreate.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "d3dx12.h"



ComputeShadaManager::ComputeShadaManager() {

}
ComputeShadaManager::~ComputeShadaManager() {

}
void ComputeShadaManager::CreateShada(wchar_t* filename, char* funcname) {
	std::shared_ptr<ShadaCreate> sc(new ShadaCreate());
	sc->CreateComputeShada(filename, funcname, &_cs);
}
void ComputeShadaManager::CreateUAVBuffer(std::shared_ptr<D3D12DeviceManager>& device,size_t onesize,int datasize) {
	std::shared_ptr<ComputeShadaCreate> csc(new ComputeShadaCreate());
	auto _agin = ((onesize + 0xff) & ~0xff);//structBufferと合わせる
	int buffsize = (int)(_agin * datasize);




	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.CreationNodeMask = 1;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	prop.Type = D3D12_HEAP_TYPE_CUSTOM;
	prop.VisibleNodeMask = 1;

	//サイズは定数バッファと同じように指定
	D3D12_RESOURCE_DESC desc{};
	desc.Alignment = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	desc.Format = DXGI_FORMAT_UNKNOWN;
	desc.Height = 1;
	desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1, 0 };
	desc.Width = (onesize * datasize + 0xff)&~0xff;

	auto hr = device->GetDevice()->CreateCommittedResource(
		&prop, D3D12_HEAP_FLAG_NONE, &desc,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS, nullptr,
		IID_PPV_ARGS(&_csbuffer));


	//csc->CreateBuffer(device->GetDevice(), buffsize, D3D12_RESOURCE_STATE_COMMON, &_csbuffer);
}
void ComputeShadaManager::CreateUAVheap(std::shared_ptr<D3D12DeviceManager>& device) {
	D3D12_DESCRIPTOR_HEAP_DESC uavHeapDesc = {};
	uavHeapDesc.NumDescriptors = 1;
	uavHeapDesc.NodeMask = 0;
	uavHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//uav用
	uavHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	device->GetDevice()->CreateDescriptorHeap(&uavHeapDesc, IID_PPV_ARGS(&_uavDescHeap));
}
void ComputeShadaManager::bufferMap(void* address) {
	//Rengeが0,0だとCPUからのアクセスができなくなる
	_rmap->Buffer_Map_Renge(address, _csbuffer.Get());

}

void ComputeShadaManager::bufferUnMap() {
	_rmap->Buffer_Unmap(_csbuffer.Get());
}
void ComputeShadaManager::CreateUAView(std::shared_ptr<D3D12DeviceManager>& device,int datasize,size_t stride) {
	//ビュー作成
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;//構造化バッファー・ビューではUNKNOWNを設定しないといけない
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.NumElements = datasize;
	uavDesc.Buffer.StructureByteStride = static_cast<UINT>(stride);//0以外だと構造化バッファとして扱われる
	device->GetDevice()->CreateUnorderedAccessView(_csbuffer.Get(), nullptr, &uavDesc, _uavDescHeap.Get()->GetCPUDescriptorHandleForHeapStart());

}
void ComputeShadaManager::Initialize() {
	std::shared_ptr<ResoceMapUnmap> rmU(new ResoceMapUnmap());
	std::shared_ptr<TextureManager> texm(new TextureManager());
	_rmap = rmU;
	_texm = texm;
}
void ComputeShadaManager::CreateSRVHeap(std::shared_ptr<D3D12DeviceManager>& device) {
	_texm->SRVCreateHeap(device,1);
}
void ComputeShadaManager::CreateSRView(std::shared_ptr<D3D12DeviceManager>& device) {
	//_texm->SRVCreateView(device,);
}
void ComputeShadaManager::CreateSRVBuffer() {

}
void ComputeShadaManager::StartResoce(std::shared_ptr<ComandManager>& comand) {
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_UNORDERED_ACCESS, _csbuffer.Get());
}
void ComputeShadaManager::EndResoce(std::shared_ptr<ComandManager>& comand) {
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ, _csbuffer.Get());
}
Microsoft::WRL::ComPtr<ID3DBlob>& ComputeShadaManager::GetCSShada() {
	return _cs;
}
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& ComputeShadaManager::GetUAVHeap() {
	return _uavDescHeap;
}
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& ComputeShadaManager::GetSRVHeap() {
	return _srvDescHeap;
}
Microsoft::WRL::ComPtr<ID3D12Resource>& ComputeShadaManager::GetUAVBuffer() {
	return _csbuffer;
}