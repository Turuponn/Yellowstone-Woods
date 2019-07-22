#pragma once

#include <memory>
#include "Geometori.h"

//ライト用定数
struct LIGHT_MAT {
	DirectX::XMMATRIX light_world;
	DirectX::XMMATRIX lighe_scalemat;
	DirectX::XMMATRIX lightview;
	DirectX::XMMATRIX lightproje;
	DirectX::XMFLOAT4 lightdir;//ディレクショナルライト情報（ライトの方向） x y z w
	float lightIntensity;//ディレクショナルライト情報（ライトの明るさ） x
	DirectX::XMMATRIX g_mWLPT;
	DirectX::XMMATRIX g_mWLP;
	DirectX::XMFLOAT3 lightpos;

};

class ConstantManager;
class D3D12DeviceManager;
class RootSignatureManager;
class ComandManager;


class DirectionalLightManager {
private:

public:
	DirectionalLightManager();
	~DirectionalLightManager();

	//平行光源を生成
	void DirectionalLightCreate(std::shared_ptr<D3D12DeviceManager> device, std::shared_ptr<RootSignatureManager>& rootsignature);

	//更新
	void Update(std::shared_ptr<ComandManager>& comand);

	//ライト:向きを入れる
	void SetLightPos(const Vector3& lightdir);
	//ライト:ライトの強さを入れる
	void SetLightIntensity(const float& intensity);

private:
	std::shared_ptr<ConstantManager> _constantmanager;
	LIGHT_MAT* _constantAddress;//定数バッファに間接的にアクセスするのに必要

	DirectX::XMMATRIX _lightcameraview;//ライトの見ている範囲（カメラ行列
	DirectX::XMMATRIX _projection;//射影行列
	DirectX::XMVECTOR _eye;//視線ベクトル

	DirectX::XMMATRIX m_mClipToUV;//ライトビュー内にある点の座標をUV座標として得るための変換行列
};
