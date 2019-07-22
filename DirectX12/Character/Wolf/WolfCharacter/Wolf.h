#pragma once


#include "Character/Character.h"





class Wolf : public Character {
private://Animation
	void UpdateAnimation(std::shared_ptr<GameEngine>& ge);
	void (Wolf::*_updateAnimationFunc)();
	void PlayEatMotion();// 食べるモーションを再生します
	void PlayWorkMotion();// 歩きモーションを再生します
	void PlayIdleMotion();// 待機モーションを再生します
	void PlayDeathMotion();// 死亡モーションを再生します
private://AI
	void (Wolf::*_updateAIFunc)(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIIdle(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIHunt(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);//追跡モード
	void AIEat(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIDeath(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
public:
	Wolf();
	~Wolf();
	void Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata);
	void Update(std::shared_ptr<GameEngine>& ge,const std::string& cameraname);
	void AIUpdate(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos, const int DISHANTMAX, const int DISEATMAX);
	/// <summary>
	/// 指定ポイントへ移動しながら近づきます
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproach(std::shared_ptr<GameEngine>& ge,const Vector3& pointpos);
	/// <summary>
	/// ワールド座標を返します
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();
	const float GetHP();
	void SetHP(const float newhp);
	std::shared_ptr<Entity>& GetEntity();
private:
	DirectX::XMVECTOR _oldvec;//前の回転ベクトル
	int _animframecount;
	std::string _nextmotionname;//次モーションの名前を入れます
};