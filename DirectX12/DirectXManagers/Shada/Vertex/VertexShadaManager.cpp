#include "VertexShadaManager.h"
#include <d3d12.h>
#include "Library\GameError.h"
#include "constance.h"
#include "Library\DirectX12Create\ShadaCreate.h"
#include "Library\DirectX12Create\String.h"


VertexShadaManager::VertexShadaManager() {

}
VertexShadaManager::~VertexShadaManager() {

}
void VertexShadaManager::CreateVertexShada(wchar_t* filename,char* funcname) {
	std::shared_ptr<ShadaCreate> sc(new ShadaCreate());
	_shadacreate = sc;
	_shadacreate->CreateVertexShada(filename, funcname, &_vertexshada);
}
void VertexShadaManager::CreateVertexShada(const std::string& filename, const std::string& funcname) {
	std::shared_ptr<ShadaCreate> sc(new ShadaCreate());
	_shadacreate = sc;
	wchar_t* newname = new wchar_t[StringtoWString(filename).size()];
	int index = 0;
	for (auto n : StringtoWString(filename)) {
		newname[index] = n;
		index = index + 1;
	}
	TCHAR* name = newname;
	printf("\n");
	printf("%ls\n", newname);
	char* newnaem2 = new char[StringtoWString(funcname).size()];
	int index2 = 0;
	for (auto n : funcname) {
		newnaem2[index2] = n;
		index2++;
	}

	_shadacreate->CreateVertexShada(name, newnaem2, &_vertexshada);
}
Microsoft::WRL::ComPtr<ID3D10Blob> VertexShadaManager::GetVertexShada() {
	return _vertexshada;
}