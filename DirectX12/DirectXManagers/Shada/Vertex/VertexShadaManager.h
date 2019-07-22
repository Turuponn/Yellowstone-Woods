#pragma once

#include <memory>
#include <string>
#include <wrl.h>

class ShadaCreate;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

class VertexShadaManager {
public:
	VertexShadaManager();
	~VertexShadaManager();
	void CreateVertexShada(wchar_t* filename, char* funcname);
	Microsoft::WRL::ComPtr<ID3DBlob>& GetVertexShada();
	void CreateVertexShada(const std::string& filename, const std::string& funcname);
private:
	std::shared_ptr<ShadaCreate> _shadacreate;
	Microsoft::WRL::ComPtr<ID3DBlob> _vertexshada;
};
