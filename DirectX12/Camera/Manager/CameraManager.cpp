#include "CameraManager.h"
#include <d3d12.h>
#include "constance.h"
#include "DirectXManagers\constance\ConstantManager.h"
#include "DirectXManagers\comand\ComandManager.h"

CameraManager::CameraManager() {
	_camAddress = nullptr;
}
CameraManager::~CameraManager() {

}
void CameraManager::CreateConstantBuffer(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<ConstantManager> c(new ConstantManager());
	c->CreateConstantBufferAndView(device, sizeof(CAMERA_MATRIX),1);
	c->ConstantbufferMap(&_camAddress);
	_constantManager = c;
}
void CameraManager::SetMatrix(CAMERA_MATRIX& newmat) {
	*_camAddress = newmat;
}
void CameraManager::Update(std::shared_ptr<ComandManager>& comand, ROOT_PARAM_TYPE type) {
	auto heap = _constantManager->GetDescHeap();
	comand->GetGraphicsCommandList()->SetDescriptorHeaps(1, &heap);
	comand->GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(type, _constantManager->GetDescHeap()->GetGPUDescriptorHandleForHeapStart());
}