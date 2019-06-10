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
	//�����p��
	_winit.axis = Vector3(1, 0, 0);
	_winit.angle = -(float)DX_PI / 2.0f;
	//�O
	_wforward.axis = Vector3(0, 1, 0);
	_wforward.angle = 0;
	//���
	_wback.axis = Vector3(0, 1, 0);
	_wback.angle = XMConvertToRadians(-180);
	//��
	_wleft.axis = Vector3(0, 1, 0);
	_wleft.angle = XMConvertToRadians(-90);
	//�E
	_wright.axis = Vector3(0, 1, 0);
	_wright.angle = XMConvertToRadians(90);

	//���f�����[�h
	_fbxhandle = ge->LoadFBXModelDR("resource/FBX/wolf.fbx", false);
	ge->SetFBXRotateQuaternion(_fbxhandle, _winit.axis, _winit.angle);//�����p���̓���
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