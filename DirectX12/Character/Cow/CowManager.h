#pragma once

#include "Geometori.h"

#include <memory>
#include <vector>
#include <string>

class Cow;
class GameEngine;
class Entity;
class WolfManager;




class CowManager{
public:
	CowManager();
	~CowManager();
	void Initialize(std::shared_ptr<GameEngine>& ge,const int maxcows);
	void Update(std::shared_ptr<GameEngine>& ge);
	void AIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolfmanager);
	/// <summary>
	/// 一番近い牛の情報のindexを返す、探索を終了した場合-1を返す
	/// </summary>
	const int GetNearCow(const Vector3& targetpos);
	/// <summary>
	/// 指定された牛の座標を返す
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos(const int index);
	/// <summary>
	/// 指定された牛の死亡判定を返す
	/// </summary>
	/// <param name="index"></param>
	/// <returns>true: 生きている false:死んでいる</returns>
	bool GetDeath(const int index);
	/// <summary>
	/// シャウトを食らうときの処理
	/// </summary>
	/// <param name="playerpos"></param>
	void MoveShout(std::shared_ptr<GameEngine>& ge,const Vector3& playerpos);
private:
	std::vector<std::shared_ptr<Cow>> _cows;
	std::shared_ptr<Entity> _entity;
	int _maxcows;
	std::vector<float> _dises;//距離入れ
	int _nearcowindex;//一番近い座標
	unsigned int _frameTime;
};