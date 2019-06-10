#pragma once


#include <memory>

class FenceCreate;
struct ID3D12Fence;
class D3D12DeviceManager;

class FenceManager {
public:
	FenceManager();
	virtual ~FenceManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device);
	ID3D12Fence*& GetFence();

private:
	std::shared_ptr<FenceCreate> _fencecreate;
	ID3D12Fence* _fence;
};