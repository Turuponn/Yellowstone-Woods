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
	/// コンスタントバッファビューを作成します
	/// </summary>
	/// <param name="device"></param>
	/// <param name="descriptorcount"></param>
	/// <param name="align">1ヒープ255アライン済み</param>
	/// <param name="constantbuffer"></param>
	/// <param name="constantdescheap"></param>
	void CreateConstantBufferView(ID3D12Device* device, const int descriptorcount, const UINT64 align, ID3D12Resource* constantbuffer, ID3D12DescriptorHeap* constantdescheap);
};