#pragma once


#include <vector>
#include <map>
#include <string>
#include <dinput.h>//Inputキーボードのキーコード用
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
	void CreateCamera(const std::string& cameraname);//カメラの新規作成
	void CreateCubeMap(const std::string& cubemapname, const std::string& texfilepath, const std::string& fbxfilepath);//キューブマップの新規作成
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
	void CreateCameraHandle(const std::string& cameraname);
	/// <summary>
	/// カメラ更新
	/// </summary>
	void UpdateCamera(const std::string& cameraname);
	//ゲームループ
	void Run();
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
	void LoadFBXModelDR(const std::string& modelname,const std::string& filepath,bool animationF);
	/// <summary>
	/// モデルを描画します
	/// </summary>
	void DrawFBXModelDR(const std::string& modelname);
	/// <summary>
	/// アニメーションを開始します
	/// </summary>
	/// <param name="animname">アニメーションの名前を入れます</param>
	/// <param name="animframe"></param>
	void FBXAnimationPlay(const std::string& modelname, const std::string& animname, const int animframe);
	/// <summary>
	/// アニメーションを終了し、初期スタンスポーズに戻します。今後Animationは再生されません
	/// </summary>
	/// <param name="handle"></param>
	void FBXAnimationEND(const std::string& modelname);
	//クウォータニオンによるワールド行列を作成します
	/// <summary>
	/// 任意軸回転を行います
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis">軸</param>
	/// <param name="newangle">回転量</param>
	void SetFBXRotateQuaternion(const std::string& modelname, const Vector3& newaxis,float newangle);
	/// <summary>
	/// 現在軸と新しい軸を合成します
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newaxis"> 回転軸</param>
	/// <param name="newangle"> 回転量</param>
	void SetFBXRotateQuaternion_mul(const std::string& modelname, const Vector3& newaxis, float newangle);
	void SetFBXPostionQuaternion(const std::string& modelname, const Vector3& newpos);
	void SetFBXScaleQuaternion(const std::string& modelname, const Vector3& newscale);
	DirectX::XMVECTOR GetFBXRotateQuaternion(const std::string& modelname);
	void SetFBXRotateQuaternion_Euler(const std::string& modelname,const Vector3& newrotate);
	/// <summary>
	/// 球面線形補間したベクトルを作成します
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="oldvec"></param>
	/// <param name="newvec"></param>
	/// <param name="t">0~1.0 0ではoldvecを 1ではnewvecになります</param>
	void SetFBXRotateQuaternion_Slerp(const std::string& modelname, const DirectX::XMVECTOR& oldvec, const DirectX::XMVECTOR& newvec, float t);
	DirectX::XMVECTOR CreateFBXRotateQuaternion(const std::string& modelname,const Vector3& axis, float angle);
	/// <summary>
	/// 回転行列->クウォータニオン
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="newmat"></param>
	void SetFBXRotateQuaternion_Matrix(const std::string& modelname,DirectX::XMMATRIX& newmat);
	/// <summary>
	/// 回転軸原点を平行移動させます
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="neworigin"> 原点の平行移動量</param>
	void SetFBXRotateQuaternionOrigin(const std::string& modelname, const Vector3& neworigin);
	/// <summary>
	/// 指定したアニメーションの最大フレーム数を返します
	/// </summary>
	/// <param name="handle"></param>
	/// <returns>最大フレーム数</returns>
	int GetAnimFrameEndPos(const std::string& modelname,const std::string& animname);
	/// <summary>
	/// CubeMapを作成します
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
	void PreDeferredShadingRender(const std::string& cameraname);
	void PostDeferredShadingRender();
	/// <summary>
	/// PostProsess Pass
	/// </summary>
	void PrePostProsessRender(const std::string& cameraname);
	void PostPostProsessRender();
	/// <summary>
	/// カメラの回転行列を作成します
	/// </summary>
	/// <param name="newpoint">集点Pを作成します</param>
	/// <param name="newcamerarotate">新しい回転角度</param>
	/// <param name="camerarenge">集点Pからの距離</param>
	void SetCameraRotate(const std::string& cameraname, const Vector3& newpoint, const Vector3& newcamerarotate,const float camerarenge);
	/// カメラの座標をセットします
	void SetCameraPosition(const std::string& cameraname,const Vector3& pos);
	/// カメラの座標を返します
	Vector3 GetCameraPosition(const std::string& cameraname);
	/// カメラの現在向きを返します 
	Vector3 GetCameraLookAt(const std::string& cameraname);
	/// カメラのビュー行列を返します
	DirectX::XMMATRIX GetCameraViewMat(const std::string& cameraname);
	/// <summary>
	/// スクリーンの描画を行います
	/// </summary>
	void DrawScreen(const std::string& cameraname);
	/// <summary>
	/// メルセンヌツイスタを使って乱数を出力します
	/// </summary>
	/// <returns>seedを無視した乱数を返します</returns>
	float GetRandMt();
	/// <summary>
	/// メルセンヌツイスタを使用し、範囲指定された分の乱数を出力します
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	const float GetRandFloatRengeMt(const float min,const float max);
	/// <summary>
	/// メルセンヌツイスタを使用し、範囲指定された分の乱数を出力します
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
	/// UIをキャンバスに登録します：矩形
	/// </summary>
	/// <param name="texfilepath"> テクスチャのパスを入れる　ない場合 ""して 空テクスチャを指定する</param>
	/// <returns></returns>
	const int CreateRECTUIHandle(const std::string& texfilepath);
	/// <summary>
	/// UI: 描画します :　矩形
	/// </summary>
	void DrawRECTUI(const int uihandle, const std::string& cameraname);
	/// <summary>
	/// UI:新しい座標を更新します
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newpos"></param>
	void SetPosUI(const int uihandle,const Vector3& newpos);
	/// <summary>
	/// UI:新しい拡縮率を更新します
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newscale"></param>
	void SetScaleUI(const int uihandle, const Vector3& newscale);
	/// <summary>
	/// UI:新しい回転原点を更新します
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newrotateorigin"></param>
	void SetRotateOriginUI(const int uihandle, const Vector3& newrotateorigin);
	/// <summary>
	/// UI:新しい色を設定します
	/// </summary>
	/// <param name="uihandle"></param>
	/// <param name="newcolor"></param>
	void SetColorUI(const int uihandle, const Vector4& newcolor);
	/// <summary>
	/// UI:新しい回転率を更新します
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