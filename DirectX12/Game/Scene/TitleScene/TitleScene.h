#pragma once

#include "Game/Scene/Scene.h"


class TitleUI;

class TitleScene : public Scene {

public:
	TitleScene();
	~TitleScene();
	virtual void Init(std::shared_ptr<GameEngine>& ge);
	virtual int Update(std::shared_ptr<GameEngine>& ge);

private:
	CAMERAINFO _caminfo;
	std::shared_ptr<TitleUI> _titleui;
	int frametimecount;
	int frametimerate;

};
