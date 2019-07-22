#pragma once


#include <vector>
#include <map>
#include <string>
#include <dinput.h>//Input�L�[�{�[�h�̃L�[�R�[�h�p
#include <memory>
#include "Geometori.h"

class D3D12DeviceManager;
class FenceManager;
class ComandManager;
class WindowInit;
class Graphics;
class SwapChainManager;

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
//class D3D11On12DeviceManager;

class GltfManager;
//class D2DManager;


class DeferredShading;
class RECTUI;




class GameEngine{
private:
	void CreateCamera(const std::string& cameraname);//�J�����̐V�K�쐬
	void CreateCubeMap(const std::string& cubemapname, const std::string& texfilepath, const std::string& fbxfilepath);//�L���[�u�}�b�v�̐V�K�쐬
	void CreateFBXModel(const std::string& modelname, const std::string& fbxfilepath, bool animationF);
private:
	void SetRootSignature();

private:
	void InputRun();
	void InputInit(WindowInit& windowinstance);
public:
	GameEngine();
	~GameEngine();
	void Initialize(WindowInit& windowinstance);
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
	/// <summary>
	/// �J�����쐬
	/// </summary>
	void CreateCameraHandle(const std::string& cameraname);
	/// <summary>
	/// �J�����X�V
	/// </summary>
	void UpdateCamera(const std::string& cameraname);
	//�Q�[�����[�v
	void Run();
	//�o�b�N�o�b�t�@�ɐ؂�ւ�
	void ScreenFilip();
	/// <summary>
	/// �L�[���͂ɑΉ�����t���O��Ԃ��܂�
	/// </summary>
	/// <param name="keycode">�@keycode DIK_�Z�Z�@�Ƃ����L�[�ɑΉ������萔������</param>
	/// <returns>�����ꂽ: 1 ������Ă��Ȃ� : 0</returns>
	const int CheckHitKey(const int keycode);
	//���s�������C�g���X�V����
	void DirectionallightUpdate(const int handle);
	//���s����������
	const int DirectionalLightInit();
	//���s�������C�g�̏��
	//@param lightdir�@���C�g�̌���
	void DirectionallightPos(const int handle, const Vector3& lightdir);
	//���s�������C�g�̋���
	void DirectionallightIntensity(const int handle,const float lightintensity);
	/// <summary>
	/// FBX�����[�h���܂�
	/// </summary>
	/// <param name="filepath"></param>
	/// <param name="animationF"></param>
	void LoadFBXModelDR(const std::string& modelname,const std::string& filepath,bool animationF);
	/// <summary>
	/// ���f����`�悵�܂�
	/// </summary>
	void DrawFBXModelDR(const std::string& modelname);
	/// <summary>
	/// �A�j���[�V�������J�n���܂�
	/// </summary>
	/// <param name="animname">�A�j���[�V�����̖��O�����܂�</param>
	/// <param name="animframe"></param>
	void FBXAnimationPlay(const std::string& modelname, const std::string& animname, const int animframe);
	/// <summary>
	/// �A�j���[�V�������I�����A�����X�^���X�|�[�Y�ɖ߂��܂��B����Animation�͍Đ�����܂���
	/// </summary>
	/// <param name="handle"></param>
	void FBXAnimationEND(const std::string& modelname);
	//�N�E�H�[�^�j�I���ɂ�郏�[���h�s����쐬���܂�
	/// <summary>
	/// �C�ӎ���]���s���܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis">��</param>
	/// <param name="newangle">��]��</param>
	void SetFBXRotateQuaternion(const std::string& modelname, const Vector3& newaxis,float newangle);
	/// <summary>
	/// ���ݎ��ƐV���������������܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis"> ��]��</param>
	/// <param name="newangle"> ��]��</param>
	void SetFBXRotateQuaternion_mul(const std::string& modelname, const Vector3& newaxis, float newangle);
	void SetFBXPostionQuaternion(const std::string& modelname, const Vector3& newpos);
	void SetFBXScaleQuaternion(const std::string& modelname, const Vector3& newscale);
	DirectX::XMVECTOR GetFBXRotateQuaternion(const std::string& modelname);
	void SetFBXRotateQuaternion_Euler(const std::string& modelname,const Vector3& newrotate);
	/// <summary>
	/// ���ʐ��`��Ԃ����x�N�g�����쐬���܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="oldvec"></param>
	/// <param name="newvec"></param>
	/// <param name="t">0~1.0 0�ł�oldvec�� 1�ł�newvec�ɂȂ�܂�</param>
	void SetFBXRotateQuaternion_Slerp(const std::string& modelname, const DirectX::XMVECTOR& oldvec, const DirectX::XMVECTOR& newvec, float t);
	DirectX::XMVECTOR CreateFBXRotateQuaternion(const std::string& modelname,const Vector3& axis, float angle);
	/// <summary>
	/// ��]�s��->�N�E�H�[�^�j�I��
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newmat"></param>
	void SetFBXRotateQuaternion_Matrix(const std::string& modelname,DirectX::XMMATRIX& newmat);
	/// <summary>
	/// ��]�����_�𕽍s�ړ������܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="neworigin"> ���_�̕��s�ړ���</param>
	void SetFBXRotateQuaternionOrigin(const std::string& modelname, const Vector3& neworigin);
	/// <summary>
	/// �w�肵���A�j���[�V�����̍ő�t���[������Ԃ��܂�
	/// </summary>
	/// <param name="handle"></param>
	/// <returns>�ő�t���[����</returns>
	int GetAnimFrameEndPos(const std::string& modelname,const std::string& animname);
	/// <summary>
	/// CubeMap���쐬���܂�
	/// </summary>
	void LoadCubeMap(const std::string& cubemapname,const std::string& texfilepath, const std::string& fbxfilepath);
	void PreCubeMap(const std::string& cubemapname);
	void SetCubeMapScaleQuaternion(const std::string& cubemapname, const Vector3& newscale);
	void SetCubeMapPostionQuaternion(const std::string& cubemapname, const Vector3& newpos);
	void SetCubeMapRotateQuaternion(const std::string& cubemapname, const Vector3& newaxis, float angle);
	//TODO: ShadowMap
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
	void PreDeferredShadingRender(const std::string& cameraname);
	void PostDeferredShadingRender();
	/// <summary>
	/// PostProsess Pass
	/// </summary>
	void PrePostProsessRender(const std::string& cameraname);
	void PostPostProsessRender();
	/// <summary>
	/// �J�����̉�]�s����쐬���܂�
	/// </summary>
	/// <param name="newpoint">�W�_P���쐬���܂�</param>
	/// <param name="newcamerarotate">�V������]�p�x</param>
	/// <param name="camerarenge">�W�_P����̋���</param>
	void SetCameraRotate(const std::string& cameraname, const Vector3& newpoint, const Vector3& newcamerarotate,const float camerarenge);
	/// �J�����̍��W���Z�b�g���܂�
	void SetCameraPosition(const std::string& cameraname,const Vector3& pos);
	/// �J�����̍��W��Ԃ��܂�
	Vector3 GetCameraPosition(const std::string& cameraname);
	/// �J�����̌��݌�����Ԃ��܂� 
	Vector3 GetCameraLookAt(const std::string& cameraname);
	/// �J�����̃r���[�s���Ԃ��܂�
	DirectX::XMMATRIX GetCameraViewMat(const std::string& cameraname);
	/// <summary>
	/// �X�N���[���̕`����s���܂�
	/// </summary>
	void DrawScreen(const std::string& cameraname);
	/// <summary>
	/// �����Z���k�c�C�X�^���g���ė������o�͂��܂�
	/// </summary>
	/// <returns>seed�𖳎�����������Ԃ��܂�</returns>
	float GetRandMt();
	/// <summary>
	/// �����Z���k�c�C�X�^���g�p���A�͈͎w�肳�ꂽ���̗������o�͂��܂�
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	const float GetRandFloatRengeMt(const float min,const float max);
	/// <summary>
	/// �����Z���k�c�C�X�^���g�p���A�͈͎w�肳�ꂽ���̗������o�͂��܂�
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	const int GetRandIntRengeMt(const int min,const int max);

