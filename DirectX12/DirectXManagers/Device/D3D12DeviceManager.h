#pragma once

#include "Library\DirectX12Create\D3D12DeviceCreate.h"
#include <vector>
#include <memory>
#include <wrl.h>


class DxGIManager;

class D3D12DeviceManager : public D3D12DeviceCreate {
public:
	D3D12DeviceManager();
	~D3D12DeviceManager();
	void CreateD3DDevice(std::shared_ptr<DxGIManager>& dxgi);
	Microsoft::WRL::ComPtr<ID3D12Device>& GetDevice();
private:
	Microsoft::WRL::ComPtr<ID3D12Device> _device;
};
