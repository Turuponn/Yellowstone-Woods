#pragma once

struct ID3D12Device;
struct ID3D12Resource;

class ConstanceBufferCreate {
public:
	ConstanceBufferCreate();
	virtual ~ConstanceBufferCreate();
	/// <summary>
	/// コンスタントバッファを作成する
	/// </summary>
	/// <param name="device"></param>
	/// <param name="aligndescsize">定数のinputのサイズを255にアラインしたもの*descriptor数でバッファを作成するためそれを入れる</param>
	/// <param name="constantbuffer">[out]定数バッファを返す</param>
	void CreateConstanceBuffer(ID3D12Device* device,const int aligndescsize, ID3D12Resource** constantbuffer);

};
