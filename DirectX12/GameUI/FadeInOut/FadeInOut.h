#pragma once


#include "GameUI/GameUI.h"

class FadeInOut : public GameUI {
public:
	FadeInOut();
	~FadeInOut();


	void LoadResoce(std::shared_ptr<GameEngine>& ge, const UIDATA& data,const std::string& filepath);
	void FadeIn(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, const float fadeinspeed);
	void FadeOut(std::shared_ptr<GameEngine>& ge, const std::string& cameraname,const float fadeoutspeed);
	void SetUIData(const UIDATA& uidata);
	const UIDATA& GetUIData();

private:
	UIDATA _data;
};