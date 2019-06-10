#pragma once



#include <memory>
#include <string>
#include "Geometori.h"


class GameEngine;

//�p��
struct Posture {
	Vector3 axis;
	float angle;
};

class Character {
protected:
	Character();
	virtual ~Character();
	/// <summary>
	/// ���f�����[�h���܂߂����������s���܂�
	/// </summary>
	/// <param name="ge"></param>
	virtual void Initialize(std::shared_ptr<GameEngine>& ge) = 0;


private:
};