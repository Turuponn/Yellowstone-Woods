#pragma once

#include "Loder\FBX\FBXLoader.h"
#include <string>
#include <memory>
#include "Geometori.h"


class D3D12DeviceManager;
class ComandManager;

class PipelineStateManager;
class VertexShadaManager;
class PixcelShadaManager;
class RootSignatureManager;
class FenceManager;
class ConstantManager;
struct D3D12_INPUT_ELEMENT_DESC;
enum TEXTURE_REGISTER;
class DeferredRenderManager;
class RenderTargetManager;
class DepthManager;
class WhiteTextureManager;

struct FBX_DRAW {
	std::shared_ptr<D3D12DeviceManager> device;
	std::shared_ptr<ComandManager> comand;
	std::shared_ptr<RootSignatureManager> rootsignature;

	FBX_DRAW() {}
	FBX_DRAW(
		std::shared_ptr<D3D12DeviceManager>& d,
		std::shared_ptr<ComandManager>& c,
		std::shared_ptr<RootSignatureManager>& r
	) :
		device(d),
		comand(c),
		rootsignature(r)
	{}
};
struct FBX_DRAW_ANIM {
	bool animationF;
	int animationFrame;
	std::string animname;
	FBX_DRAW_ANIM(){}
	FBX_DRAW_ANIM(
		bool af,
		int frame,
		std::string name
	) :
		animationF(af),
		animationFrame(frame),
	    animname(name)
	{}
};






class TextureManager;

class FBXManager : public FBXLoader {
private:
	//�萔����GPU�֑���
	void UploadConstant(std::shared_ptr<ComandManager>& comand, const int meshidx, const int materialidx, DR_MAT* address);
	void CbuffCreate(std::shared_ptr<D3D12DeviceManager>& device);
	/// ���f����`�悵�܂�
	void DeferredRender(
		FBX_DRAW& fbxdraw,
		TEXTURE_REGISTER texture_register,
		std::shared_ptr<WhiteTextureManager>& whitetexM,
		bool texF
	);
	


public:
	FBXManager();
	~FBXManager();

	/// <summary>
	/// �ʏ탍�[�h + DeferredRendar
	/// </summary>
	/// <param name="fbxdraw"></param>
	/// <param name="fence"></param>
	/// <param name="filepath"></param>
	/// <param name=""></param>
	void LoadModelDR(
		FBX_DRAW& fbxdraw,
		std::shared_ptr<FenceManager>& fence,
		const std::string& filepath,
		bool animationF
	);
	/// <summary>
	/// ���f����`�悵�܂�
	/// </summary>
	/// <param name="fbxdraw"></param>
	void DrawModelDR(FBX_DRAW& fbxdraw, TEXTURE_REGISTER texture_register, std::shared_ptr<WhiteTextureManager>& whitetexM, bool texF);

	
	/// <summary>
	/// ���f������]���� : �N�E�H�[�^�j�I��
	/// </summary>
	/// <param name="axis"> ��]��</param>
	/// <param name="angle"> ��]�p</param>
	void SetRotateQuaternion(const Vector3& axis,float angle);
	/// <summary>
	/// ���݂̎p�������]������
	/// </summary>
	/// <param name="axis"> ���݂̎�*�V������</param>
	/// <param name="angle"> �������ꂽ�C�ӎ�����̉�]</param>
	void SetRotateQuaternion_mul(const Vector3& axis, float angle);
	/// <summary>
	/// ���݂̎p���ƐV�����p�������ʐ��`��Ԃ���
	/// </summary>
	/// <param name="t">��Ԑ���W��</param>
	void SetRotateQuaternion_Slerp(const DirectX::XMVECTOR& oldvec, const DirectX::XMVECTOR& newvector, float t);
	/// /// <summary>
	/// ��]�����_�̕��s�ړ�
	/// </summary>
	/// <param name="origin"></param>
	void SetRotateQuaternionOrigin(const Vector3& origin);
	/// <summary>
	/// ��]����
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotateQuaternion_Euler(const Vector3& rotation);
	/// <summary>
	/// ��]�s��->�N�E�H�[�^�j�I��
	/// </summary>
	/// <param name="rotatemat"></param>
	void SetRotateQuaternion_Matrix(DirectX::XMMATRIX rotatemat);
	/// <summary>
	/// ��]�x�N�g�����쐬�����ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	DirectX::XMVECTOR CreateRotateQuaternion(const Vector3& axis, float angle);
	void SetPostionQuaternion(const Vector3& pos);
	DirectX::XMMATRIX GetWorldMatinv();
	/// <summary>
	/// �A�j���[�V�����̍ő�FrameTime��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	int GetAnimFrameEndPos(const std::string& animname);
	/// <summary>
	/// ��]�x�N�g����Ԃ�
	/// </summary>
	/// <returns></returns>
	DirectX::XMVECTOR GetRotateQuaternion();
	/// <summary>
	/// ���f�����g�k���� :�N�E�H�[�^�j�I��
	/// </summary>
	/// <param name="scale"></param>
	void SetScaleQuaternion(const Vector3& scale);
	/// <summary>
	/// �A�j���[�V�������Đ����܂�
	/// </summary>
	/// <param name="animname">�Đ�����A�j���[�V�����̖��O</param>
	/// <param name="frametime">�Đ�����A�j���[�V�����̃t���[��</param>
	void AnimationPlay(const std::string& animname, const int frametime);
	/// <summary>
	/// �A�j���[�V�����̍Đ����I�����A�����̃|�[�Y�ɂ��܂�
	/// </summary>
	void AnimationEND();
private:
	std::shared_ptr<PipelineStateManager> _psm;


	//��]: �N�E�H�[�^�j�I��
	DirectX::XMVECTOR _rotationAxis;
	//���s�ړ�: �N�E�H�[�^�j�I��
	DirectX::XMVECTOR _translation;
	//�g�k : �N�E�H�[�^�j�I��
	DirectX::XMVECTOR _scaling;
	//��]�����_���s�ړ��p
	DirectX::XMVECTOR _origin;
	std::shared_ptr<ConstantManager> _cb;
	std::shared_ptr<ConstantManager> _cbbone;
	DR_MAT* _cbuffAddress;
	JOINTBONE* _cbuffAddressSkinning;
	//�A�j���[�V��������p
	FBX_DRAW_ANIM _animinfo;
	
};