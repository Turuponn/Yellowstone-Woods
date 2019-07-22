#include "Player.h"
#include "GameEngine/GameEngine.h"
#include "constance.h"
#include "Entity/Entity.h"

using namespace DirectX;
using namespace std;


namespace {
	const string modelname = "crow";
}


Player::Player() {
	_fbxhandle = 0;
	_pushF = false;
	_pushShoutF = false;
	_animframecount = 0;
}
Player::~Player() {

}
void Player::Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata,const CHARACTERPARAMETERDATA& cdata) {
	 auto data = Character::GetCharacterData();
	//初期行列
	 data.worlddata = wdata;
	//初期姿勢
	 data.init.axis = Vector3(1, 0, 0);
	 data.init.angle = -(float)DX_PI / 2.0f;
	//前
	 data.forward.axis = Vector3(0, 1, 0);
	 data.forward.angle = XMConvertToRadians(180);
	//後ろ
	 data.back.axis = Vector3(0, 1, 0);
	 data.back.angle = XMConvertToRadians(0);
	//左
	 data.left.axis = Vector3(0, 1, 0);
	 data.left.angle = XMConvertToRadians(90);
	//右
	 data.right.axis = Vector3(0, 1, 0);
	 data.right.angle = XMConvertToRadians(-90);
	//媒介変数変位速度
	 data.tspeed = 0.3f;
	//モデルロード
	ge->LoadFBXModelDR(modelname,"resource/FBX/Crow.fbx", true);
	ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);//初期姿勢の入力
	ge->SetFBXRotateQuaternion_mul(modelname, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(modelname);
	//移動速度
	data.movespeed = 0.8f;
	//初期状態
	_updateAnimationFunc = &Player::PlayIdleMotion;



	Character::SetCharacterParameterData(cdata);
	Character::SetCharacterData(data);
}
void Player::Update(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	//入力系更新
	Input(ge, cameraname);
	//Animation
	UpdateAnimation(ge);
	//DrawModel
	ge->DrawFBXModelDR(modelname);
}
void Player::Approachforward(std::shared_ptr<GameEngine>& ge, const Vector3& pointpos) {
	auto data = Character::GetCharacterData();

	//追跡
	Vector3 p = pointpos;
	Vector3 pw = p - data.worlddata.pos;
	pw.Normalize();
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
#pragma region Animation
void Player::UpdateAnimation(std::shared_ptr<GameEngine>& ge) {
	(this->*_updateAnimationFunc)();
	auto endanimpos = ge->GetAnimFrameEndPos(modelname, _nextmotionname);
	_animframecount = (_animframecount + 1) % endanimpos;
	ge->FBXAnimationPlay(modelname, _nextmotionname, _animframecount);
}
void Player::PlayCryMotion() {
	_nextmotionname = "Cry";//TODO: Cry->shout 
}
void Player::PlayFlyingMotion() {
	_nextmotionname = "flying";
}
void Player::PlayIdleMotion() {
	_nextmotionname = "Idle";
}
void Player::PlayStartflyMotion() {
	_nextmotionname = "startfly";
}
#pragma endregion
void Player::InputCry(std::shared_ptr<GameEngine>& ge) {
	//叫ぶ
	if (ge->CheckHitKey(DIK_SPACE)) {
		_updateAnimationFunc = &Player::PlayCryMotion;
		_pushShoutF = true;
	}
}
void Player::Input(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	auto data = Character::GetCharacterData();
	//カメラの軸
	auto c_axis = ge->GetCameraLookAt(cameraname);


	//前方を向く回転行列からクウォータニオンを作る
	XMVECTOR U = { 0,1,0 };//空(そら)ベクトル キャラの軸
	XMVECTOR zw = { c_axis.x,1.0f,c_axis.z };
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

	//Player
	ge->SetFBXPostionQuaternion(modelname, data.worlddata.pos);
	ge->SetFBXScaleQuaternion(modelname, data.worlddata.scale);


	
	


	if (_pushShoutF == false) {
		if (_pushF == false) {//待機状態
			_updateAnimationFunc = &Player::PlayIdleMotion;
		}
		else {//移動状態
			_updateAnimationFunc = &Player::PlayFlyingMotion;
		}
	}
	

		
	


	_pushF = false;
	_pushShoutF = false;
	//Playerの移動
	if (ge->CheckHitKey(DIK_W)) {
		_pushF = true;

		_oldvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);
		ge->SetFBXRotateQuaternion_mul(modelname, data.forward.axis, data.forward.angle);
		ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
		auto newvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);

		data.worlddata.pos.x = data.worlddata.pos.x + (c_axis.Normalized().x *data.movespeed);
		data.worlddata.pos.z = data.worlddata.pos.z + (c_axis.Normalized().z *data.movespeed);
	}
	if (ge->CheckHitKey(DIK_S)) {
		_pushF = true;


		_oldvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);
		ge->SetFBXRotateQuaternion_mul(modelname, data.back.axis, data.back.angle);
		ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
		auto newvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);

		data.worlddata.pos.x = data.worlddata.pos.x - (c_axis.Normalized().x *data.movespeed);
		data.worlddata.pos.z = data.worlddata.pos.z - (c_axis.Normalized().z *data.movespeed);
	}
	if (ge->CheckHitKey(DIK_A)) {
		_pushF = true;


		_oldvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);
		ge->SetFBXRotateQuaternion_mul(modelname, data.left.axis, data.left.angle);
		ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
		auto newvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);

		data.worlddata.pos.x -= (c_axis.Normalized().z)*data.movespeed;
		data.worlddata.pos.z += (c_axis.Normalized().x)*data.movespeed;

	}
	if (ge->CheckHitKey(DIK_D)) {
		_pushF = true;


		_oldvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);
		ge->SetFBXRotateQuaternion_mul(modelname, data.right.axis, data.right.angle);
		ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
		auto newvec = ge->GetFBXRotateQuaternion(modelname);
		ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);//１のときnewvecを返す

		data.worlddata.pos.x += (c_axis.Normalized().z)*data.movespeed;
		data.worlddata.pos.z -= (c_axis.Normalized().x)*data.movespeed;
	}
	

	Character::SetCharacterData(data);
}

const Vector3& Player::GetWorldPos() {
	return Character::GetCharacterData().worlddata.pos;
}
bool Player::GetPushShout() {
	return _pushShoutF;
}
const float Player::GetHP() {
	return Character::GetCharacterParameterData().hp;
}
void Player::SetHP(const float newhp) {
	auto param = Character::GetCharacterParameterData();
	param.hp = newhp;
	Character::SetCharacterParameterData(param);
}