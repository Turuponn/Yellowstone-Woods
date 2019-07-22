#include "Wolf.h"
#include "constance.h"
#include "GameEngine/GameEngine.h"
#include "Entity/Entity.h"
using namespace DirectX;
using namespace std;

namespace {
	const string modename = "wolf";
}

Wolf::Wolf() {
	
}
Wolf::~Wolf() {

}

void Wolf::Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata) {
	auto data = Character::GetCharacterData();
	//初期姿勢
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
	ge->LoadFBXModelDR(modename,"resource/FBX/wolf.fbx", true);
	ge->SetFBXRotateQuaternion(modename, data.init.axis, data.init.angle);//初期姿勢の入力
	ge->SetFBXRotateQuaternion_mul(modename, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(modename);
	_animframecount = 0;
	//初期ワールド行列
	data.worlddata = wdata;
	//初期移動スピード
	data.movespeed = 0.4f;
	//球面線形補間媒介変数変位速度
	data.tspeed = 0.2f;
	//待機状態
	_updateAIFunc = &Wolf::AIIdle;


	Character::SetCharacterParameterData(cdata);
	Character::SetCharacterData(data);
}
void Wolf::Update(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	auto data = Character::GetCharacterData();
	//ModelUpdate
	ge->SetFBXPostionQuaternion(modename, data.worlddata.pos);
	ge->SetFBXScaleQuaternion(modename, data.worlddata.scale);
	//Animation
	UpdateAnimation(ge);
	//DrawModel
	ge->DrawFBXModelDR(modename);

#ifdef _DEBUG
	auto pos = data.worlddata.pos;
	ge->imguiAddMeshVector3(pos, string("wolfpos"), string("wolfpos_x"), string("wolfpos_y"), string("wolfpos_z"), -50.0f, 50.0f);
#endif

	Character::SetCharacterData(data);
}
void Wolf::UpdateAnimation(std::shared_ptr<GameEngine>& ge) {
	(this->*_updateAnimationFunc)();
	auto endanimpos = ge->GetAnimFrameEndPos(modename, _nextmotionname);
	_animframecount = (_animframecount + 1) % endanimpos;
	ge->FBXAnimationPlay(modename, _nextmotionname, _animframecount);
}
void Wolf::MoveApproach(std::shared_ptr<GameEngine>& ge,const Vector3& pointpos) {
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


	_oldvec = ge->GetFBXRotateQuaternion(modename);
	ge->SetFBXRotateQuaternion(modename, data.init.axis, data.init.angle);//初期姿勢
	ge->SetFBXRotateQuaternion_mul(modename, data.forward.axis, data.forward.angle);
	ge->SetFBXRotateQuaternion_Matrix(modename, pout);
	auto newvec = ge->GetFBXRotateQuaternion(modename);
	ge->SetFBXRotateQuaternion_Slerp(modename, _oldvec, newvec, data.tspeed);

	Character::SetCharacterData(data);
}
#pragma region AI
void Wolf::AIUpdate(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos, const int DISHANTMAX, const int DISEATMAX) {
	(this->*_updateAIFunc)(ge, targetpos);
	auto data = Character::GetCharacterData();
	_updateAIFunc = &Wolf::AIIdle;

	//索敵
	auto dis = Character::GetEntiy()->Distance(targetpos, Vector3(0,0,0));
	if (dis < DISHANTMAX) {//ハントモードへ
		_updateAIFunc = &Wolf::AIHunt;
		if (dis < DISEATMAX) {//食べるモードへ
			_updateAIFunc = &Wolf::AIEat;
		}
	}
	else {//待機モードへ
		_updateAIFunc = &Wolf::AIIdle;
	}
}
void Wolf::AIIdle(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Wolf::PlayIdleMotion;//待機モーション
}
void Wolf::AIHunt(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Wolf::PlayWorkMotion;
	MoveApproach(ge,targetpos);//追跡
}
void Wolf::AIEat(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Wolf::PlayEatMotion;
}
void Wolf::AIDeath(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Wolf::PlayDeathMotion;
}
#pragma endregion


#pragma region Animation
void Wolf::PlayEatMotion() {
	_nextmotionname = "bite";
}
void Wolf::PlayWorkMotion() {
	_nextmotionname = "Work";
}
void Wolf::PlayIdleMotion() {
	_nextmotionname = "Idle";
}
void Wolf::PlayDeathMotion() {
	_nextmotionname = "Deth";//TODO:
}
#pragma endregion
const Vector3& Wolf::GetWorldPos() {
	return Character::GetCharacterData().worlddata.pos;
}
const float Wolf::GetHP() {
	return Character::GetCharacterParameterData().hp;
}
void Wolf::SetHP(const float newhp) {
	auto param = Character::GetCharacterParameterData();
	param.hp = newhp;
	Character::SetCharacterParameterData(param);
}
std::shared_ptr<Entity>& Wolf::GetEntity() {
	return Character::GetEntiy();
}