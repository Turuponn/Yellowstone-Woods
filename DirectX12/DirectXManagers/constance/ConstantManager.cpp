#include "ConstantManager.h"
#include <d3d12.h>
#include "constance.h"
#include "Library\GameError.h"
#include "Library\DirectX12Create\ConstanceBufferCreate.h"
#include "Library\DirectX12Create\ConstantBufferViewCreate.h"
#include "Library\DirectX12Create\ResoceMapUnmap.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include <vector>

ConstantManager::ConstantManager() {
	_agin = 0;
	_desc_count = 0;
}
ConstantManager::~ConstantManager() {
	
}
void ConstantManager::CreateConstantBufferAndView(std::shared_ptr<D3D12DeviceManager>& device,const size_t& cbufferlayoutstructsize,const int numdesccout) {
	std::shared_ptr<ResoceMapUnmap> rmU(new ResoceMapUnmap());
	_resocemapunmap = rmU;
	CreateHeapDesc(device, numdesccout);
	CreateBuffer(device, cbufferlayoutstructsize);
	CreateViewDesc(device);
}

void ConstantManager::CreateHeapDesc(std::shared_ptr<D3D12DeviceManager>& device, const int numdesccout) {
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC _descriptorHeapdesc = {};
	_descriptorHeapdesc.NumDescriptors = numdesccout;
	_descriptorHeapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	_descriptorHeapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;	
	result = device->GetDevice()->CreateDescriptorHeap(&_descriptorHeapdesc, IID_PPV_ARGS(&_descHeap));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR,_T("CreateHeapDesc  result != S_OK")));
	}
	_desc_count = numdesccout;
}
void ConstantManager::CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const size_t& cbufferlayoutstructsize) {
	std::shared_ptr<ConstanceBufferCreate> cb(new ConstanceBufferCreate());
	_agin = ((cbufferlayoutstructsize + 0xff) & ~0xff);
	int buffsize = (int)(_agin * _desc_count);
	cb->CreateConstanceBuffer(device->GetDevice(), buffsize, &_cbuffer);
}

void ConstantManager::CreateViewDesc(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<ConstantBufferViewCreate> cbv(new ConstantBufferViewCreate());
	cbv->CreateConstantBufferView(device->GetDevice(), _desc_count, _agin, _cbuffer.Get(), _descHeap.Get());
}

void ConstantManager::ConstantbufferMap(void* address) {
	_resocemapunmap->Buffer_Map(address, _cbuffer.Get());
}
void ConstantManager::ConstantbufferUnMap() {
	_resocemapunmap->Buffer_Unmap(_cbuffer.Get());
}
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& ConstantManager::GetDescHeap() {
	return _descHeap;
}