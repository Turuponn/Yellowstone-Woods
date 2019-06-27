#pragma once


#include <vector>
#include <map>
#include <string>
#include <dinput.h>//Inputキーボードのキーコード用
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
class D3D11On12DeviceManager;

class GltfManager;
class D2DManager;


class DeferredShading;
class RECTUI;

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
	/// <summary>
	/// 画像ロード
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	const int LoadImagehandle(const std::string& filepath);
	/// <summary>
	/// BumpMap用image設定
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	const int LoadBumpImagehandle(const std::string& filepath);
	/// <summary>
	/// 画像を描画する
	/// </summary>
	/// <param name="handle"></param>
	void DrawImage(const int handle);
	/// <summary>
	/// カメラ作成
	/// </summary>
	/// <returns> カメラハンドルを返す </returns>
	const int CreateCameraHandle();
	/// <summary>
	/// カメラ更新
	/// </summary>
	/// <param name="handle"> カメラハンドルを入れる </param>
	void UpdateCamera(const int handle);
	//ゲームループ
	void Run();
	//レンダリング
	void Render();
	//バックバッファに切り替え
	void ScreenFilip();
	/// <summary>
	/// キー入力に対応するフラグを返します
	/// </summary>
	/// <param name="keycode">　keycode DIK_〇〇　というキーに対応した定数を入れる</param>
	/// <returns>押された: 1 押されていない : 0</returns>
	const int CheckHitKey(const int keycode);
	//平行光源ライトを更新する
	void DirectionallightUpdate(const int handle);
	//平行光源初期化
	const int DirectionalLightInit();
	//平行光源ライトの情報
	//@param lightdir　ライトの向き
	void DirectionallightPos(const int handle, const Vector3& lightdir);
	//平行光源ライトの強さ
	void DirectionallightIntensity(const int handle,const float lightintensity);
	/// <summary>
	/// FBXをロードします
	/// </summary>
	/// <param name="filepath"></param>
	/// <param name="animationF"></param>
	/// <returns></returns>
	const int LoadFBXModelDR(const std::string& filepath,bool animationF);
	/// <summary>
	/// モデルを描画します
	/// </summary>
	/// <param name="handle"></param>
	void DrawFBXModelDR(const int handle);
	/// <summary>
	/// アニメーションを開始します
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="animname">アニメーションの名前を入れます</param>
	/// <param name="animframe"></param>
	void FBXAnimationPlay(const int handle, const std::string& animname, const int animframe);
	/// <summary>
	/// アニメーションを終了し、初期スタンスポーズに戻します。今後Animationは再生されません
	/// </summary>
	/// <param name="handle"></param>
	void FBXAnimationEND(const int handle);
	//クウォータニオンによるワールド行列を作成します
	/// <summary>
	/// 任意軸回転を行います
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis">軸</param>
	/// <param name="newangle">回転量</param>
	void SetFBXRotateQuaternion(const int handle, const Vector3& newaxis,float newangle);
	/// <summary>
	/// 現在軸と新しい軸を合成します
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis"> 回転軸</param>
	/// <param name="newangle"> 回転量</param>
	void SetFBXRotateQuaternion_mul(const int handle, const Vector3& newaxis, float newangle);
	void SetFBXPostionQuaternion(const int handle, const Vector3& newpos);
	void SetFBXScaleQuaternion(const int handle, const Vector3& newscale);
	DirectX::XMVECTOR GetFBXRotateQuaternion(const int handle);
	void SetFBXRotateQuaternion_Euler(const int handle,const Vector3& newrotate);
	/// <summary>
	/// 球面線形補間したベクトルを作成します
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="oldvec"></param>
	/// <param name="newvec"></param>
	/// <param name="t">0~1.0 0ではoldvecを 1ではnewvecになります</param>
	void SetFBXRotateQuaternion_Slerp(const int handle, const DirectX::XMVECTOR& oldvec, const DirectX::XMVECTOR& newvec, float t);
	DirectX::XMVECTOR CreateFBXRotateQuaternion(const int handle,const Vector3& axis, float angle);
	/// <summary>
	/// 回転行列->クウォータニオン
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newmat"></param>
	void SetFBXRotateQuaternion_Matrix(const int handle,DirectX::XMMATRIX& newmat);
	/// <summary>
	/// 回転軸原点を平行移動させます
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="neworigin"> 原点の平行移動量</param>
	void SetFBXRotateQuaternionOrigin(const int handle, const Vector3& neworigin);
	/// <summary>
	/// 指定したアニメーションの最大フレーム数を返します
	/// </summary>
	/// <param name="handle"></param>
	/// <returns>最大フレーム数</returns>
	int GetAnimFrameEndPos(const int handle,const std::string& animname);
	/// <summary>
	/// CubeMapを作成します
	/// </summary>
	/// <param name="texfilepath"></param>
	/// <param name="fbxfilepath"></param>
	/// <returns></returns>
	const int LoadCubeMap(const std::string& texfilepath, const std::string& fbxfilepath);
	void PreCubeMap(const int handle);
	void SetCubeMapScaleQuaternion(const int handle, const Vector3& newscale);
	void SetCubeMapPostionQuaternion(const int handle, const Vector3& newpos);
	void SetCubeMapRotateQuaternion(const int handle, const Vector3& newaxis, float angle);
	//TODO: ShadowMap
	void DepthRenderInit();
	void DepthRenderPre();
	void DepthRenderPost();
	/// <summary>
	///DeferredRendaring用のパス開始です
	/// </summary>
	void DR_Pre();
	/// <summary>
	/// DeferredRendaring用のパスの終了位置です
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
	/// カメラ回転行列を生成します
	/// </summary>
	/// <param name="camerahandl"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="camx"></param>
	/// <param name="camy"></param>
	/// <param name="camz"></param>
	/// <param name="camerarenge">カメラと焦点の距離</param>
	void SetCameraRotate(const int camerahandl, float x, float y, float z, float camx, float camy, float camz,float camerarenge);
	/// カメラの座標をセットします
	void SetCameraPosition(const int camerahandl,float x, float y, float z);
	/// カメラの座標を返します
	Vector3 GetCameraPosition(const int camerahandl);
	/// カメラの現在向きを返します 
	Vector3 GetCameraLookAt(const int camerahandl);
	/// カメラのビュー行列を返します
	DirectX::XMMATRIX GetCameraViewMat(const int handle);
	/// <summary>
	/// スクリーンの描画を行います
	/// </summary>
	/// <param name="attachcamerahandle"> アタッチするカメラ</param>
	void DrawScreen(const int attachcamerahandle);
	/// <summary>
	/// メルセンヌツイスタを使って乱数を出力します
	/// </summary>
	/// <returns>seedを無視した乱数を返します</returns>
	float GetRand_mt();
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
	/// <summary>
	/// UIをキャンバスに登録します：矩形
	/// </summary>
	/// <param name="texfilepath"> テクスチャのパスを入れる　ない場合 ""して 空テクスチャを指定する</param>
	/// <returns></returns>
	const int CreateRECTUIHandle(const std::string& texfilepath);
	/// <summary>
	/// UIを描画します :　矩形
	/// </summary>
	/// <param name="handle"></param>
	void DrawRECTUI(const int uihandle, const int attachcamerahandle);
	/// <summary>
	/// UI用新しい座標を更新します
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newpos"></param>
	void SetPosUI(const int uihandle,const Vector3& newpos);
	/// <summary>
	/// UI用新しい拡縮率を更新します
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newscale"></param>
	void SetScaleUI(const int uihandle, const Vector3& newscale);


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
	std::map<const int, std::shared_ptr<RECTUI>> _uis;
	std::shared_ptr<DepthRenderManager>  _dmanager;
	std::shared_ptr<GbufferRenderManager> _drM;
	std::shared_ptr<WhiteTextureManager> _whiteTexM;
	std::shared_ptr<PostProsessManager> _pp;
	std::shared_ptr<GPGPUManager> _testgpgpum;
	std::shared_ptr<ImguiManager> _imgui;
	std::shared_ptr<DeferredShading> _ds;
	std::shared_ptr<SwapChainManager> _sc;
};