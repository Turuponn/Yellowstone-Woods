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
�V���O���g���N���X
*/
private:
	void Init();
private:
	GameScene();
	GameScene(const GameScene&);
	GameScene& operator=(const GameScene&);
public:
	~GameScene();
	
	//�X�V
	void Run();
	//�V�[���ύX
	void ChengeScene(Scene* scene);
	//���Ԑ���
	static GameScene& Instance();


private:
	std::shared_ptr<GameEngine> _ge;
	std::shared_ptr<PlayerManager> _player;
	std::shared_ptr<Tree> _tree;
	std::shared_ptr<Map> _map;
	std::shared_ptr<WolfManager> _wolf;
	std::shared_ptr<CowManager> _cow;
	std::shared_ptr<Entity> _entity;//�R���W�����Z�p�p
	std::shared_ptr<GameUI> _gameui;
	Scene* _scene;//���݂̃V�[��
};