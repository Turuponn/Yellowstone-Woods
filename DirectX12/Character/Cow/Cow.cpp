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
	//‰ŠúŽp¨
	_cowinit.axis = Vector3(1, 0, 0);
	_cowinit.angle = -(float)DX_PI / 2.0f;
	//‘O
	_cowforward.axis = Vector3(0, 1, 0);
	_cowforward.angle = 0;
	//Œã‚ë
	_cowback.axis = Vector3(0, 1, 0);
	_cowback.angle = XMConvertToRadians(-180);
	//¶
	_cowleft.axis = Vector3(0, 1, 0);
	_cowleft.angle = XMConvertToRadians(-90);
	//‰E
	_cowright.axis = Vector3(0, 1, 0);
	_cowright.angle = XMConvertToRadians(90);



	_fbxhandle = ge->LoadFBXModelDR("resource/FBX/Cow_static.fbx", false);
	ge->SetFBXRotateQuaternion(_fbxhandle, _cowinit.axis, _cowinit.angle);//‰ŠúŽp¨‚Ì“ü—Í
	ge->SetFBXRotateQuaternion_mul(_fbxhandle, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);

	_cowScale = Vector3(1, 1, 1);
}
void Cow::Update(std::shared_ptr<GameEngine>& ge) {

	ge->SetFBXPostionQuaternion(_fbxhandle, _cowPostion + _cowPosOffset);
	ge->SetFBXScaleQuaternion(_fbxhandle, _cowScale);
	ge->DrawFBXModelDR(_fbxhandle);
#ifdef _DEBUG
	ge->imguiAddMeshVector(_cowPostion, string("cowpos"), string("cowpos_x"), string("cowpos_y"), string("cowpos_z"), -50.0f, 50.0f);
#endif
}