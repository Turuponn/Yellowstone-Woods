#pragma once

#include "Geometori.h"
#include <memory>
#include <vector>
#include <string>

class GameEngine;
class Player;
class HPbar;
class ICON;
class Meat;
class WolfManager;


struct UIDATA;



//シーンによるグローバル設定
struct PLAYERINITINFO {
	int _hpframetimelimit;//フレームリセットタイミングパラメータ
	int _hpRecovery;//HP回復量
};

class PlayerManager {
private://Model
	void ModelInitialize(std::shared_ptr<GameEngine>& ge);

private://UI
	void UIInitialize(std::shared_ptr<GameEngine>& ge);
	//HP
	void HPbarHPUpdate(std::shared_ptr<GameEngine>& ge);//プレイヤーHPについてHPbarを更新します
	void HPUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf);
	//Meat
	void MeatUpdate(std::shared_ptr<GameEngine>& ge);


	void UIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf,const std::string& cameraname);
public:
	PlayerManager();
	~PlayerManager();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(std::shared_ptr<GameEngine>& ge, const PLAYERINITINFO& sceneplayerinitinfo);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf, const std::string& cameraname);
	/// <summary>
	/// ワールド座標を返します
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();
	/// <summary>
	/// 叫ぶボタンを返します true: 押された false: 押されていない
	/// </summary>
	/// <returns></returns>
	bool GetPushShoutF();
	/// <summary>
	/// モデルに対し注視点を向くように回転させます
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="lookpoint"></param>
	void LookAt(std::shared_ptr<GameEngine>& ge,const Vector3& lookpoint);
	/// <summary>
	/// 現在HPを返す
	/// </summary>
	/// <returns></returns>
	float GetHP();
private:
	std::shared_ptr<Player> _player;
	std::shared_ptr<HPbar> _hpbar;
	std::shared_ptr<HPbar> _hpbarframe;
	std::shared_ptr<ICON> _icon;
	std::shared_ptr<Meat> _meathalf;
	std::shared_ptr<UIDATA> _debugmeathalfbegindata;
	std::shared_ptr<UIDATA> _debugmeathalfenddata;
	
	int _hpframetime;//hp減少用
	PLAYERINITINFO _info;
	bool _meateatuianimF;//お肉食べアニメーションの再生 true:再生する false:
};
