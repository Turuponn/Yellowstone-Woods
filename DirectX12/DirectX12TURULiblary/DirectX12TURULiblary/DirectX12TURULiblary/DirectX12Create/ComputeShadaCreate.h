#pragma once

struct ID3D12Device;
enum D3D12_RESOURCE_STATES;
struct ID3D12Resource;

class ComputeShadaCreate {
public:
	ComputeShadaCreate();
	virtual ~ComputeShadaCreate();
	/// <summary>
	/// UAV: �o�b�t�@�̍쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="aligndescsize">�A���C�����ꂽ�o�b�t�@(256)�̃T�C�Y</param>
	/// <param name="r_startstate">���\�[�X�ŏ��̏��</param>
	/// <param name="buffer">[out]�쐬���ꂽ�o�b�t�@��Ԃ��܂�</param>
	void CreateBuffer(ID3D12Device* device, const int aligndescsize, D3D12_RESOURCE_STATES r_startstate, ID3D12Resource** buffer);


private:

};