#pragma once

struct ID3D12Device;
struct ID3D12Resource;

class IndexBufferCreate {
public:
	IndexBufferCreate();
	virtual ~IndexBufferCreate();
	/// <summary>
	///インデックスバッファを作成する 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="allindexsize">全インデックスサイズを入れる インデックス数 インデックスカウント</param>
	/// <param name="oneindexsize">1インデックスのサイズ sizeofで入れる</param>
	/// <param name="buffer">[out]</param>
	void CreateIndexBuffer(ID3D12Device* device, const int allindexsize, const int oneindexsize, ID3D12Resource** buffer);
};
