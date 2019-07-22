#pragma once

#include "GameUI/GameUI.h"


class UIDefault : public GameUI {
public:
	UIDefault();
	~UIDefault();

	void Create(std::shared_ptr<GameEngine>& ge, const UIDATA& uidata, const std::string& filepath);
	void Draw(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void SetData(const UIDATA& uidata);
	const UIDATA& GetData();

private:
	UIDATA _data;
};
