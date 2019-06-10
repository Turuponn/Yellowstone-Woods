#pragma once

#include "Character/Character.h"






class Player : public Character {
public:
	Player();
	virtual ~Player();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
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
	/// <summary>
	/// プレイヤーの中心座標を返します
	/// </summary>
	/// <returns></returns>
	Vector3 GetPlayerPos();
	/// <summary>
	/// あたらしい中心座標を外部から入力します
	/// </summary>
	/// <param name="newp"></param>
	void SetPlayerPos(const Vector3& newp);

private:
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
	float _t;//球面線形補間の補間用変数
	float _tspeed;//補間速度
	float _movespeed;//キャラクター移動速度
};