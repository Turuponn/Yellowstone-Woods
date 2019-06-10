#pragma once

#include <wrl.h>
#include <memory>
#include <string>

class ShadaCreate;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

class VertexShadaManager {
public:
	VertexShadaManager();
	virtual ~VertexShadaManager();
	void CreateVertexShada(wchar_t* filename, char* funcname);
	Microsoft::WRL::ComPtr<ID3DBlob> GetVertexShada();
	void CreateVertexShada(const std::string& filename, const std::string& funcname);
private:
	std::shared_ptr<ShadaCreate> _shadacreate;
	Microsoft::WRL::ComPtr<ID3DBlob> _vertexshada;
};
