#pragma once

struct D3D12_INDEX_BUFFER_VIEW;
struct ID3D12Resource;
typedef unsigned int        UINT;
typedef unsigned __int64    size_t;



class IndexBufferView {
public:
	IndexBufferView();
	virtual ~IndexBufferView();
	/// <summary>
	/// インデックスビューを作成する
	/// </summary>
	/// <param name="indexbuffer"></param>
	/// <param name="allindexsize">全インデックス数 (全インデックス数*1インデックスあたりのサイズ)</param>
	/// <param name="oneindexsize">1インデックスのサイズ</param>
	/// <param name="vartexnum">頂点数</param>
	/// <param name="indexbufferview">[out] インデックスバッファビューを返す</param>
	void CreateIndexView(ID3D12Resource* indexbuffer, const UINT allindexsize, const size_t oneindexsize, const UINT vartexnum, D3D12_INDEX_BUFFER_VIEW** indexbufferview);
	/// <summary>
	/// インデックスビューを作る: R16
	/// </summary>
	/// <param name="indexbuffer"></param>
	/// <param name="allindexsize"></param>
	/// <param name="oneindexsize"></param>
	/// <param name="vartexnum"></param>
	/// <param name="indexbufferview">[out]</param>
	void CreateIndexViewR16(
		ID3D12Resource* indexbuffer,
		const UINT allindexsize,
		const size_t oneindexsize,
		const UINT vartexnum,
		D3D12_INDEX_BUFFER_VIEW** indexbufferview
	);
	/// <summary>
	/// インデックスビューを作る: R32
	/// </summary>
	/// <param name="indexbuffer"></param>
	/// <param name="allindexsize"></param>
	/// <param name="oneindexsize"></param>
	/// <param name="vartexnum"></param>
	/// <param name="indexbufferview">[out]</param>
	void CreateIndexViewR32(
		ID3D12Resource* indexbuffer,
		const UINT allindexsize,
		const size_t oneindexsize,
		const UINT vartexnum,
		D3D12_INDEX_BUFFER_VIEW** indexbufferview
	);
};
