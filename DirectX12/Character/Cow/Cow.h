#pragma once

#include "Character/Character.h"

class Cow : public Character {
public:
	Cow();
	virtual ~Cow();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	
	void Update(std::shared_ptr<GameEngine>& ge);

private:
	Posture _cowinit;//�����p��
	Posture _cowforward;//�O
	Posture _cowback;//���
	Posture _cowleft;//��
	Posture _cowright;//�E
	Vector3 _cowPostion;
	Vector3 _cowScale;
	Vector3 _cowPosOffset;

	DirectX::XMVECTOR _oldvec;
	int _fbxhandle;

};