#pragma once

#include "Character/Character.h"



class HPbar;





class Player : public Character {
private://player param
	void HPDataUpdate();

private://UI
	void HPbarUpdateWorld();
	void HPbarUpdate(std::shared_ptr<GameEngine>& ge, const int camerahandle);
private://Input

public:
	Player();
	virtual ~Player();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	virtual const Vector3& GetPostion();
	virtual const Vector3& GetScale();
	virtual void SetPostion(const Vector3& newpos);
	virtual void SetScale(const Vector3& newscale);


	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="camerahandle">カメラとキャラクターを対にします</param>
	void Update(std::shared_ptr<GameEngine>& ge, const int camerahandle);
	/// <summary>
	/// キーが押されているかどうかを返します
	/// </summary>
	/// <returns>true: 押されている false: 押されていない</returns>
	bool PushKey();


private:
	std::shared_ptr<HPbar> _hpbar;
	CharacterHPbar _hpparinfo;
	CharacterHPbar _hpdefaultinfo;
	Posture _pinit;//初期姿勢
	Posture _pforward;//前
	Posture _pback;//後ろ
	Posture _pleft;//左
	Posture _pright;//右
	DirectX::XMVECTOR _oldvec;//前の回転ベクトル
	Vector3 _playerPostion;
	Vector3 _playerScale;
	int _fbxhandle;//モデルハンドル
	bool _pushF;//押された場合 true: false:
	int _animframecount;
	float _tspeed;//球面線形補間媒介変数変位速度
	float _movespeed;//キャラクター移動速度

	float _hp;//プレイヤーhp
};