#pragma once

struct ID3D12Device;
struct ID3D12Resource;


class VertexBufferCreate {
public:

	VertexBufferCreate();
	virtual ~VertexBufferCreate();
	/// <summary>
	/// 頂点バッファを作成する
	/// </summary>
	/// <param name="device"></param>
	/// <param name="buffersize">全体の頂点バッファサイズ</param>
	/// <param name="buffer">[out]</param>
	void CreateBuffer(ID3D12Device* device, const int buffersize, ID3D12Resource** buffer);

};
