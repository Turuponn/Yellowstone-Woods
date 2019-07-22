#pragma once

#include "GameUI/GameUI.h"


class ICON : public GameUI {
public:
	ICON();
	~ICON();

	void CreateUI(std::shared_ptr<GameEngine>& ge, const UIDATA& uidata, const std::string& filepath);
	void DrawUI(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void SetUIData(const UIDATA& uidata);
	const UIDATA& GetUIData();
	

private:
	UIDATA _data;
};