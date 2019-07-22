#include "D3D12DeviceCreate.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "GameError.h"


D3D12DeviceCreate::D3D12DeviceCreate() {

}
D3D12DeviceCreate::~D3D12DeviceCreate() {

}

void D3D12DeviceCreate::CreateDevice(ID3D12Device** device, IDXGIAdapter* adapter) {


	//使用可能フューチャーレベル
	D3D_FEATURE_LEVEL levelTable[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};


	HRESULT result = E_FAIL;
	int counter = 0;//フューチャーレベルがあったかどうか
	D3D_FEATURE_LEVEL scsessLevel;
	//使用可能な最高フューチャーレベルを探す
	for (auto lev : levelTable) {
		//デバイスの作成
		result = D3D12CreateDevice(
			adapter,
			lev,
			IID_PPV_ARGS(device)
		);
		if (result == S_OK) {
			scsessLevel = lev;
			counter = 1;
			break;
		}

	}


	


	//デバッグのみフューチャーレベルを見せる
#ifdef _DEBUG
	switch (scsessLevel) {
	case D3D_FEATURE_LEVEL_12_1:
		printf("USE_FEATURE_LEVEL_12_1");
		break;
	case D3D_FEATURE_LEVEL_12_0:
		printf("USE_FEATURE_LEVEL_12_0");
		break;
	case D3D_FEATURE_LEVEL_11_1:
		printf("USE_FEATURE_LEVEL_11_1");
		break;
	case D3D_FEATURE_LEVEL_11_0:
		printf("USE_FEATURE_LEVEL_11_0");
		break;
	default:
		break;
	}
#endif


	//使用可能なフューチャーレベルがなかったら、落とす処理
	if (counter <= 0) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("フューチャーレベル　このPCでは使えません")));
	}
}