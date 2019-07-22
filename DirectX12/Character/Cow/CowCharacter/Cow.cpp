#include "Cow.h"
#include "constance.h"
#include "GameEngine/GameEngine.h"
#include "Entity/Entity.h"
using namespace DirectX;
using namespace std;

namespace {
	const int FRAMETIMECOUNTMAX = 1;
	const float MAXPOSDIS = 50;//中心からどれくらい離れた位置から出現するか用定数


}

Cow::Cow() {
	_alivecount = 0;
	_randposFrame.frameCount = 0;
	_randposFrame.frameTime = 0;
	_characterFadeFrame.frameCount = 0;
	_characterFadeFrame.frameTime = 0;
	_randtargetpos.randX = 0;
	_randtargetpos.randZ = 0;
	_initrandpackage.frametimecountmax = 0;
}
Cow::~Cow() {

}
void Cow::Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata,const std::string& modelname) {
	//初期姿勢
	CHARACTERDATA data = {};
	data.init.axis = Vector3(1, 0, 0);
	data.init.angle = -(float)DX_PI / 2.0f; 
	//前
	data.forward.axis = Vector3(0, 1, 0);
	data.forward.angle = 0;
	//後ろ
	data.back.axis = Vector3(0, 1, 0);
	data.back.angle = XMConvertToRadians(-180);
	//左
	data.left.axis = Vector3(0, 1, 0);
	data.left.angle = XMConvertToRadians(-90);
	//右
	data.right.axis = Vector3(0, 1, 0);
	data.right.angle = XMConvertToRadians(90);
	//モデルロード
	ge->LoadFBXModelDR(modelname,"resource/FBX/Cow.fbx", true);
	ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);//初期姿勢の入力
	//ランダムで姿勢を変える
	auto r = ge->GetRandIntRengeMt(0, 3);
	auto axis = data.forward.axis;
	auto angle = data.forward.angle;
	if (r == 0) {
		axis = data.back.axis;
		angle = data.back.angle;
	}
	if (r == 1) {
		axis = data.left.axis;
		angle = data.left.angle;
	}
	if (r == 2) {
		axis = data.right.axis;
		angle = data.right.angle;
	}
	ge->SetFBXRotateQuaternion_mul(modelname, axis, angle);
	_oldvec = ge->GetFBXRotateQuaternion(modelname);
	//初期animation
	_updateAnimationFunc = &Cow::PlayIdleMotion;
	//初期ワールド行列
	data.worlddata = wdata;
	//初期フレーム値
	_animframecount = 0;
	//初期移動スピード
	data.movespeed = 0.3f;
	//球面線形補間媒介変数変位速度
	data.tspeed = 0.2f;
	//アニメーションを常に使用する
	_animationstopF = true;
	//待機
	_updateAIFunc = &Cow::AIIdle;
	//生きているが復活は許可されておらず消滅していない状態
	_fadeF = false;
	Character::SetCharacterParameterData(cdata);
	Character::SetCharacterData(data);
}
void Cow::EscapeUpdate(std::shared_ptr<GameEngine>& ge,const int ESCAPEDIS) {
	auto data = Character::GetCharacterData();
	//中心からどれくらい離れたか、ある程度離れていれば吹っ飛ばす
	auto discenter = Character::GetEntiy()->Distance(Vector3(0, 0, 0), data.worlddata.pos);
	if (ESCAPEDIS < discenter) {//離れている場合　飛ばす
		_updateAIFunc = &Cow::AIEscape;
	}
	
}
void Cow::Update(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const int ESCAPEDIS, const RANDPACKAGE& randpackage) {
	_initrandpackage = randpackage;
	//ModelUpdate
	ge->SetFBXPostionQuaternion(modelname, Character::GetCharacterData().worlddata.pos);
	ge->SetFBXScaleQuaternion(modelname, Character::GetCharacterData().worlddata.scale);
	//Animation
	UpdateAnimation(modelname,ge);
	//EscapeJudgment
	EscapeUpdate(ge, ESCAPEDIS);
	//Draw
	ge->DrawFBXModelDR(modelname);


	
#ifdef _DEBUG
	 auto pos = Character::GetCharacterData().worlddata.pos;
	ge->imguiAddMeshVector3(pos, string("cowpos"), string("cowpos_x"), string("cowpos_y"), string("cowpos_z"), -50.0f, 50.0f);
#endif
}
void Cow::UpdateAnimation(const std::string& modelname,std::shared_ptr<GameEngine>& ge) {
	(this->*_updateAnimationFunc)();//UpdateAnimation
	auto endanimpos = ge->GetAnimFrameEndPos(modelname, _nextmotionname);
	if (_animationstopF == true) {//何かしらの理由でストップさせる場合
		_animframecount = (_animframecount + 1) % endanimpos;
	}
	else {//ストップさせる
		_animframecount = _animframecount >= endanimpos ? endanimpos : (_animframecount + 1);
		
	}
	ge->FBXAnimationPlay(modelname, _nextmotionname, _animframecount);
#ifdef _DEBUG
	ge->imguiAddMeshInt(_animframecount, string("animcount"), string("cout"), 0, 50);
#endif
}
void Cow::MoveApproachforward(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& pointpos) {
	auto data = Character::GetCharacterData();
	
	//追跡
	Vector3 p = pointpos;
	Vector3 pw = p - data.worlddata.pos;
	pw.Normalize();
	auto direction = pw;//向き
	data.worlddata.pos.x = data.worlddata.pos.x + (direction.x *data.movespeed);
	data.worlddata.pos.z = data.worlddata.pos.z + (direction.z *data.movespeed);
	//目標に向かって回転
	auto p_axis = p - data.worlddata.pos;


	//前方を向く回転行列からクウォータニオンを作る
	XMVECTOR U = { 0,1,0 };//空(そら)ベクトル キャラの軸
	XMVECTOR zw = { p_axis.x,1.0f,p_axis.z };
	zw = XMVector3Normalize(zw);
	XMVECTOR xw = XMVector3Cross(U, zw);//水平なベクトルを求める
	xw = XMVector3Normalize(xw);
	XMVECTOR yw = XMVector3Cross(zw, xw);
	yw = XMVector3Normalize(yw);

	XMFLOAT3 z1 = {};
	XMFLOAT3 x1 = {};
	XMFLOAT3 y1 = {};
	XMStoreFloat3(&z1, zw);
	XMStoreFloat3(&x1, xw);
	XMStoreFloat3(&y1, yw);

	//指定点 P　を作る
	XMMATRIX pout = XMMatrixIdentity();
	pout.r[0].m128_f32[0] = x1.x;
	pout.r[0].m128_f32[1] = x1.y;
	pout.r[0].m128_f32[2] = x1.z;
	pout.r[0].m128_f32[3] = 0;

	pout.r[1].m128_f32[0] = y1.x;
	pout.r[1].m128_f32[1] = y1.y;
	pout.r[1].m128_f32[2] = y1.z;
	pout.r[1].m128_f32[3] = 0;

	pout.r[2].m128_f32[0] = z1.x;
	pout.r[2].m128_f32[1] = z1.y;
	pout.r[2].m128_f32[2] = z1.z;
	pout.r[2].m128_f32[3] = 0;

	pout.r[3].m128_f32[0] = 0.0f;
	pout.r[3].m128_f32[1] = 0.0f;
	pout.r[3].m128_f32[2] = 0.0f;
	pout.r[3].m128_f32[3] = 1.0f;

	_oldvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);//初期姿勢
	ge->SetFBXRotateQuaternion_mul(modelname, data.forward.axis, data.forward.angle);
	ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
	auto newvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);

	Character::SetCharacterData(data);
}

