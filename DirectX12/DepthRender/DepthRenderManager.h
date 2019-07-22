#pragma once

#include <memory>

class D3D12DeviceManager;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class RootSignatureManager;
class ComandManager;
class FenceManager;


class DepthRenderManager {
private:
	void CreateBufferHeap(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateBufferView(std::shared_ptr<D3D12DeviceManager>& device);
public:
	DepthRenderManager();
	~DepthRenderManager();

	void DepthRenderInit(std::shared_ptr<D3D12DeviceManager>& device);

	void DepthRenderPre(std::shared_ptr<ComandManager>& comand);
	void DepthRenderPost(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);

private:
    ID3D12DescriptorHeap*		dh_buffer_;	//シャドウマップ用深度バッファ用デスクリプタヒープ
	ID3D12DescriptorHeap*		dh_texture_;	//シャドウマップ用深度テクスチャ用デスクリプタヒープ
	ID3D12Resource*				d_buffer_;


};