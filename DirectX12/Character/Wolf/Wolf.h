#pragma once


#include "Character/Character.h"

class HPbar;

class Wolf : public Character {
private://UI
	void HPbarUpdateWorld();
	void HPbarUpdate(std::shared_ptr<GameEngine>& ge, const int camerahandle);
public:
	Wolf();
	virtual ~Wolf();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	virtual const Vector3& GetPostion();
	virtual const Vector3& GetScale();
	virtual void SetPostion(const Vector3& newpos);
	virtual void SetScale(const Vector3& newscale);


	void Update(std::shared_ptr<GameEngine>& ge, const int camerahandle);
	/// <summary>
	/// 指定ポイントへ移動しながら近づきます
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproach(std::shared_ptr<GameEngine>& ge,const Vector3& pointpos);
	/// <summary>
	/// 食べるモーションを再生します
	/// </summary>
	void PlayEatMotion();
	/// <summary>
	/// 歩きモーションを再生します
	/// </summary>
	void PlayWorkMotion();
	/// <summary>
	/// 待機モーションを再生します
	/// </summary>
	void PlayIdleMotion();
	/// <summary>
	/// 死亡モーションを再生します
	/// </summary>
	void PlayDethMotion();


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
	int _animframecount;
	std::string _nextmotionname;//次モーションの名前を入れます
	float _movespeed;//移動速度
	float _tspeed;//球面線形補間媒介変数変位速度
	//UI
	std::shared_ptr<HPbar> _hpbar;
	CharacterHPbar _hpparinfo;
};