bool Cow::GetCowDeathF() {
	return Character::GetDeathF();
}
void Cow::MoveApproachback(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& pointpos) {
	auto data = Character::GetCharacterData();
	//追跡
	Vector3 p = pointpos;
	Vector3 pw = p - data.worlddata.pos;
	pw.Normalize();
	auto direction = pw;//向き
	data.worlddata.pos.x = data.worlddata.pos.x - (direction.x *data.movespeed);
	data.worlddata.pos.z = data.worlddata.pos.z - (direction.z *data.movespeed);
	//目標に向かって回転

	auto p_axis = p - data.worlddata.pos;


	//前方を向く回転行列からクウォータニオンを作る
	XMVECTOR U = { 0,1,0 };//空(そら)ベクトル キャラの軸
	XMVECTOR zw = { p_axis.x,1.0f,p_axis.z };
	zw = XMVector3Normalize(zw);
	XMVECTOR xw = XMVector3Cross(U, zw);//水平なベクトルを求める
	xw = XMVector3Normalize(xw);
	XMVECTOR yw = XMVector3Cross(zw, xw);
	yw = XMVector3Normalize(yw);

	XMFLOAT3 z1 = {};
	XMFLOAT3 x1 = {};
	XMFLOAT3 y1 = {};
	XMStoreFloat3(&z1, zw);
	XMStoreFloat3(&x1, xw);
	XMStoreFloat3(&y1, yw);

	//指定点 P　を作る
	XMMATRIX pout = XMMatrixIdentity();
	pout.r[0].m128_f32[0] = x1.x;
	pout.r[0].m128_f32[1] = x1.y;
	pout.r[0].m128_f32[2] = x1.z;
	pout.r[0].m128_f32[3] = 0;

	pout.r[1].m128_f32[0] = y1.x;
	pout.r[1].m128_f32[1] = y1.y;
	pout.r[1].m128_f32[2] = y1.z;
	pout.r[1].m128_f32[3] = 0;

	pout.r[2].m128_f32[0] = z1.x;
	pout.r[2].m128_f32[1] = z1.y;
	pout.r[2].m128_f32[2] = z1.z;
	pout.r[2].m128_f32[3] = 0;

	pout.r[3].m128_f32[0] = 0.0f;
	pout.r[3].m128_f32[1] = 0.0f;
	pout.r[3].m128_f32[2] = 0.0f;
	pout.r[3].m128_f32[3] = 1.0f;

	_oldvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);//初期姿勢
	ge->SetFBXRotateQuaternion_mul(modelname, data.back.axis, data.back.angle);
	ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
	auto newvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);

	Character::SetCharacterData(data);
}
const Vector3& Cow::GetWorldPos() {
	return Character::GetCharacterData().worlddata.pos;
}

