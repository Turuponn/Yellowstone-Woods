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
	/// ��`�^��UI���쐬���܂�
	/// </summary>
	void CreateUIRect(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		const std::string& filepath
	);
	/// <summary>
	/// ��`�^��UI��`�悵�܂�
	/// </summary>
	void DrawRect(
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<Camera>& camera,
		std::shared_ptr<WhiteTextureManager>& whitetexM
	);
	/// <summary>
	/// ���W���X�V���܂�
	/// </summary>
	/// <param name="newpos"></param>
	void SetPos(const Vector3& newpos);
	/// <summary>
	/// �g�k�����X�V���܂�
	/// </summary>
	/// <param name="newscale"></param>
	void SetScale(const Vector3& newscale);
private:
	int _handle;
	std::shared_ptr<Canvas> _canvas;//UI�p�̃L�����o�X

};