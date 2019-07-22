#pragma once


#include "Geometori.h"
#include "GameUI/GameUI.h"
#include <memory>
#include <string>

class GameEngine;



struct MEATINFO {
	float animspeed;
};

class Meat : public GameUI {
public:
	Meat();
	~Meat();
	void CreateUI(std::shared_ptr<GameEngine>& ge, const UIDATA& begindata, const UIDATA& enddata, const std::string& filepath);
	void DrawUI(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void SetUIData(const UIDATA& uidata);
	void SetUIBeginData(const UIDATA& uidata);
	void SetUIEndData(const UIDATA& uidata);
	const UIDATA& GetUIBeginData();
	const UIDATA& GetUIEndData();
	const UIDATA& GetUIData();
	/// <summary>
	/// お肉用アニメーションさせます　
	/// </summary>
	/// <param name="data"></param>
	/// <param name="info"></param>
	/// <param name="playanimF">アニメーションさせている場合用処理</param>
	void AnimationMeat(const UIDATA& data,const MEATINFO& info,bool playanimF);
	/// <summary>
	/// アニメーション終了を知らせます
	/// </summary>
	/// <returns></returns>
	bool GetAnimF();

private:
	UIDATA _enddata;
	UIDATA _begindata;
	UIDATA _data;
	bool _playanimF;
};