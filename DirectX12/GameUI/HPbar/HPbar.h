#pragma once

#include "GameUI/GameUI.h"

class GameEngine;



struct HPINFO {
	int hp;//現在HP
	int maxhp;//最大HP
};


class HPbar : public GameUI{
public:
	HPbar();
	~HPbar();

	void CreateUI(std::shared_ptr<GameEngine>& ge, const UIDATA& ddata,const std::string& filepath);
	void DrawUI(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void SetUIData(const UIDATA& uidata);
	const UIDATA& GetUIData();


	/// <summary>
	/// HPバーとHP量を割合でリンクさせます
	/// </summary>
	void ReduceUpdate(std::shared_ptr<GameEngine>& ge, const HPINFO& hinfo);

private:
	UIDATA _defaultuidata;
	UIDATA _uidata;
};