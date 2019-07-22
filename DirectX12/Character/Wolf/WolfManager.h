#pragma once

#include "Geometori.h"

#include <memory>
#include <vector>
#include <string>

//シーンによるグローバル設定
struct WOLFINITINFO {
	int _hpframetimelimit;//フレームリセットタイミングパラメータ
	int _hpRecovery;//回復量
};


class GameEngine;
class Wolf;
class CowManager;
class HPbar;
class ICON;
class Meat;
struct UIDATA;

class WolfManager {
private://Model
	void ModelInitialize(std::shared_ptr<GameEngine>& ge);
private://UI
	void UIInitialize(std::shared_ptr<GameEngine>& ge);
	//HP
	void HPbarHPUpdate(std::shared_ptr<GameEngine>& ge);//プレイヤーHPについてHPbarを更新します
	void HPUpdate(std::shared_ptr<GameEngine>& ge);
	//Meat
	void MeatUpdate(std::shared_ptr<GameEngine>& ge);

	void UIUpdate(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
public:
	WolfManager();
	~WolfManager();
	void Initialize(std::shared_ptr<GameEngine>& ge,const WOLFINITINFO& scenewolfinitinfo);
	void Update(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void AIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<CowManager>& cowmanager);
	const Vector3& GetWorldPos();
	/// <summary>
	/// 肉を食べた場合 true:　食べた false:　食べていない
	/// </summary>
	/// <returns></returns>
	bool GetEatDeathMeatRecoveryF();

	//現在のHPを返します
	float GetHP();

private:
	std::shared_ptr<Wolf> _wolf;
	std::shared_ptr<HPbar> _hpbar;
	std::shared_ptr<HPbar> _hpbarframe;
	std::shared_ptr<ICON> _icon;
	std::shared_ptr <Meat> _meat;
	std::shared_ptr <UIDATA> _debugBeginmeatuidata;
	std::shared_ptr <UIDATA> _debugEndmeatuidata;
	int _nearcowindex;//一番近い牛のindex
	WOLFINITINFO _info;//初期化用パラメータ
	
	
	int _hpframetime;//hp減少用
	bool _meateatuianimF;//肉になった場合 true: 表示 false:非表示
	bool _eatdeathMeatRecoveryF;//回復用フラグ true:回復 false:回復しない
	
};