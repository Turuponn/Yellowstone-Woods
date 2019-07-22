#pragma once


#include "Geometori.h"
#include <memory>


class WindowInit;
class GameEngine;

class PlayerManager;
class Tree;
class Map;
class WolfManager;
class CowManager;
class Entity;
class GameUI;

class Scene;

struct GAMEMAIN;

class GameScene {
/*
シングルトンクラス
*/
private:
	void Init();
private:
	GameScene();
	GameScene(const GameScene&);
	GameScene& operator=(const GameScene&);
public:
	~GameScene();
	
	//更新
	void Run();
	//シーン変更
	void ChengeScene(Scene* scene);
	//実態生成
	static GameScene& Instance();


private:
	std::shared_ptr<GameEngine> _ge;
	std::shared_ptr<PlayerManager> _player;
	std::shared_ptr<Tree> _tree;
	std::shared_ptr<Map> _map;
	std::shared_ptr<WolfManager> _wolf;
	std::shared_ptr<CowManager> _cow;
	std::shared_ptr<Entity> _entity;//コリジョン算術用
	std::shared_ptr<GameUI> _gameui;
	Scene* _scene;//現在のシーン
};