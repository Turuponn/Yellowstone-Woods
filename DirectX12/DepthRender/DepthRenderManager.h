#pragma once

#include <memory>
#include <wrl.h>

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
	virtual ~DepthRenderManager();

	void DepthRenderInit(std::shared_ptr<D3D12DeviceManager>& device);

	void DepthRenderPre(std::shared_ptr<ComandManager>& comand);
	void DepthRenderPost(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);

private:
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		dh_buffer_;	//�V���h�E�}�b�v�p�[�x�o�b�t�@�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		dh_texture_;	//�V���h�E�}�b�v�p�[�x�e�N�X�`���p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12Resource>				d_buffer_;


};