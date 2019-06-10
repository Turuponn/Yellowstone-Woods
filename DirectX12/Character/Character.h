#pragma once



#include <memory>
#include <string>
#include "Geometori.h"


class GameEngine;

//姿勢
struct Posture {
	Vector3 axis;
	float angle;
};

class Character {
protected:
	Character();
	virtual ~Character();
	/// <summary>
	/// モデルロードを含めた初期化を行います
	/// </summary>
	/// <param name="ge"></param>
	virtual void Initialize(std::shared_ptr<GameEngine>& ge) = 0;


private:
};