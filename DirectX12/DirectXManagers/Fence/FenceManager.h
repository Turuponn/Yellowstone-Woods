#pragma once


#include <memory>
#include <wrl.h>

class FenceCreate;
struct ID3D12Fence;
class D3D12DeviceManager;

class FenceManager {
public:
	FenceManager();
	~FenceManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device);
	Microsoft::WRL::ComPtr <ID3D12Fence>& GetFence();

private:
	std::shared_ptr<FenceCreate> _fencecreate;
	Microsoft::WRL::ComPtr<ID3D12Fence> _fence;
};