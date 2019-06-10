#pragma once


typedef wchar_t TCHAR;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;


class ShadaCreate {
public:
	ShadaCreate();
	virtual ~ShadaCreate();
	/// <summary>
	/// 頂点シェーダ作成
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="vertexfuncname"></param>
	/// <param name="newvertexshadar">[out]</param>
	void CreateVertexShada(TCHAR* filename, char* vertexfuncname, ID3DBlob** newvertexshadar);
	/// <summary>
	/// ピクセルシェーダ作成
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="pixelfuncname"></param>
	/// <param name="newpixelshader">[out]</param>
	void CreatePixelShada(TCHAR* filename, char* pixelfuncname, ID3DBlob** newpixelshader);
	/// <summary>
	/// コンピュートシェーダ作成
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="funcname"></param>
	/// <param name="shadaresoce">[out]</param>
	void CreateComputeShada(TCHAR* filename, char* funcname, ID3DBlob** shadaresoce);
	/// <summary>
	/// ジオメトリシェーダ作成
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="funcname"></param>
	/// <param name="shadaresoce">[out]</param>
	void CreateGeometryShada(TCHAR* filename, char* funcname, ID3DBlob** shadaresoce);

private:
	ID3DBlob* _error;
};