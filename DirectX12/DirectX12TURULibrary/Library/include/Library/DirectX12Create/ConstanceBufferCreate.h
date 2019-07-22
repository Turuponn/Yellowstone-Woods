#pragma once

struct ID3D12Device;
struct ID3D12Resource;

class ConstanceBufferCreate {
public:
	ConstanceBufferCreate();
	virtual ~ConstanceBufferCreate();
	/// <summary>
	/// �R���X�^���g�o�b�t�@���쐬����
	/// </summary>
	/// <param name="device"></param>
	/// <param name="aligndescsize">�萔��input�̃T�C�Y��255�ɃA���C����������*descriptor���Ńo�b�t�@���쐬���邽�߂��������</param>
	/// <param name="constantbuffer">[out]�萔�o�b�t�@��Ԃ�</param>
	void CreateConstanceBuffer(ID3D12Device* device,const int aligndescsize, ID3D12Resource** constantbuffer);

};
