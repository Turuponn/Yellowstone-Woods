#pragma once

struct ID3D12Device;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
typedef unsigned __int64    UINT64;


class ConstantBufferViewCreate {
public:
	ConstantBufferViewCreate();
	virtual ~ConstantBufferViewCreate();

	/// <summary>
	/// �R���X�^���g�o�b�t�@�r���[���쐬���܂�
	/// </summary>
	/// <param name="device"></param>
	/// <param name="descriptorcount"></param>
	/// <param name="align">1�q�[�v255�A���C���ς�</param>
	/// <param name="constantbuffer"></param>
	/// <param name="constantdescheap"></param>
	void CreateConstantBufferView(ID3D12Device* device, const int descriptorcount, const UINT64 align, ID3D12Resource* constantbuffer, ID3D12DescriptorHeap* constantdescheap);
};