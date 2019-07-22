#include "DirectionalLightManager.h"
#include "DirectXManagers\constance\ConstantManager.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include <d3d12.h>
#include "constance.h"
#include "DirectXManagers\comand\ComandManager.h"



using namespace DirectX;

DirectionalLightManager::DirectionalLightManager() {
	_constantAddress = nullptr;



	m_mClipToUV = DirectX::XMMatrixIdentity();
	m_mClipToUV.r[0].m128_f32[0] = 0.5;
	m_mClipToUV.r[1].m128_f32[1] = -0.5;
	m_mClipToUV.r[2].m128_f32[2] = 1;
	m_mClipToUV.r[3].m128_f32[0] = 0.5;
	m_mClipToUV.r[3].m128_f32[1] = 0.5;
	m_mClipToUV.r[3].m128_f32[3] = 1;

}
DirectionalLightManager::~DirectionalLightManager() {

}

void DirectionalLightManager::DirectionalLightCreate(std::shared_ptr<D3D12DeviceManager> device, std::shared_ptr<RootSignatureManager>& rootsignature) {
	//平行光源を定義
	std::shared_ptr<ConstantManager> cb(new ConstantManager());
	cb->CreateConstantBufferAndView(device,sizeof(LIGHT_MAT), rootsignature->GetRengeType()[ROOT_PARAM_CONSTANT_LIGHT].NumDescriptors);
	cb->ConstantbufferMap(&_constantAddress);


	_eye = { 0,20,-40 };//視点ベクトル　左手系
	DirectX::XMVECTOR target = { 0.0f, 1.0f, 0.0f };//ターゲット:焦点
	DirectX::XMVECTOR upper_vec = { 0, 1, 0 };//アッパーベクトル
	_lightcameraview = DirectX::XMMatrixLookAtLH(_eye, target, upper_vec);
	
	



	//平行光源: ライトの設定
	_constantAddress->lightview = _lightcameraview;
	_constantAddress->lightproje = _projection;
	_constantAddress->lightdir = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);//初期ライト方向
	_constantAddress->lightIntensity = 1.0f;//ライトの強さ
	_constantAddress->light_world = DirectX::XMMatrixIdentity();
	_constantAddress->lighe_scalemat = DirectX::XMMatrixScaling(1, 1, 1);
	_constantmanager = cb;




	XMFLOAT3 temp = { -1, 1, -1 };
	XMVECTOR lightpos = XMVector3Normalize(XMLoadFloat3(&temp))*XMVector3Length(target - _eye);
	XMStoreFloat3(&_constantAddress->lightpos, lightpos);

	_lightcameraview = DirectX::XMMatrixLookAtLH(lightpos, target, upper_vec);
	DirectX::XMMATRIX lightproj = DirectX::XMMatrixOrthographicLH(
		64,
		64,
		0.1f,
		10000.0f
	);



	_constantAddress->lightproje = lightproj;
	_constantAddress->lightview = _lightcameraview;


	_constantAddress->g_mWLPT = _lightcameraview*lightproj*m_mClipToUV;
	_constantAddress->g_mWLP = _lightcameraview*lightproj;

}

void DirectionalLightManager::Update(std::shared_ptr<ComandManager>& comand) {
	
	





	
	
	
	auto heap = _constantmanager->GetDescHeap();
	comand->GetGraphicsCommandList()->SetDescriptorHeaps(1, &heap);
	comand->GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(ROOT_PARAM_CONSTANT_LIGHT, _constantmanager->GetDescHeap()->GetGPUDescriptorHandleForHeapStart());
}
void DirectionalLightManager::SetLightPos(const Vector3& lightdir){
	_constantAddress->lightdir.x = lightdir.x;
	_constantAddress->lightdir.y = lightdir.y;
	_constantAddress->lightdir.z = lightdir.z;
	_constantAddress->lightdir.w = 0.0f;
}
void DirectionalLightManager::SetLightIntensity(const float& intensity) {
	_constantAddress->lightIntensity = intensity;
}