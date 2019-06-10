#pragma once

#include "Camera\Manager\CameraManager.h"
#include "Geometori.h"

class ComandManager;

class Camera : public CameraManager {
private:
	void Input();
	CAMERA_MATRIX UpdateConstance();
public:
	Camera();
	virtual ~Camera();


	void CreateCamera(std::shared_ptr<D3D12DeviceManager>& device);
	

	void Update(std::shared_ptr<ComandManager>& comand);

	/// <summary>
	/// �j�A�ƃt�@�[�X�V
	/// </summary>
	/// <param name="newnearnum">�@�߂� </param>
	/// <param name="newfar">�@����</param>
	void SetNearFar(const float newnearnum, const float newfar);


	/// <summary>
	/// �J�����̉�]
	/// </summary>
	void CameraRotate(float x, float y, float z, float camx, float camy, float camz, float camerarenge);



	/// �v���W�F�N�V�����s���Ԃ�
	DirectX::XMMATRIX& GetCameraProje();
	/// �r���[�s���Ԃ�
	DirectX::XMMATRIX& GetCameraView();
	/// �����x�N�g����Ԃ�
	DirectX::XMVECTOR& GetEyeVec();
	/// �J�����̎���p��Ԃ�
	float GetfieldOfView();
	/// �A�X�y�N�g���Ԃ�
	float GetAspect();
	/// �J�����̍��W��Ԃ��܂�
	Vector3 GetCameraPosition();
	/// �J�����̍��W���X�V���܂�
	void SetCameraPostion(float x, float y, float z);
	/// �J�����������Ă�������@��Ԃ��܂��B
	Vector3 GetCameraLookAt();

private:
	DirectX::XMMATRIX _cameraview;//�J�����s��
	DirectX::XMMATRIX _projection;//�ˉe�s��
	

	std::shared_ptr<Geometori> _ziometori;
	
	DirectX::XMVECTOR _target;//�����_
	DirectX::XMVECTOR _eye;//�����x�N�g��
	DirectX::XMVECTOR _inveye;//�t�����x�N�g��
	DirectX::XMVECTOR _upper_vec;//��������w���x�N�g��
	float _fieldOfView;//����p
	float _aspect;//�A�X�y��

	
};