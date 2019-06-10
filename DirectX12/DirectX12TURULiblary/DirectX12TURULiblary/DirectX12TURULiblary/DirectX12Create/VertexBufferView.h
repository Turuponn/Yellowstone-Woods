#pragma once


struct ID3D12Resource;
struct D3D12_VERTEX_BUFFER_VIEW;
typedef unsigned int        UINT;
typedef unsigned __int64    size_t;

class VertexBufferView {
public:
	VertexBufferView();
	virtual ~VertexBufferView();
	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	/// <param name="vertexbuffer"></param>
	/// <param name="allvertexsize">すべての頂点の大きさを入れる　頂点数*一頂点数あたりのサイズ</param>
	/// <param name="onevertexsize">一頂点サイズを入れる</param>
	/// <param name="vertexbuffview">[out]  頂点バッファビューを返す</param>
	void CreateVertexBufferView(ID3D12Resource* vertexbuffer, const UINT allvertexsize, const size_t onevertexsize, D3D12_VERTEX_BUFFER_VIEW** vertexbuffview);

};
