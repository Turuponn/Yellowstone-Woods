#pragma once


typedef wchar_t TCHAR;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;


class ShadaCreate {
public:
	ShadaCreate();
	virtual ~ShadaCreate();
	/// <summary>
	/// ���_�V�F�[�_�쐬
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="vertexfuncname"></param>
	/// <param name="newvertexshadar">[out]</param>
	void CreateVertexShada(TCHAR* filename, char* vertexfuncname, ID3DBlob** newvertexshadar);
	/// <summary>
	/// �s�N�Z���V�F�[�_�쐬
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="pixelfuncname"></param>
	/// <param name="newpixelshader">[out]</param>
	void CreatePixelShada(TCHAR* filename, char* pixelfuncname, ID3DBlob** newpixelshader);
	/// <summary>
	/// �R���s���[�g�V�F�[�_�쐬
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="funcname"></param>
	/// <param name="shadaresoce">[out]</param>
	void CreateComputeShada(TCHAR* filename, char* funcname, ID3DBlob** shadaresoce);
	/// <summary>
	/// �W�I���g���V�F�[�_�쐬
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="funcname"></param>
	/// <param name="shadaresoce">[out]</param>
	void CreateGeometryShada(TCHAR* filename, char* funcname, ID3DBlob** shadaresoce);

private:
	ID3DBlob* _error;
};