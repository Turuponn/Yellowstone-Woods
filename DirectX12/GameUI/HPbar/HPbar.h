#pragma once

#include "GameUI/GameUI.h"

class GameEngine;



struct HPINFO {
	int hp;//Œ»İHP
	int maxhp;//Å‘åHP
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
	/// HPƒo[‚ÆHP—Ê‚ğŠ„‡‚ÅƒŠƒ“ƒN‚³‚¹‚Ü‚·
	/// </summary>
	void ReduceUpdate(std::shared_ptr<GameEngine>& ge, const HPINFO& hinfo);

private:
	UIDATA _defaultuidata;
	UIDATA _uidata;
};