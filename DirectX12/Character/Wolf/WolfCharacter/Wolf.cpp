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
	//�����p��
	data.init.axis = Vector3(1, 0, 0);
	data.init.angle = -(float)DX_PI / 2.0f;
	//�O
	data.forward.axis = Vector3(0, 1, 0);
	data.forward.angle = 0;
	//���
	data.back.axis = Vector3(0, 1, 0);
	data.back.angle = XMConvertToRadians(-180);
	//��
	data.left.axis = Vector3(0, 1, 0);
	data.left.angle = XMConvertToRadians(-90);
	//�E
	data.right.axis = Vector3(0, 1, 0);
	data.right.angle = XMConvertToRadians(90);

	//���f�����[�h
	ge->LoadFBXModelDR(modename,"resource/FBX/wolf.fbx", true);
	ge->SetFBXRotateQuaternion(modename, data.init.axis, data.init.angle);//�����p���̓���
	ge->SetFBXRotateQuaternion_mul(modename, Vector3(0, 1, 0), 0);
	_oldvec = ge->GetFBXRotateQuaternion(modename);
	_animframecount = 0;
	//�������[���h�s��
	data.worlddata = wdata;
	//�����ړ��X�s�[�h
	data.movespeed = 0.4f;
	//���ʐ��`��Ԕ}��ϐ��ψʑ��x
	data.tspeed = 0.2f;
	//�ҋ@���
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
	//�ǐ�
	Vector3 p = pointpos;
	Vector3 pw = p - data.worlddata.pos;
	pw.Normalize();
	 auto direction = pw;//����
	 data.worlddata.pos.x = data.worlddata.pos.x + (direction.x *data.movespeed);
	 data.worlddata.pos.z = data.worlddata.pos.z + (direction.z *data.movespeed);
	//�ڕW�Ɍ������ĉ�]
	auto p_axis = p - data.worlddata.pos;


	//�O����������]�s�񂩂�N�E�H�[�^�j�I�������
	XMVECTOR U = { 0,1,0 };//��(����)�x�N�g�� �L�����̎�
	XMVECTOR zw = { p_axis.x,1.0f,p_axis.z };
	zw = XMVector3Normalize(zw);
	XMVECTOR xw = XMVector3Cross(U, zw);//�����ȃx�N�g�������߂�
	xw = XMVector3Normalize(xw);
	XMVECTOR yw = XMVector3Cross(zw, xw);
	yw = XMVector3Normalize(yw);

	XMFLOAT3 z1 = {};
	XMFLOAT3 x1 = {};
	XMFLOAT3 y1 = {};
	XMStoreFloat3(&z1, zw);
	XMStoreFloat3(&x1, xw);
	XMStoreFloat3(&y1, yw);

	//�w��_ P�@�����
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
	ge->SetFBXRotateQuaternion(modename, data.init.axis, data.init.angle);//�����p��
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

	//���G
	auto dis = Character::GetEntiy()->Distance(targetpos, Vector3(0,0,0));
	if (dis < DISHANTMAX) {//�n���g���[�h��
		_updateAIFunc = &Wolf::AIHunt;
		if (dis < DISEATMAX) {//�H�ׂ郂�[�h��
			_updateAIFunc = &Wolf::AIEat;
		}
	}
	else {//�ҋ@���[�h��
		_updateAIFunc = &Wolf::AIIdle;
	}
}
void Wolf::AIIdle(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Wolf::PlayIdleMotion;//�ҋ@���[�V����
}
void Wolf::AIHunt(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Wolf::PlayWorkMotion;
	MoveApproach(ge,targetpos);//�ǐ�
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