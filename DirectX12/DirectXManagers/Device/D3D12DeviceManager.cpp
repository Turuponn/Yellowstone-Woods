#include "D3D12DeviceManager.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "Library\GameError.h"
#include "constance.h"
#include "DirectXManagers\DxGI\DxGIManager.h"

D3D12DeviceManager::D3D12DeviceManager() {

}
D3D12DeviceManager::~D3D12DeviceManager() {
}

void D3D12DeviceManager::CreateD3DDevice(std::shared_ptr<DxGIManager>& dxgi) {
	std::vector<IDXGIAdapter*> adapters;
	IDXGIAdapter* adapter = nullptr;
	//GPU�Ŏ��s����\��̏ꍇEnumAdapters���g�p����f�o�C�X���쐬����
	//�\�t�g�E�F�A�̏ꍇ CreateSoftwareAdapter�@���g�p����
	//�����GPU�f�o�C�X�̂�
	for (int i = 0; dxgi->GetDxGIFac()->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		adapters.push_back(adapter);
		
	}
	

	//���̒����� NVIDIA ��T��
	for (auto adpt : adapters) {
		adapter = adpt;//��ԍŏ��̃O���t�B�b�N�{�[�h���g�p���܂��B
		break;
	}

	D3D12DeviceCreate::CreateDevice(&_device, adapter);
	for (auto ptr : adapters) {
		SAFE_RELEASE(ptr);
	}
	
}

Microsoft::WRL::ComPtr<ID3D12Device>& D3D12DeviceManager::GetDevice() {
	return _device;
}
