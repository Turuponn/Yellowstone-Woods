#pragma once

#include <memory>
#include <string>
#include <wrl.h>

class ShadaCreate;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

class PixcelShadaManager {
public:
	PixcelShadaManager();
	~PixcelShadaManager();

	//シェーダ作成:ピクセル
	//@param　filename　シェーダファイル名
	//@param funcname　関数名
	void CreatePixelShada(wchar_t* filename, char* funcname);
	Microsoft::WRL::ComPtr<ID3DBlob>& GetPixelShada();

private:
	std::shared_ptr<ShadaCreate> _shadacreate;
	Microsoft::WRL::ComPtr<ID3DBlob> _pixcelshada;
};
