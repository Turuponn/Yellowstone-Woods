#include "D3D12DeviceManager.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "Library\GameError.h"
#include "constance.h"
#include "DirectXManagers\DxGI\DxGIManager.h"

D3D12DeviceManager::D3D12DeviceManager() {

}
D3D12DeviceManager::~D3D12DeviceManager() {
}

void D3D12DeviceManager::CreateD3DDevice(std::shared_ptr<DxGIManager>& dxgi) {
	std::vector<IDXGIAdapter*> adapters;
	IDXGIAdapter* adapter = nullptr;
	//GPUで実行する予定の場合EnumAdaptersを使用するデバイスを作成する
	//ソフトウェアの場合 CreateSoftwareAdapter　を使用する
	//今回はGPUデバイスのみ
	for (int i = 0; dxgi->GetDxGIFac()->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		adapters.push_back(adapter);
		
	}
	

	//この中から NVIDIA を探す
	for (auto adpt : adapters) {
		adapter = adpt;//一番最初のグラフィックボードを使用します。
		break;
	}

	D3D12DeviceCreate::CreateDevice(&_device, adapter);
	for (auto ptr : adapters) {
		SAFE_RELEASE(ptr);
	}
	
}

Microsoft::WRL::ComPtr<ID3D12Device>& D3D12DeviceManager::GetDevice() {
	return _device;
}
