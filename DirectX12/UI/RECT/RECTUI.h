#pragma once
#include "Geometori.h"
#include <vector>
#include <string>
#include <memory>

class GameEngine;
class Canvas;
class D3D12DeviceManager;
class RootSignatureManager;
class ComandManager;
class Camera;
class WhiteTextureManager;


class RECTUI {
public:
	RECTUI();
	virtual ~RECTUI();

	/// <summary>
	/// 矩形型のUIを作成します
	/// </summary>
	void CreateUIRect(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		const std::string& filepath
	);
	/// <summary>
	/// 矩形型のUIを描画します
	/// </summary>
	void DrawRect(
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<Camera>& camera,
		std::shared_ptr<WhiteTextureManager>& whitetexM
	);
	/// <summary>
	/// 座標を更新します
	/// </summary>
	/// <param name="newpos"></param>
	void SetPos(const Vector3& newpos);
	/// <summary>
	/// 拡縮率を更新します
	/// </summary>
	/// <param name="newscale"></param>
	void SetScale(const Vector3& newscale);
	/// <summary>
	/// 回転原点
	/// </summary>
	/// <param name="newrotateorigin"></param>
	void SetRotateOrigin(const Vector3& newrotateorigin);
	/// <summary>
	/// 色を指定します
	/// </summary>
	/// <param name="newcolor"></param>
	void SetColor(const Vector4& newcolor);
	/// <summary>
	/// 回転率を更新します
	/// </summary>
	/// <param name="newrotate"></param>
	void SetRotate(const float newrotate);
	

private:
	int _handle;
	std::shared_ptr<Canvas> _canvas;//UI用のキャンバス

};