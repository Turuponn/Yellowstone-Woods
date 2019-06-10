#pragma once

#include "Geometori.h"
#include <memory>

class ConstantManager;
class D3D12DeviceManager;
class ComandManager;
enum ROOT_PARAM_TYPE;

struct CAMERA_MATRIX {
	DirectX::XMMATRIX camera_viewproje;
	DirectX::XMMATRIX camera_view;
	DirectX::XMMATRIX camera_proje;
	DirectX::XMMATRIX camera_viewproje_inv; //逆行列
	DirectX::XMMATRIX camera_view_inv;
	DirectX::XMMATRIX camera_proje_inv;
	DirectX::XMMATRIX camera_viewproje_trans; //転置行列
	DirectX::XMMATRIX camera_proje_trans;
	DirectX::XMMATRIX camera_view_trans;
	DirectX::XMFLOAT3 camera_postion;
	DirectX::XMFLOAT3 camera_target;
	DirectX::XMFLOAT3 camera_upvec;
};

class CameraManager {
protected:
	CameraManager();
	virtual ~CameraManager();

	/// <summary>
	/// カメラ用定数を作成する
	/// </summary>
	/// <param name="device"></param>
	void CreateConstantBuffer(std::shared_ptr<D3D12DeviceManager>& device);
	/// <summary>
	/// 新しい行列を入れる
	/// </summary>
	/// <param name="newmat"></param>
	void SetMatrix(CAMERA_MATRIX& newmat);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="type"> 使うスロットを入れる</param>
	void Update(std::shared_ptr<ComandManager>& comand, ROOT_PARAM_TYPE type);
	
private:
	CAMERA_MATRIX* _camAddress;
	std::shared_ptr<ConstantManager> _constantManager;
};