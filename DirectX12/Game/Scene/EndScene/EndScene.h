#pragma once

#include "Game/Scene/Scene.h"

class EndUI;

class EndScene : public Scene {
private:
	void InitCamera(std::shared_ptr<GameEngine>& ge);
	void InitUI(std::shared_ptr<GameEngine>& ge);
public:
	EndScene();
	~EndScene();

	virtual void Init(std::shared_ptr<GameEngine>& ge);
	virtual int Update(std::shared_ptr<GameEngine>& ge);
	
private:
	CAMERAINFO _caminfo;
	std::shared_ptr<EndUI> _ui;
	int frametimecount;
	int frametimerate;
};