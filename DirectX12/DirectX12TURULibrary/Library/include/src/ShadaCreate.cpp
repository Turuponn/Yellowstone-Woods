#include "ShadaCreate.h"
#include <d3d12.h>
#include "../GameError.h"
#include <dxgi1_4.h>
#include <D3Dcompiler.h>//シェーダ用

ShadaCreate::ShadaCreate() {

}
ShadaCreate::~ShadaCreate() {

}

void ShadaCreate::CreateVertexShada(TCHAR* filename, char* vertexfuncname, ID3DBlob** newvertexshadar) {
	HRESULT result = E_FAIL;
	result = D3DCompileFromFile(
		filename,
		nullptr,//マクロ
		D3D_COMPILE_STANDARD_FILE_INCLUDE,// インクルードを利用する
		vertexfuncname,//シェーダー側の関数名
		"vs_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		newvertexshadar,//出力
		&_error
	);
	if (result != S_OK) {
		if (_error != NULL) {
			OutputDebugStringA((char*)_error->GetBufferPointer());
		}
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("ShadaCreate::CreateVertexShada() result != S_OK")));
	}
}

void ShadaCreate::CreateComputeShada(TCHAR* filename, char* funcname, ID3DBlob** shadaresoce) {
	HRESULT result = E_FAIL;
	result = D3DCompileFromFile(
		filename,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		funcname,
		"cs_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		shadaresoce,
		&_error
	);

	if (result != S_OK) {
		if (_error != NULL) {
			OutputDebugStringA((char*)_error->GetBufferPointer());
		}
		throw(1);
	}
}
void ShadaCreate::CreatePixelShada(TCHAR* filename, char* pixelfuncname, ID3DBlob** newpixelshader) {
	//PS
	HRESULT result = E_FAIL;
	result = D3DCompileFromFile(
		filename,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		pixelfuncname,
		"ps_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		newpixelshader,
		&_error
	);
	if (result != S_OK) {
		if (_error != NULL) {
			OutputDebugStringA((char*)_error->GetBufferPointer());
		}
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("ShadaCreate::CreatePixelShada()  result != S_OK")));
	}
}
void ShadaCreate::CreateGeometryShada(TCHAR* filename, char* funcname, ID3DBlob** shadaresoce) {
	HRESULT result = E_FAIL;
	result = D3DCompileFromFile(
		filename,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		funcname,
		"gs_5_1",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		shadaresoce,
		&_error
	);

	if (result != S_OK) {
		if (_error != NULL) {
			OutputDebugStringA((char*)_error->GetBufferPointer());
		}
		throw(1);
	}
}