#pragma once

struct ID3D12Device;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;

class DepthCreate {
public:
	DepthCreate();
	virtual ~DepthCreate();

	
	/// <summary>
	/// 深度バッファ作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="screensize_x">画面幅</param>
	/// <param name="screensize_y">画面縦</param>
	/// <param name="depthbuffer">[out]</param>
	void CreateDepthBuffer(ID3D12Device* device, const unsigned int screensize_x, const unsigned int screensize_y, ID3D12Resource** depthbuffer);
	/// <summary>
	/// 深度バッファビュー作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="depthbuffer"></param>
	/// <param name="depthheapedesc"></param>
	void CreateDepthBufferView(ID3D12Device* device, ID3D12Resource* depthbuffer, ID3D12DescriptorHeap* depthheapedesc);
	/// <summary>
	/// 深度用ディスクリプタヒープ作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="depthheapedesc">[out] 深度用に設定したDescriptorHeapを作成して返す</param>
	void CreateDepthDescHeap(ID3D12Device* device, ID3D12DescriptorHeap** depthheapedesc);
};
