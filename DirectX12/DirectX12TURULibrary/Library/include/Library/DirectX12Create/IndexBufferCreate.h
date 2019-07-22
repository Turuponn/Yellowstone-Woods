#pragma once

struct ID3D12Device;
struct ID3D12Resource;

class IndexBufferCreate {
public:
	IndexBufferCreate();
	virtual ~IndexBufferCreate();
	/// <summary>
	///�C���f�b�N�X�o�b�t�@���쐬���� 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="allindexsize">�S�C���f�b�N�X�T�C�Y������ �C���f�b�N�X�� �C���f�b�N�X�J�E���g</param>
	/// <param name="oneindexsize">1�C���f�b�N�X�̃T�C�Y sizeof�œ����</param>
	/// <param name="buffer">[out]</param>
	void CreateIndexBuffer(ID3D12Device* device, const int allindexsize, const int oneindexsize, ID3D12Resource** buffer);
};
