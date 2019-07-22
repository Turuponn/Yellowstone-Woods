#include "ComputeShadaManager.h"
#include "Library\DirectX12Create\ShadaCreate.h"
#include <d3d12.h>
#include "Library\DirectX12Create\ResoceMapUnmap.h"
#include "Library\DirectX12Create\ComputeShadaCreate.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "d3dx12.h"
#include "constance.h"


ComputeShadaManager::ComputeShadaManager() {

}
ComputeShadaManager::~ComputeShadaManager() {
	SAFE_RELEASE(_cs);
	SAFE_RELEASE(_csbuffer);
	SAFE_RELEASE(_uavDescHeap);
	SAFE_RELEASE(_srvDescHeap);
}
void ComputeShadaManager::CreateShada(wchar_t* filename, char* funcname) {
	std::shared_ptr<ShadaCreate> sc(new ShadaCreate());
	sc->CreateComputeShada(filename, funcname, &_cs);
}
void ComputeShadaManager::CreateUAVBuffer(std::shared_ptr<D3D12DeviceManager>& device,size_t onesize,int datasize) {
	std::shared_ptr<ComputeShadaCreate> csc(new ComputeShadaCreate());
	auto _agin = ((onesize + 0xff) & ~0xff);//structBuffer�ƍ��킹��
	int buffsize = (int)(_agin * datasize);




	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.CreationNodeMask = 1;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	prop.Type = D3D12_HEAP_TYPE_CUSTOM;
	prop.VisibleNodeMask = 1;

	//�T�C�Y�͒萔�o�b�t�@�Ɠ����悤�Ɏw��
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
	uavHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//uav�p
	uavHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	device->GetDevice()->CreateDescriptorHeap(&uavHeapDesc, IID_PPV_ARGS(&_uavDescHeap));
}
void ComputeShadaManager::bufferMap(void* address) {
	//Renge��0,0����CPU����̃A�N�Z�X���ł��Ȃ��Ȃ�
	_rmap->Buffer_Map_Renge(address, _csbuffer);

}

void ComputeShadaManager::bufferUnMap() {
	_rmap->Buffer_Unmap(_csbuffer);
}
void ComputeShadaManager::CreateUAView(std::shared_ptr<D3D12DeviceManager>& device,int datasize,size_t stride) {
	//�r���[�쐬
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;//�\�����o�b�t�@�[�E�r���[�ł�UNKNOWN��ݒ肵�Ȃ��Ƃ����Ȃ�
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.NumElements = datasize;
	uavDesc.Buffer.StructureByteStride = static_cast<UINT>(stride);//0�ȊO���ƍ\�����o�b�t�@�Ƃ��Ĉ�����
	device->GetDevice()->CreateUnorderedAccessView(_csbuffer, nullptr, &uavDesc, _uavDescHeap->GetCPUDescriptorHandleForHeapStart());

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
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_UNORDERED_ACCESS, _csbuffer);
}
void ComputeShadaManager::EndResoce(std::shared_ptr<ComandManager>& comand) {
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ, _csbuffer);
}
ID3DBlob*& ComputeShadaManager::GetCSShada() {
	return _cs;
}
ID3D12DescriptorHeap*& ComputeShadaManager::GetUAVHeap() {
	return _uavDescHeap;
}
ID3D12DescriptorHeap*& ComputeShadaManager::GetSRVHeap() {
	return _srvDescHeap;
}
ID3D12Resource*& ComputeShadaManager::GetUAVBuffer() {
	return _csbuffer;
}