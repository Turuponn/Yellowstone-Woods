#include "D3D11On12DeviceManager.h"
#include <d3d11on12.h>
#include "DirectXManagers/comand/ComandManager.h"
#include "DirectXManagers/Device/D3D12DeviceManager.h"
using namespace Microsoft::WRL;

D3D11On12DeviceManager::D3D11On12DeviceManager() {

}
D3D11On12DeviceManager::~D3D11On12DeviceManager() {

}
void D3D11On12DeviceManager::Create11On12Device(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand) {
	//2015�N�ȑO��Dx11�̂悤��D3D12CreateDevice ���� �ݒ�ł��Ă������A
	//���ꂩ���11device����o�R���Ďg�p����K�v������B
	UINT d3d11DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if _DEBUG
	// �f�o�b�O���C���[�g�p
	d3d11DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	
	if (!(SUCCEEDED(D3D11On12CreateDevice(
		device->GetDevice(),
		d3d11DeviceFlags,
		nullptr,
		0,
		reinterpret_cast<IUnknown**>(comand->GetComandQueue().GetAddressOf()),
		1,
		0,
		&_d3d11Device,
		&_d3d11DeviceContext,
		nullptr
	)))) {
		throw(1);
	}

	_d3d11Device.As(&_d3d11On12Device);
}
Microsoft::WRL::ComPtr<ID3D11On12Device>& D3D11On12DeviceManager::GetD3D11on12Device() {
	return _d3d11On12Device;
}
Microsoft::WRL::ComPtr<ID3D11DeviceContext>& D3D11On12DeviceManager::GetD3D11DeviceContext() {
	return _d3d11DeviceContext;
}



