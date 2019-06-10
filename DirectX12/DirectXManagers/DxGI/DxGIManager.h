#pragma once


#include <wrl.h>

struct IDXGIFactory4;

class DxGIManager {
public:

	DxGIManager();
	virtual ~DxGIManager();
	void CreateDxGiFactory();

	Microsoft::WRL::ComPtr<IDXGIFactory4>& GetDxGIFac();

private:
	Microsoft::WRL::ComPtr<IDXGIFactory4> _dxgifac4;
};