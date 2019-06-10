#pragma once

struct ID3D12Device;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;

class DepthCreate {
public:
	DepthCreate();
	virtual ~DepthCreate();

	
	/// <summary>
	/// �[�x�o�b�t�@�쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="screensize_x">��ʕ�</param>
	/// <param name="screensize_y">��ʏc</param>
	/// <param name="depthbuffer">[out]</param>
	void CreateDepthBuffer(ID3D12Device* device, const unsigned int screensize_x, const unsigned int screensize_y, ID3D12Resource** depthbuffer);
	/// <summary>
	/// �[�x�o�b�t�@�r���[�쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="depthbuffer"></param>
	/// <param name="depthheapedesc"></param>
	void CreateDepthBufferView(ID3D12Device* device, ID3D12Resource* depthbuffer, ID3D12DescriptorHeap* depthheapedesc);
	/// <summary>
	/// �[�x�p�f�B�X�N���v�^�q�[�v�쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="depthheapedesc">[out] �[�x�p�ɐݒ肵��DescriptorHeap���쐬���ĕԂ�</param>
	void CreateDepthDescHeap(ID3D12Device* device, ID3D12DescriptorHeap** depthheapedesc);
};
