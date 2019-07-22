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
	//定数情報をGPUへ送る
	void UploadConstant(std::shared_ptr<ComandManager>& comand, const int meshidx, const int materialidx, DR_MAT* address);
	void CbuffCreate(std::shared_ptr<D3D12DeviceManager>& device);
	/// モデルを描画します
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
	/// 通常ロード + DeferredRendar
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
	/// モデルを描画します
	/// </summary>
	/// <param name="fbxdraw"></param>
	void DrawModelDR(FBX_DRAW& fbxdraw, TEXTURE_REGISTER texture_register, std::shared_ptr<WhiteTextureManager>& whitetexM, bool texF);

	
	/// <summary>
	/// モデルを回転する : クウォータニオン
	/// </summary>
	/// <param name="axis"> 回転軸</param>
	/// <param name="angle"> 回転角</param>
	void SetRotateQuaternion(const Vector3& axis,float angle);
	/// <summary>
	/// 現在の姿勢から回転させる
	/// </summary>
	/// <param name="axis"> 現在の軸*新しい軸</param>
	/// <param name="angle"> 合成された任意軸周りの回転</param>
	void SetRotateQuaternion_mul(const Vector3& axis, float angle);
	/// <summary>
	/// 現在の姿勢と新しい姿勢を球面線形補間する
	/// </summary>
	/// <param name="t">補間制御係数</param>
	void SetRotateQuaternion_Slerp(const DirectX::XMVECTOR& oldvec, const DirectX::XMVECTOR& newvector, float t);
	/// /// <summary>
	/// 回転軸原点の平行移動
	/// </summary>
	/// <param name="origin"></param>
	void SetRotateQuaternionOrigin(const Vector3& origin);
	/// <summary>
	/// 回転入力
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotateQuaternion_Euler(const Vector3& rotation);
	/// <summary>
	/// 回転行列->クウォータニオン
	/// </summary>
	/// <param name="rotatemat"></param>
	void SetRotateQuaternion_Matrix(DirectX::XMMATRIX rotatemat);
	/// <summary>
	/// 回転ベクトルを作成し結果を返す
	/// </summary>
	/// <returns></returns>
	DirectX::XMVECTOR CreateRotateQuaternion(const Vector3& axis, float angle);
	void SetPostionQuaternion(const Vector3& pos);
	DirectX::XMMATRIX GetWorldMatinv();
	/// <summary>
	/// アニメーションの最大FrameTimeを返します
	/// </summary>
	/// <returns></returns>
	int GetAnimFrameEndPos(const std::string& animname);
	/// <summary>
	/// 回転ベクトルを返す
	/// </summary>
	/// <returns></returns>
	DirectX::XMVECTOR GetRotateQuaternion();
	/// <summary>
	/// モデルを拡縮する :クウォータニオン
	/// </summary>
	/// <param name="scale"></param>
	void SetScaleQuaternion(const Vector3& scale);
	/// <summary>
	/// アニメーションを再生します
	/// </summary>
	/// <param name="animname">再生するアニメーションの名前</param>
	/// <param name="frametime">再生するアニメーションのフレーム</param>
	void AnimationPlay(const std::string& animname, const int frametime);
	/// <summary>
	/// アニメーションの再生を終了し、初期のポーズにします
	/// </summary>
	void AnimationEND();
private:
	std::shared_ptr<PipelineStateManager> _psm;


	//回転: クウォータニオン
	DirectX::XMVECTOR _rotationAxis;
	//平行移動: クウォータニオン
	DirectX::XMVECTOR _translation;
	//拡縮 : クウォータニオン
	DirectX::XMVECTOR _scaling;
	//回転軸原点平行移動用
	DirectX::XMVECTOR _origin;
	std::shared_ptr<ConstantManager> _cb;
	std::shared_ptr<ConstantManager> _cbbone;
	DR_MAT* _cbuffAddress;
	JOINTBONE* _cbuffAddressSkinning;
	//アニメーション制御用
	FBX_DRAW_ANIM _animinfo;
	
};