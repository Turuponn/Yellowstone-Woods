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
	/// �C���f�b�N�X�r���[���쐬����
	/// </summary>
	/// <param name="indexbuffer"></param>
	/// <param name="allindexsize">�S�C���f�b�N�X�� (�S�C���f�b�N�X��*1�C���f�b�N�X������̃T�C�Y)</param>
	/// <param name="oneindexsize">1�C���f�b�N�X�̃T�C�Y</param>
	/// <param name="vartexnum">���_��</param>
	/// <param name="indexbufferview">[out] �C���f�b�N�X�o�b�t�@�r���[��Ԃ�</param>
	void CreateIndexView(ID3D12Resource* indexbuffer, const UINT allindexsize, const size_t oneindexsize, const UINT vartexnum, D3D12_INDEX_BUFFER_VIEW** indexbufferview);
	/// <summary>
	/// �C���f�b�N�X�r���[�����: R16
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
	/// �C���f�b�N�X�r���[�����: R32
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
