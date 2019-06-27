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
	//�����p��
	_cowinit.axis = Vector3(1, 0, 0);
	_cowinit.angle = -(float)DX_PI / 2.0f;
	//�O
	_cowforward.axis = Vector3(0, 1, 0);
	_cowforward.angle = 0;
	//���
	_cowback.axis = Vector3(0, 1, 0);
	_cowback.angle = XMConvertToRadians(-180);
	//��
	_cowleft.axis = Vector3(0, 1, 0);
	_cowleft.angle = XMConvertToRadians(-90);
	//�E
	_cowright.axis = Vector3(0, 1, 0);
	_cowright.angle = XMConvertToRadians(90);
	//���f�����[�h
	_fbxhandle = ge->LoadFBXModelDR("resource/FBX/Cow.fbx", true);
	ge->SetFBXRotateQuaternion(_fbxhandle, _cowinit.axis, _cowinit.angle);//�����p���̓���
	ge->SetFBXRotateQuaternion_mul(_fbxhandle, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(_fbxhandle);
	//�����g�k�l
	_cowScale = Vector3(3, 3, 3);
	//�������W
	_cowPostion = Vector3(0, GROUNDPOS_Y+ _cowScale.y, 0);
	//�����t���[���l
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
