#pragma once


#include <memory>
#include <Windows.h>
#include "Geometori.h"
#include <string>

class D3D12DeviceManager;
class Graphics;
class TextureManager;
class ComandManager;

class ImguiManager {
private:
	void ShowGuiLightIntensity();
	void ShowGuiLightDirectionalLightDir();
	void ShowCubeMapMeshScale();
public:
	ImguiManager();
	virtual ~ImguiManager();


	bool Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<Graphics>& graphics,HWND& windowhwnd);

	void DrawimGui(std::shared_ptr<ComandManager>& comand);

	/// <summary>
	/// �������E�B���h�E�̃T�C�Y�ɕύX���������ꍇ���I�ɑΉ����邽�߂̏������s��
	/// </summary>
	void ResetimGuiCheck();
	/// <summary>
	/// ���C�g�̋���p�̐��l������
	/// </summary>
	void AdditemLightIntensity(float& lightintensitynum);

	/// <summary>
	/// ���s�����̌���������
	/// </summary>
	/// <param name="dirpos"></param>
	void AdditemDirLightPos(Vector3& dirpos);
	/// <summary>
	/// �L���[�u�}�b�v�̃T�C�Y��ύX����
	/// </summary>
	/// <param name="newscale"></param>
	void CubeMapMeshScale(Vector3& newscale);
	/// <summary>
	/// ���b�V���̃X�P�[�����O���ڂ𓮓I�ɒǉ�����
	/// </summary>
	/// <param name="newscale"></param>
	/// <param name="text"> �����p���x��</param>
	/// <param name="label_x"> ���ڗp���x��x</param>
	/// <param name="label_y"></param>
	/// <param name="label_z"></param>
	void ShowAddMeshScale(Vector3* newscale, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z,float maxsize);
	void ShowAddMeshVector(Vector3& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize, float minsize);
	void ShowAddMeshFloat(float& newparam, std::string& text, std::string& label, float maxsize, float minsize);

	//�ŏ��̏���
	void PreGui(std::shared_ptr<ComandManager>& comand);
	//�Ō�̏���
	void PostGui(std::shared_ptr<ComandManager>& comand);
private:
	std::shared_ptr<TextureManager> _guitex;

	float* _lightintensitynum;//���C�g�̋���
	Vector3* _lightdirpos;//���s����:
	Vector3* _cubemapscale;//�L���[�u�}�b�v�g�k�l
	unsigned int _heapeIncrementSize;
};