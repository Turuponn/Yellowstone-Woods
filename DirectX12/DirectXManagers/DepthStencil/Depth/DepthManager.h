#pragma once




#include <memory>
#include <wrl.h>

struct D3D12_DEPTH_STENCIL_VIEW_DESC;
struct ID3D12DescriptorHeap;
class D3D12DeviceManager;
struct ID3D12Resource;
class D3D12DeviceManager;
class DepthCreate;


class DepthManager {
private:

public:
	DepthManager();
	~DepthManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int screensize_x, const int screensize_y);
	void CreateHeap(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateView(std::shared_ptr<D3D12DeviceManager>& device, Microsoft::WRL::ComPtr<ID3D12Resource>& pResoce);
	Microsoft::WRL::ComPtr<ID3D12Resource>& GetDepthBuffer();
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& GetDescriptorHeap();
private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _depthHeapDesc;
	Microsoft::WRL::ComPtr<ID3D12Resource> _depthbuffer;
};



