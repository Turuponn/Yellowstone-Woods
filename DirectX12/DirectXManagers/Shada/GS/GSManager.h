#pragma once

#include <memory>
#include <string>
#include <wrl.h>

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;


class GSManager {
public:

	GSManager();
	virtual ~GSManager();


	/// <summary>
	/// �W�I���g���V�F�[�_�쐬
	/// </summary>
	/// <param name="filename">�p�X</param>
	/// <param name="funcname">���\�b�h��</param>
	void CreateShada(wchar_t* filename, char* funcname);
	
	/// <summary>
	/// gs�p�ɃR���p�C���ς݂̃p�C�v���C���pBlob��Ԃ�
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3DBlob>& GetBlob();

private:
	Microsoft::WRL::ComPtr<ID3DBlob> _gs;
};
