#pragma once

#include "Character/Character.h"



class HPbar;





class Player : public Character {
private://Animation
	void UpdateAnimation(std::shared_ptr<GameEngine>& ge);
	void (Player::*_updateAnimationFunc)();
	void PlayCryMotion();
	void PlayFlyingMotion();
	void PlayIdleMotion();
	void PlayStartflyMotion();

private://Input
	//入力系
	void Input(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
public:
	Player();
	~Player();
	void Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata);

	
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="ge"></param>
	void Update(std::shared_ptr<GameEngine>& ge,const std::string& cameraname);
	/// <summary>
	/// ポイントの方向を向く
	/// </summary>
	void Approachforward(std::shared_ptr<GameEngine>& ge, const Vector3& pointpos);

	void InputCry(std::shared_ptr<GameEngine>& ge);

	/// <summary>
	/// ワールド座標を返します
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();
	const float GetHP();
	void SetHP(const float newhp);
	/// <summary>
	/// 叫ぶボタンが押された場合 true:　押された false:　押されていない
	/// </summary>
	/// <returns></returns>
	bool GetPushShout();

private:
	DirectX::XMVECTOR _oldvec;//前の回転ベクトル
	int _fbxhandle;//モデルハンドル
	bool _pushF;//押された場合 true: false:
	bool _pushShoutF;//押された場合 true:押された　false:押されていない
	int _animframecount;
	std::string _nextmotionname;//次モーションの名前を入れます
	
};