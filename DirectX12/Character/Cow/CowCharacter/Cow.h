#pragma once

#include "Character/Character.h"



struct RANDPOS {
	float randX;
	float randY;
	float randZ;
};
struct RANDPACKAGE {
	Vector3 randpos;
	Vector3 randscale;
	int frametimecountmax;//どのくらいフレームで待てばいいか最大値
};

class Cow : public Character {
private:
	void EscapeUpdate(std::shared_ptr<GameEngine>& ge, const int ESCAPEDIS);//一定範囲を超えた場合、逃げ切ったとみなし割り込み処理を発生させる
private://AI
	void (Cow::*_updateAIFunc)(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIIdle(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIRun(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);//逃げモード
	void AIMove(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);//餌を求めて移動する
	void AIDeath(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIEscape(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
private:
	void MoveToDeath();// 死亡後死体がのこらないように遥か彼方へ飛ばす処理
private://Animation
	void UpdateAnimation(const std::string& modelname,std::shared_ptr<GameEngine>& ge);//アニメーション更新
	void (Cow::*_updateAnimationFunc)();
	void PlayWorkMotion();// 歩きモーションを再生します
	void PlayIdleMotion();// 待機モーションを再生します
	void PlayDeathMotion();// 死亡モーションを再生します

public:
	Cow();
	~Cow();
	void Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata, const std::string& modelname);

	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="ESCAPEDIS">逃げ切る際判定用半径</param>
	/// <param name="randpackage">ランダム初期化用</param>
	void Update(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const int ESCAPEDIS,const RANDPACKAGE& randpackage);
	/// <summary>
	/// AIの更新
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="targetpos"></param>
	/// <param name="DISRUNMAX">走る場合、距離の範囲</param>
	/// <param name="DISMOVEMAX">中心に移動する場合、距離の範囲</param>
	/// <param name="DISDEATHMAX">死亡する場合、距離の範囲</param>
	void AIUpdate(
		const std::string& modelname,
		std::shared_ptr<GameEngine>& ge,
		const Vector3& targetpos,
		const int DISRUNMAX, 
		const int DISMOVEMAX,
		const int DISDEATHMAX
	);
	/// <summary>
	/// 指定ポイントへ前進移動しながら近づきます
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproachforward(const std::string& modelname,std::shared_ptr<GameEngine>& ge,const Vector3& pointpos);
	/// <summary>
	/// 指定ポイントを見て後退移動しながら退きます
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproachback(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& pointpos);
	/// <summary>
	/// 死亡しているかどうか
	/// </summary>
	/// <returns>true:　生きている false:　死亡している</returns>
	bool GetCowDeathF();
	/// <summary>
	/// ワールド座標を返す
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();

	
private:
	
	
	DirectX::XMVECTOR _oldvec;
	int _animframecount;
	int _alivecount;//復活用カウンタ
	

	std::string _nextmotionname;//次モーションの名前を入れます
	bool _animationstopF;//アニメーションを使用するかどうか true:　する false:　しない
	bool _fadeF;//消滅しているか true:消滅している false:消滅していない
	RANDPOS _randtargetpos;//ランダムな注視点
	FRAMETIME _randposFrame;
	RANDPACKAGE _initrandpackage;//初期化用乱数を保存しておく
	FRAMETIME _characterFadeFrame;//消滅した場合用フレーム制御
};