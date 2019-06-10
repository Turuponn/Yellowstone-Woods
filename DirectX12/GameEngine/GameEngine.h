#pragma once


#include <vector>
#include <map>
#include <string>
#include <dinput.h>//Input�L�[�{�[�h�̃L�[�R�[�h�p
#include <memory>
#include "Geometori.h"



struct FBX_MATERIAL_HANDLE {
	int basetexHandle;
	int bumptexHandle;
};



class D3D12DeviceManager;
class FenceManager;
class ComandManager;
class WindowInit;
class Graphics;


class TextureManager;
class DirectInputManager;
class Camera;
class FBXManager;
class DxGIManager;
class CubeMapManager;
class Rand;

class DirectionalLightManager;



class DepthRenderManager;
class CubeMapManager;
class ImguiManager;

class GbufferRenderManager;
class WhiteTextureManager;
class FowardLayerManager;
class GPGPUManager;//Test
class PostProsessManager;

class GltfManager;


class DeferredShading;

class GameEngine{
private:
	void SetRootSignature();

private:
	void InputRun();
	void InputInit(WindowInit& windowinstance);
public:
	GameEngine();
	virtual ~GameEngine();
	void Initialize(WindowInit& windowinstance);
	//�摜=====================
	/// <summary>
	/// �摜���[�h
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	const int LoadImagehandle(const std::string& filepath);
	/// <summary>
	/// BumpMap�pimage�ݒ�
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	const int LoadBumpImagehandle(const std::string& filepath);
	/// <summary>
	/// �摜��`�悷��
	/// </summary>
	/// <param name="handle"></param>
	void DrawImage(const int handle);
	//�J����=====================
	/// <summary>
	/// �J�����쐬
	/// </summary>
	/// <returns> �J�����n���h����Ԃ� </returns>
	const int CreateCameraHandle();
	/// <summary>
	/// �J�����X�V
	/// </summary>
	/// <param name="handle"> �J�����n���h�������� </param>
	void UpdateCamera(const int handle);
	//�Q�[�����[�v===============
	//�Q�[�����[�v
	void Run();
	//�����_�����O
	void Render();
	//�o�b�N�o�b�t�@�ɐ؂�ւ�
	void ScreenFilip();
	//���͌n================
	/// <summary>
	/// �L�[���͂ɑΉ�����t���O��Ԃ��܂�
	/// </summary>
	/// <param name="keycode">�@keycode DIK_�Z�Z�@�Ƃ����L�[�ɑΉ������萔������</param>
	/// <returns>�����ꂽ: 1 ������Ă��Ȃ� : 0</returns>
	const int CheckHitKey(const int keycode);
	//���s�������C�g===============
	//���s�������C�g���X�V����
	void DirectionallightUpdate(const int handle);
	//���s����������
	const int DirectionalLightInit();
	//���s�������C�g�̏��
	//@param lightdir�@���C�g�̌���
	void DirectionallightPos(const int handle, const Vector3& lightdir);
	//���s�������C�g�̋���
	void DirectionallightIntensity(const int handle,const float lightintensity);
	//FBX=====================
	const int LoadFBXModelDR(const std::string& filepath,bool animationF);
	/// <summary>
	/// ���f����`�悵�܂�
	/// </summary>
	/// <param name="handle"></param>
	void DrawFBXModelDR(const int handle);
	/// <summary>
	/// �A�j���[�V�������J�n���܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="animname">�A�j���[�V�����̖��O�����܂�</param>
	/// <param name="animframe"></param>
	void FBXAnimationPlay(const int handle, const std::string& animname, const int animframe);
	/// <summary>
	/// �A�j���[�V�������I�����A�����X�^���X�|�[�Y�ɖ߂��܂��B����Animation�͍Đ�����܂���
	/// </summary>
	/// <param name="handle"></param>
	void FBXAnimationEND(const int handle);
	//�N�E�H�[�^�j�I���ɂ�郏�[���h�s����쐬���܂�
	/// <summary>
	/// �C�ӎ���]���s���܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis">��</param>
	/// <param name="newangle">��]��</param>
	void SetFBXRotateQuaternion(const int handle, const Vector3& newaxis,float newangle);
	/// <summary>
	/// ���ݎ��ƐV���������������܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis"> ��]��</param>
	/// <param name="newangle"> ��]��</param>
	void SetFBXRotateQuaternion_mul(const int handle, const Vector3& newaxis, float newangle);
	void SetFBXPostionQuaternion(const int handle, const Vector3& newpos);
	void SetFBXScaleQuaternion(const int handle, const Vector3& newscale);
	DirectX::XMVECTOR GetFBXRotateQuaternion(const int handle);
	void SetFBXRotateQuaternion_Euler(const int handle,const Vector3& newrotate);
	/// <summary>
	/// ���ʐ��`��Ԃ����x�N�g�����쐬���܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="oldvec"></param>
	/// <param name="newvec"></param>
	/// <param name="t">0~1.0 0�ł�oldvec�� 1�ł�newvec�ɂȂ�܂�</param>
	void SetFBXRotateQuaternion_Slerp(const int handle, const DirectX::XMVECTOR& oldvec, const DirectX::XMVECTOR& newvec, float t);
	DirectX::XMVECTOR CreateFBXRotateQuaternion(const int handle,const Vector3& axis, float angle);
	/// <summary>
	/// ��]�s��->�N�E�H�[�^�j�I��
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newmat"></param>
	void SetFBXRotateQuaternion_Matrix(const int handle,DirectX::XMMATRIX& newmat);
	/// <summary>
	/// ��]�����_�𕽍s�ړ������܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="neworigin"> ���_�̕��s�ړ���</param>
	void SetFBXRotateQuaternionOrigin(const int handle, const Vector3& neworigin);
	/// <summary>
	/// �w�肵���A�j���[�V�����̍ő�t���[������Ԃ��܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <returns>�ő�t���[����</returns>
	int GetAnimFrameEndPos(const int handle,const std::string& animname);
	//CubeMap================
	const int LoadCubeMap(const std::string& texfilepath, const std::string& fbxfilepath);
	void PreCubeMap(const int handle);
	void SetCubeMapScaleQuaternion(const int handle, const Vector3& newscale);
	void SetCubeMapPostionQuaternion(const int handle, const Vector3& newpos);
	void SetCubeMapRotateQuaternion(const int handle, const Vector3& newaxis, float angle);
	//ShadowMap==============
	void DepthRenderInit();
	void DepthRenderPre();
	void DepthRenderPost();
	/// <summary>
	///DeferredRendaring�p�̃p�X�J�n�ł�
	/// </summary>
	void DR_Pre();
	/// <summary>
	/// DeferredRendaring�p�̃p�X�̏I���ʒu�ł�
	/// </summary>
	void DR_Post();
	/// <summary>
	/// DeferredShading Pass
	/// </summary>
	/// <param name="attachcamerahandle"></param>
	void PreDeferredShadingRender(int attachcamerahandle);
	void PostDeferredShadingRender();
	/// <summary>
	/// PostProsess Pass
	/// </summary>
	/// <param name="attachcamerahandle"></param>
	void PrePostProsessRender(int attachcamerahandle);
	void PostPostProsessRender();
	/// <summary>
	/// �J������]�s��𐶐����܂�
	/// </summary>
	/// <param name="camerahandl"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="camx"></param>
	/// <param name="camy"></param>
	/// <param name="camz"></param>
	/// <param name="camerarenge">�J�����Əœ_�̋���</param>
	void SetCameraRotate(const int camerahandl, float x, float y, float z, float camx, float camy, float camz,float camerarenge);
	/// �J�����̍��W���Z�b�g���܂�
	void SetCameraPosition(const int camerahandl,float x, float y, float z);
	/// �J�����̍��W��Ԃ��܂�
	Vector3 GetCameraPosition(const int camerahandl);
	/// �J�����̌��݌�����Ԃ��܂� 
	Vector3 GetCameraLookAt(const int camerahandl);
	/// �J�����̃r���[�s���Ԃ��܂�
	DirectX::XMMATRIX GetCameraViewMat(const int handle);
	/// <summary>
	/// �X�N���[���̕`����s���܂�
	/// </summary>
	/// <param name="attachcamerahandle"> �A�^�b�`����J����</param>
	void DrawScreen(int attachcamerahandle);
	//#debug
	void imgui(WindowInit& windowinfo);
	void Drawimgui();
	void imguiAddItemLightIntensity(float& lightintensity);
	void imguiAddItemDirLightPos(Vector3& d_pos);
	void imguiCubeMapScale(Vector3& d_cubemap);
	void imguiAddMeshScale(Vector3* newscale, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize);
	void imguiAddMeshVector(Vector3& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize,float minsize);
	void imguiAddMeshFloat(float& newparam, std::string& text, std::string& label, float maxsize, float minsize);
	void imguiPre();
	void imguiPost();
private:
	std::shared_ptr<Graphics> _graphics;
	std::shared_ptr<D3D12DeviceManager> _device;
	std::shared_ptr<FenceManager> _fencemanager;
	std::shared_ptr<ComandManager> _comand;
	std::shared_ptr<DxGIManager> _dxgimanager;
	std::shared_ptr<Rand> _randpacage;
	std::shared_ptr<FowardLayerManager> _f_ayer;
	std::shared_ptr<DirectInputManager> _directinputmanager;
	std::map<const int, std::shared_ptr<TextureManager>> _imagedatas;
	std::map<const int, std::shared_ptr<DirectionalLightManager>> _dirlights;
	std::map<const int, std::shared_ptr<Camera>> _cameras;
	std::map<const int, std::shared_ptr<FBXManager>> _fbxs;
	std::map<const int, std::shared_ptr<GltfManager>> _gltfs;
	std::map<const int, std::shared_ptr<CubeMapManager>> _cubemap;
	std::shared_ptr<DepthRenderManager>  _dmanager;
	std::shared_ptr<GbufferRenderManager> _drM;
	std::shared_ptr<WhiteTextureManager> _whiteTexM;
	std::shared_ptr<PostProsessManager> _pp;
	std::shared_ptr<GPGPUManager> _testgpgpum;
	std::shared_ptr<ImguiManager> _imgui;
	std::shared_ptr<DeferredShading> _ds;
};