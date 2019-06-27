#pragma once

#include "Geometori.h"
#include <memory>
#include <string>

class GameEngine;

struct HPBARINFO {
	Vector3 pos;
	Vector3 scale;
};


class HPbar {
private:
	void UpdateInfo(std::shared_ptr<GameEngine>& ge);
public:
	HPbar();
	~HPbar();

	void CreateUI(std::shared_ptr<GameEngine>& ge,const std::string& filepath);
	void DrawUI(std::shared_ptr<GameEngine>& ge, const int camerahandle);
	void SetPos(const Vector3& newpos);
	void SetScale(const Vector3& newscale);

private:
	int _uihandle;
	HPBARINFO _hpbarinfo;
};