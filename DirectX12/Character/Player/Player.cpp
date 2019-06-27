#include "Player.h"
#include "GameEngine/GameEngine.h"
#include "constance.h"
#include "Entity/Entity.h"
#include "GameUI/HPbar/HPbar.h"
using namespace DirectX;
using namespace std;

namespace {
	const int MAXHP = 100.0f;
}

Player::Player() {
	_fbxhandle = 0;
	_pushF = false;
	_animframecount = 0;
	_playerScale = {1,1,1};
}
Player::~Player() {

}
void Player::Initialize(std::shared_ptr<GameEngine>& ge) {
	//初期座標
	_playerPostion = { 0,GROUNDPOS_Y+5,0 };
	//初期姿勢
	_pinit.axis = Vector3(1, 0, 0);
	_pinit.angle = -(float)DX_PI / 2.0f;
	//前
	_pforward.axis = Vector3(0, 1, 0);
	_pforward.angle = XMConvertToRadians(180);
	//後ろ
	_pback.axis = Vector3(0, 1, 0);
	_pback.angle = XMConvertToRadians(0);
	//左
	_pleft.axis = Vector3(0, 1, 0);
	_pleft.angle = XMConvertToRadians(90);
	//右
	_pright.axis = Vector3(0, 1, 0);
	_pright.angle = XMConvertToRadians(-90);
	//媒介変数変位速度
	_tspeed = 0.1f;
	//モデルロード
	_fbxhandle = ge->LoadFBXModelDR("resource/FBX/Crow.fbx", true);
	ge->SetFBXRotateQuaternion(_fbxhandle, _pinit.axis, _pinit.angle);//初期姿勢の入力
	ge->SetFBXRotateQuaternion_mul(_fbxhandle, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
	//移動速度
	_movespeed = 0.8f;
	//hpバー
	std::shared_ptr<HPbar> hpbar(new HPbar());
	_hpbar = hpbar;
	_hpbar->CreateUI(ge,"resource/Texture/CharacterHPbar/HPbar.png");
	int sY = (SCREEN_SIZE_Y / 2);
	int sX = (SCREEN_SIZE_X / 2);
	_hpparinfo.pos = { (float)(sX-100) , (float)(-sY),0 };
	_hpparinfo.scale = { 0.2,0.2,0.2 };
	_hpdefaultinfo = _hpparinfo;
	_hp = 100.0f;

}
void Player::HPbarUpdateWorld() {
	_hpbar->SetPos(_hpparinfo.pos);
	_hpbar->SetScale(_hpparinfo.scale);
}
void Player::HPbarUpdate(std::shared_ptr<GameEngine>& ge, const int camerahandle) {
#ifdef _DEBUG
	//Screen座標空間で移動
	ge->imguiAddMeshVector(
		_hpparinfo.pos,
		string("puipos"),
		string("puipos_x"),
		string("puipos_y"),
		string("puipos_z"),
		-1280,
		1280
	);
	ge->imguiAddMeshVector(
		_hpparinfo.scale,
		string("puiscale"),
		string("puiscale_x"),
		string("puiscale_y"),
		string("puiscale_z"),
		0.0f,
		10.0f
	);
#endif
	HPbarUpdateWorld();//ワールド行列の更新
	_hpbar->DrawUI(ge, camerahandle);
}
#pragma region playerparam
void Player::HPDataUpdate() {
	////体力比率計算
	//auto hpRate = _hp / MAXHP;
	////バーのサイズ変更
	//auto scalex = _hpparinfo.scale.x * hpRate;
	//_hpparinfo.scale.x = scalex;
	////サイズ変更に合わせて場所を移動
	//auto positionx = _hpparinfo.pos.x - mDefaultScaleX * (1 - hpRate) * 0.5;
	//mTransform->Position.x = positionx;
}
#pragma endregion
void Player::Update(std::shared_ptr<GameEngine>& ge,const int camerahandle) {
	//HPbarの更新
	HPbarUpdate(ge,camerahandle);

	//カメラの軸
	auto c_axis = ge->GetCameraLookAt(camerahandle);


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
	ge->SetFBXPostionQuaternion(_fbxhandle, _playerPostion);
	ge->SetFBXScaleQuaternion(_fbxhandle, _playerScale);
	if (_pushF == false) {//待機状態
		auto endanimpos = ge->GetAnimFrameEndPos(_fbxhandle, "Idle");
		_animframecount = (_animframecount + 1) % endanimpos;
		ge->FBXAnimationPlay(_fbxhandle, "Idle", _animframecount);
	}
	else {//移動状態
		auto endanimpos = ge->GetAnimFrameEndPos(_fbxhandle, "flying");
		_animframecount = (_animframecount + 1) % endanimpos;
		ge->FBXAnimationPlay(_fbxhandle, "flying", _animframecount);
	}
	ge->DrawFBXModelDR(_fbxhandle);



	_pushF = false;
	//Playerの移動
	if (ge->CheckHitKey(DIK_W) == 1) {
		_pushF = true;

		_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion(_fbxhandle, _pinit.axis, _pinit.angle);
		ge->SetFBXRotateQuaternion_mul(_fbxhandle, _pforward.axis, _pforward.angle);
		ge->SetFBXRotateQuaternion_Matrix(_fbxhandle, pout);
		auto newvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion_Slerp(_fbxhandle, _oldvec, newvec, _tspeed);

		_playerPostion.x = _playerPostion.x + (c_axis.Normalized().x *_movespeed);
		_playerPostion.z = _playerPostion.z + (c_axis.Normalized().z *_movespeed);
	}
	if (ge->CheckHitKey(DIK_S) == 1) {
		_pushF = true;
	

		_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion(_fbxhandle, _pinit.axis, _pinit.angle);
		ge->SetFBXRotateQuaternion_mul(_fbxhandle, _pback.axis, _pback.angle);
		ge->SetFBXRotateQuaternion_Matrix(_fbxhandle, pout);
		auto newvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion_Slerp(_fbxhandle, _oldvec, newvec, _tspeed);

		_playerPostion.x = _playerPostion.x - (c_axis.Normalized().x *_movespeed);
		_playerPostion.z = _playerPostion.z - (c_axis.Normalized().z *_movespeed);
	}
	if (ge->CheckHitKey(DIK_A) == 1) {
		_pushF = true;


		_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion(_fbxhandle, _pinit.axis, _pinit.angle);
		ge->SetFBXRotateQuaternion_mul(_fbxhandle, _pleft.axis, _pleft.angle);
		ge->SetFBXRotateQuaternion_Matrix(_fbxhandle, pout);
		auto newvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion_Slerp(_fbxhandle, _oldvec, newvec, _tspeed);

		_playerPostion.x -= (c_axis.Normalized().z)*_movespeed;
		_playerPostion.z += (c_axis.Normalized().x)*_movespeed;

	}
	if (ge->CheckHitKey(DIK_D) == 1) {
		_pushF = true;


		_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion(_fbxhandle, _pinit.axis, _pinit.angle);
		ge->SetFBXRotateQuaternion_mul(_fbxhandle, _pright.axis, _pright.angle);
		ge->SetFBXRotateQuaternion_Matrix(_fbxhandle, pout);
		auto newvec = ge->GetFBXRotateQuaternion(_fbxhandle);
		ge->SetFBXRotateQuaternion_Slerp(_fbxhandle, _oldvec, newvec, _tspeed);//１のときnewvecを返す

		_playerPostion.x += (c_axis.Normalized().z)*_movespeed;
		_playerPostion.z -= (c_axis.Normalized().x)*_movespeed;
	}

}

bool Player::PushKey() {
	return _pushF;
}

const Vector3& Player::GetPostion() {
	return _playerPostion;
}
void Player::SetScale(const Vector3& newscale) {
	_playerScale = newscale;
}
const Vector3& Player::GetScale() {
	return _playerScale;
}
void Player::SetPostion(const Vector3& newpos) {
	_playerPostion = newpos;
}