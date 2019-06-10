#include "D3D12DeviceManager.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "Library\GameError.h"
#include "constance.h"
#include "DirectXManagers\DxGI\DxGIManager.h"

D3D12DeviceManager::D3D12DeviceManager() {
	_device = nullptr;
}
D3D12DeviceManager::~D3D12DeviceManager() {
	SAFE_RELEASE(_device);
}

void D3D12DeviceManager::CreateD3DDevice(std::shared_ptr<DxGIManager>& dxgi) {
	std::vector<IDXGIAdapter*> adapters;
	IDXGIAdapter* adapter = nullptr;
	for (int i = 0; dxgi->GetDxGIFac()->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		adapters.push_back(adapter);
		//‚±‚Ì’†‚©‚ç NVIDIA ‚ð’T‚·
		for (auto adpt : adapters) {
			DXGI_ADAPTER_DESC adesc = {};
			adpt->GetDesc(&adesc);
			std::wstring strDesc = adesc.Description;
		}

	}

	D3D12DeviceCreate::CreateDevice(&_device, adapter);
}

ID3D12Device*& D3D12DeviceManager::GetDevice() {
	return _device;
}
