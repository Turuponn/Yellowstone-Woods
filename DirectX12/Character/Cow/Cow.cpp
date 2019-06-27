#include "Cow.h"
#include "constance.h"
#include "GameEngine/GameEngine.h"
using namespace DirectX;
using namespace std;


Cow::Cow() {
	_fbxhandle = 0;
}
Cow::~Cow() {

}
void Cow::Initialize(std::shared_ptr<GameEngine>& ge) {
	//初期姿勢
	_cowinit.axis = Vector3(1, 0, 0);
	_cowinit.angle = -(float)DX_PI / 2.0f;
	//前
	_cowforward.axis = Vector3(0, 1, 0);
	_cowforward.angle = 0;
	//後ろ
	_cowback.axis = Vector3(0, 1, 0);
	_cowback.angle = XMConvertToRadians(-180);
	//左
	_cowleft.axis = Vector3(0, 1, 0);
	_cowleft.angle = XMConvertToRadians(-90);
	//右
	_cowright.axis = Vector3(0, 1, 0);
	_cowright.angle = XMConvertToRadians(90);
	//モデルロード
	_fbxhandle = ge->LoadFBXModelDR("resource/FBX/Cow.fbx", true);
	ge->SetFBXRotateQuaternion(_fbxhandle, _cowinit.axis, _cowinit.angle);//初期姿勢の入力
	ge->SetFBXRotateQuaternion_mul(_fbxhandle, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
	//初期拡縮値
	_cowScale = Vector3(3, 3, 3);
	//初期座標
	_cowPostion = Vector3(0, GROUNDPOS_Y+ _cowScale.y, 0);
	//初期フレーム値
	_animframecount = 0;
}
void Cow::Update(std::shared_ptr<GameEngine>& ge) {
	
	ge->SetFBXPostionQuaternion(_fbxhandle, _cowPostion + _cowPosOffset);
	ge->SetFBXScaleQuaternion(_fbxhandle, _cowScale);
	
	auto endanimpos = ge->GetAnimFrameEndPos(_fbxhandle, "Idle");
	_animframecount = (_animframecount + 1) % endanimpos;
	ge->FBXAnimationPlay(_fbxhandle, "Idle", _animframecount);

	ge->DrawFBXModelDR(_fbxhandle);


	
#ifdef _DEBUG
	ge->imguiAddMeshVector(_cowPostion, string("cowpos"), string("cowpos_x"), string("cowpos_y"), string("cowpos_z"), -50.0f, 50.0f);
#endif
}
const Vector3& Cow::GetPostion(){
	return _cowPostion;
}

const Vector3& Cow::GetScale() {
	return _cowScale;
}
void Cow::SetPostion(const Vector3& newpos) {
	_cowPostion = newpos;
}
void Cow::SetScale(const Vector3& newscale) {
	_cowScale = newscale;
}
