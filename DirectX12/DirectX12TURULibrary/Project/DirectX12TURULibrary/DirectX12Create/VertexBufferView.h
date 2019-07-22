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
	/// ���_�o�b�t�@�r���[���쐬����
	/// </summary>
	/// <param name="vertexbuffer"></param>
	/// <param name="allvertexsize">���ׂĂ̒��_�̑傫��������@���_��*�꒸�_��������̃T�C�Y</param>
	/// <param name="onevertexsize">�꒸�_�T�C�Y������</param>
	/// <param name="vertexbuffview">[out]  ���_�o�b�t�@�r���[��Ԃ�</param>
	void CreateVertexBufferView(ID3D12Resource* vertexbuffer, const UINT allvertexsize, const size_t onevertexsize, D3D12_VERTEX_BUFFER_VIEW** vertexbuffview);

};
