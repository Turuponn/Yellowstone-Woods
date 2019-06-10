#pragma once


#include "Character/Character.h"

class Wolf : public Character {
public:
	Wolf();
	virtual ~Wolf();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	
	void Update(std::shared_ptr<GameEngine>& ge);

private:
	Posture _winit;//�����p��
	Posture _wforward;//�O
	Posture _wback;//���
	Posture _wleft;//��
	Posture _wright;//�E
	int _fbxhandle;//���f���n���h��
	DirectX::XMVECTOR _oldvec;//�O�̉�]�x�N�g��
	Vector3 _wolfPostion;
	Vector3 _wolfScale;
	Vector3 _wolfPosOffset;
};