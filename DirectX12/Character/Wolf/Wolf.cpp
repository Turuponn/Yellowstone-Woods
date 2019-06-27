#include "Wolf.h"
#include "constance.h"
#include "GameEngine/GameEngine.h"
#include "GameUI/HPbar/HPbar.h"
using namespace DirectX;
using namespace std;

Wolf::Wolf() {
	
}
Wolf::~Wolf() {

}

void Wolf::Initialize(std::shared_ptr<GameEngine>& ge) {
	//初期姿勢
	_winit.axis = Vector3(1, 0, 0);
	_winit.angle = -(float)DX_PI / 2.0f;
	//前
	_wforward.axis = Vector3(0, 1, 0);
	_wforward.angle = 0;
	//後ろ
	_wback.axis = Vector3(0, 1, 0);
	_wback.angle = XMConvertToRadians(-180);
	//左
	_wleft.axis = Vector3(0, 1, 0);
	_wleft.angle = XMConvertToRadians(-90);
	//右
	_wright.axis = Vector3(0, 1, 0);
	_wright.angle = XMConvertToRadians(90);

	//モデルロード
	_fbxhandle = ge->LoadFBXModelDR("resource/FBX/wolf.fbx", true);
	ge->SetFBXRotateQuaternion(_fbxhandle, _winit.axis, _winit.angle);//初期姿勢の入力
	ge->SetFBXRotateQuaternion_mul(_fbxhandle, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
	_animframecount = 0;
	//初期拡縮値
	_wolfScale = Vector3(2, 2, 2);
	//初期座標
	_wolfPostion = Vector3(-50, GROUNDPOS_Y+_wolfScale.y, 0);
	//初期animation
	_nextmotionname = "Idle";
	//初期移動スピード
	_movespeed = 0.5f;
	//球面線形補間媒介変数変位速度
	_tspeed = 0.2f;
	//UI: HPbar
	std::shared_ptr<HPbar> hpbar(new HPbar());
	_hpbar = hpbar;
	_hpbar->CreateUI(ge,"resource/Texture/CharacterHPbar/Wolf/animal_ookami.png");
	_hpparinfo.pos = {0,0,0};
	_hpparinfo.scale = { 0.3,0.3,0.3 };
}
void Wolf::Update(std::shared_ptr<GameEngine>& ge,const int camerahandle) {
	//UIUpdate
	HPbarUpdate(ge, camerahandle);
	//ModelUpdate
	ge->SetFBXPostionQuaternion(_fbxhandle, _wolfPostion+ _wolfPosOffset);
	ge->SetFBXScaleQuaternion(_fbxhandle, _wolfScale);
	auto endanimpos = ge->GetAnimFrameEndPos(_fbxhandle, _nextmotionname);
	_animframecount = (_animframecount + 1) % endanimpos;
	ge->FBXAnimationPlay(_fbxhandle, _nextmotionname, _animframecount);
	//DrawModel
	ge->DrawFBXModelDR(_fbxhandle);

#ifdef _DEBUG
	ge->imguiAddMeshVector(_wolfPostion, string("wolfpos"), string("wolfpos_x"), string("wolfpos_y"), string("wolfpos_z"), -50.0f, 50.0f);
#endif
}
void Wolf::MoveApproach(std::shared_ptr<GameEngine>& ge,const Vector3& pointpos) {
	//追跡
	Vector3 p = pointpos;
	Vector3 pw = p -_wolfPostion;
	pw.Normalize();
	 auto direction = pw;//向き
	_wolfPostion.x = _wolfPostion.x + (direction.x *_movespeed);
	_wolfPostion.z = _wolfPostion.z + (direction.z *_movespeed);
	//目標に向かって回転

	auto p_axis = p - _wolfPostion;


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


	_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
	ge->SetFBXRotateQuaternion(_fbxhandle, _winit.axis, _winit.angle);//初期姿勢
	ge->SetFBXRotateQuaternion_mul(_fbxhandle, _wforward.axis, _wforward.angle);
	ge->SetFBXRotateQuaternion_Matrix(_fbxhandle, pout);
	auto newvec = ge->GetFBXRotateQuaternion(_fbxhandle);
	ge->SetFBXRotateQuaternion_Slerp(_fbxhandle, _oldvec, newvec, _tspeed);


}
void Wolf::HPbarUpdateWorld() {
	_hpbar->SetPos(_hpparinfo.pos);
	_hpbar->SetScale(_hpparinfo.scale);
}
void Wolf::HPbarUpdate(std::shared_ptr<GameEngine>& ge, const int camerahandle) {
#ifdef _DEBUG
	ge->imguiAddMeshVector(
		_hpparinfo.pos,
		string("wolfuipos"),
		string("wolfuipos_x"),
		string("wolfuipos_y"),
		string("wolfuipos_z"),
		-1280,
		1280
	);
	ge->imguiAddMeshVector(
		_hpparinfo.scale,
		string("wolfuiscale"),
		string("wolfuiscale_x"),
		string("wolfuiscale_y"),
		string("wolfuiscale_z"),
		0.0f,
		10.0f
	);
#endif
	HPbarUpdateWorld();
	_hpbar->DrawUI(ge, camerahandle);
}
const Vector3& Wolf::GetPostion() {
	return _wolfPostion;
}
const Vector3& Wolf::GetScale() {
	return _wolfScale;
}
void Wolf::SetPostion(const Vector3& newpos){
	_wolfPostion = newpos;
}
void Wolf::SetScale(const Vector3& newscale) {
	_wolfScale = newscale;
}
void Wolf::PlayEatMotion() {
	_nextmotionname = "bite";
}
void Wolf::PlayWorkMotion() {
	_nextmotionname = "Work";
}
void Wolf::PlayIdleMotion() {
	_nextmotionname = "Idle";
}
void Wolf::PlayDethMotion() {
	_nextmotionname = "Deth";
}