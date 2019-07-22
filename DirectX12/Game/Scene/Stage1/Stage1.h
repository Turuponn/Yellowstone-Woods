#pragma once

#include "Game/Scene/Scene.h"

class PlayerManager;
class Tree;
class Map;
class WolfManager;
class CowManager;
class Entity;




class Stage1 :public Scene {
public:
	Stage1();
	~Stage1();
	virtual void Init(std::shared_ptr<GameEngine>& ge);
	virtual int Update(std::shared_ptr<GameEngine>& ge);
private:
	CAMERAINFO _caminfo;
	

	std::shared_ptr<PlayerManager> _player;
	std::shared_ptr<Tree> _tree;
	std::shared_ptr<Map> _map;
	std::shared_ptr<WolfManager> _wolf;
	std::shared_ptr<CowManager> _cow;
	std::shared_ptr<Entity> _entity;

	//cubemap
	int _cubemaphandle;
	Vector3 _cubemapscale;
	Vector3 _cubemapPostion;






};
