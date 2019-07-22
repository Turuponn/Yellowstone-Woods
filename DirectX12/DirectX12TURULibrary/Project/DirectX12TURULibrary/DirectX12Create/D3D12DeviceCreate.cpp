#include "D3D12DeviceCreate.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "GameError.h"


D3D12DeviceCreate::D3D12DeviceCreate() {

}
D3D12DeviceCreate::~D3D12DeviceCreate() {

}

void D3D12DeviceCreate::CreateDevice(ID3D12Device** device, IDXGIAdapter* adapter) {


	//�g�p�\�t���[�`���[���x��
	D3D_FEATURE_LEVEL levelTable[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};


	HRESULT result = E_FAIL;
	int counter = 0;//�t���[�`���[���x�������������ǂ���
	D3D_FEATURE_LEVEL scsessLevel;
	//�g�p�\�ȍō��t���[�`���[���x����T��
	for (auto lev : levelTable) {
		//�f�o�C�X�̍쐬
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


	


	//�f�o�b�O�̂݃t���[�`���[���x����������
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


	//�g�p�\�ȃt���[�`���[���x�����Ȃ�������A���Ƃ�����
	if (counter <= 0) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("�t���[�`���[���x���@����PC�ł͎g���܂���")));
	}
}