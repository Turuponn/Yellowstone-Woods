#pragma once

#include <memory>
#include "Geometori.h"

//���C�g�p�萔
struct LIGHT_MAT {
	DirectX::XMMATRIX light_world;
	DirectX::XMMATRIX lighe_scalemat;
	DirectX::XMMATRIX lightview;
	DirectX::XMMATRIX lightproje;
	DirectX::XMFLOAT4 lightdir;//�f�B���N�V���i�����C�g���i���C�g�̕����j x y z w
	float lightIntensity;//�f�B���N�V���i�����C�g���i���C�g�̖��邳�j x
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

	//���s�����𐶐�
	void DirectionalLightCreate(std::shared_ptr<D3D12DeviceManager> device, std::shared_ptr<RootSignatureManager>& rootsignature);

	//�X�V
	void Update(std::shared_ptr<ComandManager>& comand);

	//���C�g:����������
	void SetLightPos(const Vector3& lightdir);
	//���C�g:���C�g�̋���������
	void SetLightIntensity(const float& intensity);

private:
	std::shared_ptr<ConstantManager> _constantmanager;
	LIGHT_MAT* _constantAddress;//�萔�o�b�t�@�ɊԐړI�ɃA�N�Z�X����̂ɕK�v

	DirectX::XMMATRIX _lightcameraview;//���C�g�̌��Ă���͈́i�J�����s��
	DirectX::XMMATRIX _projection;//�ˉe�s��
	DirectX::XMVECTOR _eye;//�����x�N�g��

	DirectX::XMMATRIX m_mClipToUV;//���C�g�r���[���ɂ���_�̍��W��UV���W�Ƃ��ē��邽�߂̕ϊ��s��
};
