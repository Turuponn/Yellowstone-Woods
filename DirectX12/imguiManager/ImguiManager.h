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
	/// もしもウィンドウのサイズに変更があった場合動的に対応するための処理を行う
	/// </summary>
	void ResetimGuiCheck();
	/// <summary>
	/// ライトの強弱用の数値を入れる
	/// </summary>
	void AdditemLightIntensity(float& lightintensitynum);

	/// <summary>
	/// 平行光源の向きを入れる
	/// </summary>
	/// <param name="dirpos"></param>
	void AdditemDirLightPos(Vector3& dirpos);
	/// <summary>
	/// キューブマップのサイズを変更する
	/// </summary>
	/// <param name="newscale"></param>
	void CubeMapMeshScale(Vector3& newscale);
	/// <summary>
	/// メッシュのスケーリング項目を動的に追加する
	/// </summary>
	/// <param name="newscale"></param>
	/// <param name="text"> 説明用ラベル</param>
	/// <param name="label_x"> 項目用ラベルx</param>
	/// <param name="label_y"></param>
	/// <param name="label_z"></param>
	void ShowAddMeshScale(Vector3* newscale, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z,float maxsize);
	void ShowAddMeshVector(Vector3& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize, float minsize);
	void ShowAddMeshFloat(float& newparam, std::string& text, std::string& label, float maxsize, float minsize);

	//最初の処理
	void PreGui(std::shared_ptr<ComandManager>& comand);
	//最後の処理
	void PostGui(std::shared_ptr<ComandManager>& comand);
private:
	std::shared_ptr<TextureManager> _guitex;

	float* _lightintensitynum;//ライトの強弱
	Vector3* _lightdirpos;//平行光源:
	Vector3* _cubemapscale;//キューブマップ拡縮値
	unsigned int _heapeIncrementSize;
};