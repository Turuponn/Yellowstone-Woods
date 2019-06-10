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
	/// ニアとファー更新
	/// </summary>
	/// <param name="newnearnum">　近い </param>
	/// <param name="newfar">　遠い</param>
	void SetNearFar(const float newnearnum, const float newfar);


	/// <summary>
	/// カメラの回転
	/// </summary>
	void CameraRotate(float x, float y, float z, float camx, float camy, float camz, float camerarenge);



	/// プロジェクション行列を返す
	DirectX::XMMATRIX& GetCameraProje();
	/// ビュー行列を返す
	DirectX::XMMATRIX& GetCameraView();
	/// 視線ベクトルを返す
	DirectX::XMVECTOR& GetEyeVec();
	/// カメラの視野角を返す
	float GetfieldOfView();
	/// アスペクト比を返す
	float GetAspect();
	/// カメラの座標を返します
	Vector3 GetCameraPosition();
	/// カメラの座標を更新します
	void SetCameraPostion(float x, float y, float z);
	/// カメラが向いている向き　を返します。
	Vector3 GetCameraLookAt();

private:
	DirectX::XMMATRIX _cameraview;//カメラ行列
	DirectX::XMMATRIX _projection;//射影行列
	

	std::shared_ptr<Geometori> _ziometori;
	
	DirectX::XMVECTOR _target;//注視点
	DirectX::XMVECTOR _eye;//視線ベクトル
	DirectX::XMVECTOR _inveye;//逆視線ベクトル
	DirectX::XMVECTOR _upper_vec;//上方向を指すベクトル
	float _fieldOfView;//視野角
	float _aspect;//アスペ比

	
};