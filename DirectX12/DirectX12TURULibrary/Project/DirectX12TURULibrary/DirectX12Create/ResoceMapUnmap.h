#pragma once





struct ID3D12Resource;

class ResoceMapUnmap {
public:
	ResoceMapUnmap();
	virtual ~ResoceMapUnmap();
	/// <summary>
	/// ���\�[�X�o�b�t�@���}�b�v����
	/// </summary>
	/// <param name="address">���X�g�f�[�^�ւ̃A�h���X [in]�Q�Ɠn��</param>
	/// <param name="resourcebuffer">�}�b�v����Ώۃo�b�t�@�[</param>
	void Buffer_Map(void* address, ID3D12Resource* resourcebuffer);
	/// <summary>
	/// ���\�[�X�o�b�t�@���A���}�b�v����
	/// </summary>
	/// <param name="resourcebuffer"> �A���}�b�v�������o�b�t�@</param>
	void Buffer_Unmap(ID3D12Resource* resourcebuffer);
	/// <summary>
	/// ���\�[�X�̃������͈͂��L�q��������
	/// </summary>
	/// <param name="address"></param>
	/// <param name="resourcebuffer"></param>
	void Buffer_Map_Renge(void* address, ID3D12Resource* resourcebuffer);

private:
};