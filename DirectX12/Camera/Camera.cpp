#include "Camera.h"
#include "constance.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\comand\ComandManager.h"

using namespace DirectX;


Camera::Camera(){
	_target = { 0,0,0 };
	_eye = { 100,100,100 };//視線ベクトル
	_upper_vec = { 0,1,0 };
	_aspect = 0.0f;
	_fieldOfView = 0.0f;
}

Camera::~Camera() {

}

void Camera::CreateCamera(std::shared_ptr<D3D12DeviceManager>& device){
	CameraManager::CreateConstantBuffer(device);
	CAMERA_MATRIX initmat;


	_fieldOfView = DirectX::XM_PIDIV4;
	_aspect = static_cast<float>(SCREEN_SIZE_X) / static_cast<float>(SCREEN_SIZE_Y);

	//初期行列作成
	_cameraview = DirectX::XMMatrixLookAtLH(_eye, _target, _upper_vec);
	_projection = DirectX::XMMatrixPerspectiveFovLH(_fieldOfView, _aspect, 0.1f, 5000.0f);
	initmat.camera_view = _cameraview;
	initmat.camera_proje = _projection;
	initmat.camera_viewproje = DirectX::XMMatrixMultiply(_cameraview, _projection);
	initmat.camera_proje_inv = DirectX::XMMatrixInverse(nullptr, _projection);
	initmat.camera_view_inv = DirectX::XMMatrixInverse(nullptr, _cameraview);
	initmat.camera_viewproje_inv = DirectX::XMMatrixInverse(nullptr,DirectX::XMMatrixMultiply(_cameraview, _projection));
	initmat.camera_view_trans = DirectX::XMMatrixTranspose(_cameraview);
	initmat.camera_proje_trans = DirectX::XMMatrixTranspose(_projection);
	initmat.camera_viewproje_trans = DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(_cameraview, _projection));
	DirectX::XMStoreFloat3(&initmat.camera_postion, _eye);
	DirectX::XMStoreFloat3(&initmat.camera_target, _target);
	DirectX::XMStoreFloat3(&initmat.camera_upvec, _upper_vec);


	CameraManager::SetMatrix(initmat);
	
}
CAMERA_MATRIX Camera::UpdateConstance() {
	CAMERA_MATRIX cameramat = {};
	cameramat.camera_view = _cameraview;
	cameramat.camera_proje = _projection;
	cameramat.camera_viewproje = DirectX::XMMatrixMultiply(_cameraview, _projection);
	cameramat.camera_proje_inv = DirectX::XMMatrixInverse(nullptr, _projection);
	cameramat.camera_view_inv = DirectX::XMMatrixInverse(nullptr, _cameraview);
	cameramat.camera_viewproje_inv = DirectX::XMMatrixInverse(nullptr,DirectX::XMMatrixMultiply(_cameraview, _projection));
	cameramat.camera_view_trans = DirectX::XMMatrixTranspose(_cameraview);
	cameramat.camera_proje_trans = DirectX::XMMatrixTranspose(_projection);
	cameramat.camera_viewproje_trans = DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(_cameraview, _projection));
	DirectX::XMStoreFloat3(&cameramat.camera_postion, _eye);
	DirectX::XMStoreFloat3(&cameramat.camera_target, _target);
	DirectX::XMStoreFloat3(&cameramat.camera_upvec, _upper_vec);
	return cameramat;
}
void Camera::Update(std::shared_ptr<ComandManager>& comand) {
	
	Input();
	CameraManager::SetMatrix(UpdateConstance());
	CameraManager::Update(comand, ROOT_PARAM_CONSTANT_CAMERA);

}
void Camera::Input() {
	_projection = DirectX::XMMatrixPerspectiveFovLH(_fieldOfView, _aspect, 0.1f, 10000.0f);
	_cameraview = DirectX::XMMatrixLookAtLH(
		_eye, _target, _upper_vec
	);
}
void Camera::SetNearFar(const float newnearnum, const float newfar) {
	_projection = DirectX::XMMatrixPerspectiveFovLH(_fieldOfView, _aspect, newnearnum, newfar);
}
void Camera::CameraRotate(float x, float y, float z,float camx,float camy,float camz,float camerarenge) {


	//常にTargetを見るeye
	DirectX::XMVECTOR p = { x,y,z };
	_target = p;
	//_eye = (_target + (_eye - _target));



  DirectX::XMFLOAT3 e = {};
  DirectX::XMFLOAT3 t = {};
  XMStoreFloat3(&e,_eye);
  XMStoreFloat3(&t, _target);
  float renge = camerarenge;
  if (camerarenge == 0.0) {
	  renge = 0.5f;
  }
   
   XMVECTOR t2 = {
	renge*cos(camy)- renge*sin(camy),
	  t.y,
	renge*sin(camy)+ renge*cos(camy)
   };
   _eye = _target+t2;

}

DirectX::XMMATRIX& Camera::GetCameraProje() {
	return _projection;
}
DirectX::XMMATRIX& Camera::GetCameraView() {
	return _cameraview;
}
DirectX::XMVECTOR& Camera::GetEyeVec() {
	return _eye;
}
float Camera::GetfieldOfView() {
	return _fieldOfView;
	
}
float Camera::GetAspect() {
	return _aspect;
}
Vector3 Camera::GetCameraLookAt() {
	auto vec = _target - _eye;//視線ベクトル
	XMFLOAT3 v = {};
	XMStoreFloat3(&v, vec);
	return Vector3(v.x, v.y, v.z);
}
Vector3 Camera::GetCameraPosition() {
	DirectX::XMFLOAT3 e = {};
	XMStoreFloat3(&e, _eye);
	return Vector3(e.x,e.y,e.z);
}
void Camera::SetCameraPostion(float x, float y, float z) {
	DirectX::XMVECTOR p = { x,y,z };
	_target = p;
	_eye = (_target + (_eye - _target));
}