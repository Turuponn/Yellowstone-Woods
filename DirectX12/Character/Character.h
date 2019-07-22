#pragma once



#include <memory>
#include <string>
#include "Geometori.h"
#define GROUNDPOS_Y 1 //Y座標offsetデータ

class GameEngine;
class Entity;


//姿勢
struct POSTURE {
	Vector3 axis;
	float angle;
};
//キャラ用HPbar
struct CHARACTERHPBAR {
	Vector3 pos;
	Vector3 scale;
};
//ワールド行列用データ
struct WORLDDATA {
	Vector3 pos;
	Vector3 scale;
	Vector3 rotate;
};
//キャラクター用保有データ
struct CHARACTERDATA {
	WORLDDATA worlddata;//ワールド行列用データ
	POSTURE init;//初期姿勢
	POSTURE forward;//前
	POSTURE back;//後ろ
	POSTURE left;//左
	POSTURE right;//右
	float movespeed;//移動速度
	float tspeed;//球面線形補間媒介変数変位速度
};
struct CHARACTERPARAMETERDATA {
	float hp;
};


struct FRAMETIME {
	unsigned int frameTime;//フレームをカウントする
	unsigned int frameCount;//フレームをいくつカウントしたか
};



class Character {
private:
	void init();
protected:
	Character();
	



	///アクセッサ====================================
	/// <summary>
	/// コリジョンマネージャーを返します
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<Entity>& GetEntiy();
	/// <summary>
	/// 死亡しているかどうかを返します
	/// </summary>
	/// <returns>true: 生きている false:　死亡している</returns>
	bool GetDeathF();
	/// <summary>
	/// 死亡するべきかどうかを更新します
	/// </summary>
	/// <param name="newstatus">true:　生きている false:　死亡している</param>
	void SetDeathF(bool newstatus);
	/// <summary>
	/// キャラクター保持データを返します
	/// </summary>
	/// <returns></returns>
	const CHARACTERDATA& GetCharacterData();
	/// <summary>
	/// キャラクター保持データを更新します
	/// </summary>
	/// <param name="newcharacterdata"></param>
	void SetCharacterData(const CHARACTERDATA& newcharacterdata);
	/// <summary>
	/// キャラクター保持データ:パラメータ　を更新します
	/// </summary>
	/// <param name="cparamdata"></param>
	void SetCharacterParameterData(const CHARACTERPARAMETERDATA& cparamdata);
	/// <summary>
	/// キャラクター保持データ:パラメータ　を返します
	/// </summary>
	/// <returns></returns>
	const CHARACTERPARAMETERDATA& GetCharacterParameterData();
	///純粋仮想関数==================================
	
public:
	virtual ~Character();
	
private:
	std::shared_ptr<Entity> _entity;
	CHARACTERDATA _characterdata;
	CHARACTERPARAMETERDATA _cparamdata;
	bool _deathF;//死亡していて復活の猶予もない場合 true:　生きてる false:　生きていない
};