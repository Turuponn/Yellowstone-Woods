#pragma once


#include "Geometori.h"
#include <memory>


class WindowInit;
class GameEngine;

class Player;
class Tree;
class Map;
class Wolf;
class Cow;
class Entity;
class GameUI;

class GameScene {
public:
	GameScene();
	virtual ~GameScene();
	void Initialize(WindowInit& windowinstance);
	void Updata();

private:
	std::shared_ptr<GameEngine> _ge;
	std::shared_ptr<Player> _player;
	std::shared_ptr<Tree> _tree;
	std::shared_ptr<Map> _map;
	std::shared_ptr<Wolf> _wolf;
	std::shared_ptr<Cow> _cow;//TODO:　こいつは内部で複数になります
	std::shared_ptr<Entity> _entity;//コリジョン算術用
	std::shared_ptr<GameUI> _gameui;
};