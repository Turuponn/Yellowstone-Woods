#include "Wolf.h"
#include "constance.h"
#include "GameEngine/GameEngine.h"
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
	_fbxhandle = ge->LoadFBXModelDR("resource/FBX/wolf.fbx", false);
	ge->SetFBXRotateQuaternion(_fbxhandle, _winit.axis, _winit.angle);//初期姿勢の入力
	ge->SetFBXRotateQuaternion_mul(_fbxhandle, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);

	_wolfScale = Vector3(1, 1, 1);

}
void Wolf::Update(std::shared_ptr<GameEngine>& ge) {

	ge->SetFBXPostionQuaternion(_fbxhandle, _wolfPostion+ _wolfPosOffset);
	ge->SetFBXScaleQuaternion(_fbxhandle, _wolfScale);
	ge->DrawFBXModelDR(_fbxhandle);

#ifdef _DEBUG
	ge->imguiAddMeshVector(_wolfPostion, string("wolfpos"), string("wolfpos_x"), string("wolfpos_y"), string("wolfpos_z"), -50.0f, 50.0f);
#endif
}