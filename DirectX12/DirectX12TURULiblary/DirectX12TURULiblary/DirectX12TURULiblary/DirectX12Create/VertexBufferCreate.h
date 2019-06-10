#pragma once

struct ID3D12Device;
struct ID3D12Resource;


class VertexBufferCreate {
public:

	VertexBufferCreate();
	virtual ~VertexBufferCreate();
	/// <summary>
	/// ���_�o�b�t�@���쐬����
	/// </summary>
	/// <param name="device"></param>
	/// <param name="buffersize">�S�̂̒��_�o�b�t�@�T�C�Y</param>
	/// <param name="buffer">[out]</param>
	void CreateBuffer(ID3D12Device* device, const int buffersize, ID3D12Resource** buffer);

};