	//#debug
	void imgui(WindowInit& windowinfo);
	void Drawimgui();
	void imguiAddItemLightIntensity(float& lightintensity);
	void imguiAddItemDirLightPos(Vector3& d_pos);
	void imguiCubeMapScale(Vector3& d_cubemap);
	void imguiAddMeshScale(Vector3* newscale, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize);
	void imguiAddMeshVector3(Vector3& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize,float minsize);
	void imguiAddMeshVector4(Vector4& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, std::string& label_w, float maxsize, float minsize);
	void imguiAddMeshFloat(float& newparam, std::string& text, std::string& label, float maxsize, float minsize);
	void imguiAddMeshInt(int& newparam, std::string& text, std::string& label, int maxsize, int minsize);
	void imguiPre();
	void imguiPost();
	/// <summary>
	/// UI���L�����o�X�ɓo�^���܂��F��`
	/// </summary>
	/// <param name="texfilepath"> �e�N�X�`���̃p�X������@�Ȃ��ꍇ ""���� ��e�N�X�`�����w�肷��</param>
	/// <returns></returns>
	const int CreateRECTUIHandle(const std::string& texfilepath);
	/// <summary>
	/// UI: �`�悵�܂� :�@��`
	/// </summary>
	void DrawRECTUI(const int uihandle, const std::string& cameraname);
	/// <summary>
	/// UI:�V�������W���X�V���܂�
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newpos"></param>
	void SetPosUI(const int uihandle,const Vector3& newpos);
	/// <summary>
	/// UI:�V�����g�k�����X�V���܂�
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newscale"></param>
	void SetScaleUI(const int uihandle, const Vector3& newscale);
	/// <summary>
	/// UI:�V������]���_���X�V���܂�
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newrotateorigin"></param>
	void SetRotateOriginUI(const int uihandle, const Vector3& newrotateorigin);
	/// <summary>
	/// UI:�V�����F��ݒ肵�܂�
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newcolor"></param>
	void SetColorUI(const int uihandle, const Vector4& newcolor);
	/// <summary>
	/// UI:�V������]�����X�V���܂�
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newrotate"></param>
	void SetRotateUI(const int uihandle, const float newrotate);


private:
	std::shared_ptr<Graphics> _graphics;
	std::shared_ptr<D3D12DeviceManager> _device;
	std::shared_ptr<FenceManager> _fencemanager;
	std::shared_ptr<ComandManager> _comand;
	std::shared_ptr<DxGIManager> _dxgimanager;
	std::shared_ptr<Rand> _randpacage;
	std::shared_ptr<FowardLayerManager> _f_ayer;
	std::shared_ptr<DirectInputManager> _directinputmanager;
	std::shared_ptr<DepthRenderManager>  _dmanager;
	std::shared_ptr<GbufferRenderManager> _drM;
	std::shared_ptr<WhiteTextureManager> _whiteTexM;
	std::shared_ptr<PostProsessManager> _pp;
	std::shared_ptr<GPGPUManager> _testgpgpum;
	std::shared_ptr<ImguiManager> _imgui;
	std::shared_ptr<DeferredShading> _ds;
	std::shared_ptr<SwapChainManager> _sc;


	std::map<const int, std::shared_ptr<TextureManager>> _imagedatas;
	std::map<const int, std::shared_ptr<DirectionalLightManager>> _dirlights;
	std::map<std::string, std::shared_ptr<Camera >> _cameras;
	std::map<std::string, std::shared_ptr<FBXManager>> _fbxs;
	std::map<const int, std::shared_ptr<GltfManager>> _gltfs;
	std::map<std::string, std::shared_ptr<CubeMapManager>> _cubemap;
	std::map<const int, std::shared_ptr<RECTUI>> _uis;
};