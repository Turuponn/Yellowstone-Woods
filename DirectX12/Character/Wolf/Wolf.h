#pragma once


#include "Character/Character.h"

class Wolf : public Character {
public:
	Wolf();
	virtual ~Wolf();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	
	void Update(std::shared_ptr<GameEngine>& ge);

private:
	Posture _winit;//初期姿勢
	Posture _wforward;//前
	Posture _wback;//後ろ
	Posture _wleft;//左
	Posture _wright;//右
	int _fbxhandle;//モデルハンドル
	DirectX::XMVECTOR _oldvec;//前の回転ベクトル
	Vector3 _wolfPostion;
	Vector3 _wolfScale;
	Vector3 _wolfPosOffset;
};