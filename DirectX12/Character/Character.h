#pragma once



#include <memory>
#include <string>
#include "Geometori.h"
#define GROUNDPOS_Y 1 //BB�g���ăT�C�Y��

class GameEngine;
class Entity;


//�p��
struct Posture {
	Vector3 axis;
	float angle;
};
//�L�����pHPbar
struct CharacterHPbar {
	Vector3 pos;
	Vector3 scale;
};

class Character {
private:
	void init();
protected:
	Character();
	virtual ~Character();
	/// <summary>
	/// �R���W�����}�l�[�W���[��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<Entity>& GetEntiy();




	/// <summary>
	/// ���f�����[�h���܂߂����������s���܂�
	/// </summary>
	/// <param name="ge"></param>
	virtual void Initialize(std::shared_ptr<GameEngine>& ge) = 0;
	/// �A�N�Z�b�T=====================================
	virtual const Vector3& GetPostion() = 0;
	virtual const Vector3& GetScale() = 0;
	virtual void SetPostion(const Vector3& newpos) = 0;
	virtual void SetScale(const Vector3& newscale) = 0;


private:
	std::shared_ptr<Entity> _entity;
};