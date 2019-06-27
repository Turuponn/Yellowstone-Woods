#pragma once

#include "Character/Character.h"

class Cow : public Character {
public:
	Cow();
	virtual ~Cow();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	virtual const Vector3& GetPostion();
	
	virtual const Vector3& GetScale();
	virtual void SetPostion(const Vector3& newpos);
	virtual void SetScale(const Vector3& newscale);

	void Update(std::shared_ptr<GameEngine>& ge);
	

private:
	Posture _cowinit;//èâä˙épê®
	Posture _cowforward;//ëO
	Posture _cowback;//å„ÇÎ
	Posture _cowleft;//ç∂
	Posture _cowright;//âE
	Vector3 _cowPostion;
	Vector3 _cowScale;
	Vector3 _cowPosOffset;

	DirectX::XMVECTOR _oldvec;
	int _fbxhandle;
	int _animframecount;

};