#pragma region AI
void Cow::AIUpdate(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos,const int DISRUNMAX,const int DISMOVEMAX,const int DISDEATHMAX) {
	(this->*_updateAIFunc)(modelname,ge, targetpos);
	auto data = Character::GetCharacterData();
	_updateAIFunc = &Cow::AIIdle;//待機

	//状態遷移
	if (Character::GetDeathF()) {//生きていたら

		
		//フレームタイマーを設定し、ランダムな値を取得する
		++_randposFrame.frameTime;
		if (_randposFrame.frameTime > 60) {
			_randposFrame.frameTime = 0;
			++_randposFrame.frameCount;
		}
	
		if (FRAMETIMECOUNTMAX < _randposFrame.frameCount) {
			_randtargetpos.randX = ge->GetRandFloatRengeMt(-(MAXPOSDIS-10), MAXPOSDIS-10);//-10して即離脱を避ける
			_randtargetpos.randZ = ge->GetRandFloatRengeMt(-(MAXPOSDIS-10), MAXPOSDIS-10);
			_randposFrame.frameCount = 0;
		}
		

		//敵にある程度接近されたら
		auto dis = Character::GetEntiy()->Distance(targetpos, data.worlddata.pos);
		if (dis < DISRUNMAX) {//逃げに切り替え
			_updateAIFunc = &Cow::AIRun;
			if (dis < DISDEATHMAX) {//食べられた
				_updateAIFunc = &Cow::AIDeath;//死亡
			}
		}
		else {
			//通常の挙動、餌を求め中心方向移動する
			auto discenter = Character::GetEntiy()->Distance(//半径ｎ分ランダムな場所を目指すように　毎フレームまたはnフレームごとに更新でもいい
				Vector3(
					_randtargetpos.randX,
					1,//スタック減少を回避するために+する
					_randtargetpos.randZ),
				data.worlddata.pos
			);
			if (discenter > DISMOVEMAX) {
				_updateAIFunc = &Cow::AIMove;
			}
		}
	}
	else {//死んでたら
		_updateAIFunc = &Cow::AIEscape;//存在を消す
	}
}

void Cow::AIIdle(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Cow::PlayIdleMotion;//待機

}
void Cow::AIRun(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Cow::PlayWorkMotion;//走って
	MoveApproachback(modelname,ge, targetpos);//逃げる
}
void Cow::AIMove(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Cow::PlayWorkMotion;//走って
	MoveApproachforward(modelname,ge, Vector3(_randtargetpos.randX, 1, _randtargetpos.randZ));
}
void Cow::AIDeath(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_animationstopF = false;//Animation Stop
	Character::SetDeathF(false);//死亡
	_updateAnimationFunc = &Cow::PlayDeathMotion;
}
void Cow::AIEscape(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	auto data = Character::GetCharacterData();
	data.worlddata.pos.x = 99999;
	data.worlddata.pos.z = 99999;
	_characterFadeFrame.frameTime++;
	if (_characterFadeFrame.frameTime > 60) {
		_characterFadeFrame.frameTime = 0;
		_characterFadeFrame.frameCount++;
	}
	if (_characterFadeFrame.frameCount > _initrandpackage.frametimecountmax) {//指定フレーム待ち、消滅を解除
		_animationstopF = true;//Animation Play
		Character::SetDeathF(true);//復活
		data.worlddata.pos = _initrandpackage.randpos;
		data.worlddata.scale = _initrandpackage.randscale;
		_characterFadeFrame.frameCount = 0;
		_characterFadeFrame.frameTime = 0;
	}
	Character::SetCharacterData(data);
}
#pragma endregion

#pragma region Animation
void Cow::PlayWorkMotion() {
	_nextmotionname = "Work";
}
void Cow::PlayIdleMotion() {
	_nextmotionname = "Idle";
}
void Cow::PlayDeathMotion() {
	_nextmotionname = "Deth";//TODO:
}
#pragma endregion
