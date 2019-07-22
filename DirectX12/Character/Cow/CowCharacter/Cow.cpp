#include "Cow.h"
#include "constance.h"
#include "GameEngine/GameEngine.h"
#include "Entity/Entity.h"
using namespace DirectX;
using namespace std;

namespace {
	const int FRAMETIMECOUNTMAX = 1;
	const float MAXPOSDIS = 50;//���S����ǂꂭ�炢���ꂽ�ʒu����o�����邩�p�萔


}

Cow::Cow() {
	_alivecount = 0;
	_randposFrame.frameCount = 0;
	_randposFrame.frameTime = 0;
	_characterFadeFrame.frameCount = 0;
	_characterFadeFrame.frameTime = 0;
	_randtargetpos.randX = 0;
	_randtargetpos.randZ = 0;
	_initrandpackage.frametimecountmax = 0;
}
Cow::~Cow() {

}
void Cow::Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata,const std::string& modelname) {
	//�����p��
	CHARACTERDATA data = {};
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
	ge->LoadFBXModelDR(modelname,"resource/FBX/Cow.fbx", true);
	ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);//�����p���̓���
	//�����_���Ŏp����ς���
	auto r = ge->GetRandIntRengeMt(0, 3);
	auto axis = data.forward.axis;
	auto angle = data.forward.angle;
	if (r == 0) {
		axis = data.back.axis;
		angle = data.back.angle;
	}
	if (r == 1) {
		axis = data.left.axis;
		angle = data.left.angle;
	}
	if (r == 2) {
		axis = data.right.axis;
		angle = data.right.angle;
	}
	ge->SetFBXRotateQuaternion_mul(modelname, axis, angle);
	_oldvec = ge->GetFBXRotateQuaternion(modelname);
	//����animation
	_updateAnimationFunc = &Cow::PlayIdleMotion;
	//�������[���h�s��
	data.worlddata = wdata;
	//�����t���[���l
	_animframecount = 0;
	//�����ړ��X�s�[�h
	data.movespeed = 0.3f;
	//���ʐ��`��Ԕ}��ϐ��ψʑ��x
	data.tspeed = 0.2f;
	//�A�j���[�V��������Ɏg�p����
	_animationstopF = true;
	//�ҋ@
	_updateAIFunc = &Cow::AIIdle;
	//�����Ă��邪�����͋�����Ă��炸���ł��Ă��Ȃ����
	_fadeF = false;
	Character::SetCharacterParameterData(cdata);
	Character::SetCharacterData(data);
}
void Cow::EscapeUpdate(std::shared_ptr<GameEngine>& ge,const int ESCAPEDIS) {
	auto data = Character::GetCharacterData();
	//���S����ǂꂭ�炢���ꂽ���A������x����Ă���ΐ�����΂�
	auto discenter = Character::GetEntiy()->Distance(Vector3(0, 0, 0), data.worlddata.pos);
	if (ESCAPEDIS < discenter) {//����Ă���ꍇ�@��΂�
		_updateAIFunc = &Cow::AIEscape;
	}
	
}
void Cow::Update(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const int ESCAPEDIS, const RANDPACKAGE& randpackage) {
	_initrandpackage = randpackage;
	//ModelUpdate
	ge->SetFBXPostionQuaternion(modelname, Character::GetCharacterData().worlddata.pos);
	ge->SetFBXScaleQuaternion(modelname, Character::GetCharacterData().worlddata.scale);
	//Animation
	UpdateAnimation(modelname,ge);
	//EscapeJudgment
	EscapeUpdate(ge, ESCAPEDIS);
	//Draw
	ge->DrawFBXModelDR(modelname);


	
#ifdef _DEBUG
	 auto pos = Character::GetCharacterData().worlddata.pos;
	ge->imguiAddMeshVector3(pos, string("cowpos"), string("cowpos_x"), string("cowpos_y"), string("cowpos_z"), -50.0f, 50.0f);
#endif
}
void Cow::UpdateAnimation(const std::string& modelname,std::shared_ptr<GameEngine>& ge) {
	(this->*_updateAnimationFunc)();//UpdateAnimation
	auto endanimpos = ge->GetAnimFrameEndPos(modelname, _nextmotionname);
	if (_animationstopF == true) {//��������̗��R�ŃX�g�b�v������ꍇ
		_animframecount = (_animframecount + 1) % endanimpos;
	}
	else {//�X�g�b�v������
		_animframecount = _animframecount >= endanimpos ? endanimpos : (_animframecount + 1);
		
	}
	ge->FBXAnimationPlay(modelname, _nextmotionname, _animframecount);
#ifdef _DEBUG
	ge->imguiAddMeshInt(_animframecount, string("animcount"), string("cout"), 0, 50);
#endif
}
void Cow::MoveApproachforward(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& pointpos) {
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

	_oldvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);//�����p��
	ge->SetFBXRotateQuaternion_mul(modelname, data.forward.axis, data.forward.angle);
	ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
	auto newvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);

	Character::SetCharacterData(data);
}

bool Cow::GetCowDeathF() {
	return Character::GetDeathF();
}
void Cow::MoveApproachback(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& pointpos) {
	auto data = Character::GetCharacterData();
	//�ǐ�
	Vector3 p = pointpos;
	Vector3 pw = p - data.worlddata.pos;
	pw.Normalize();
	auto direction = pw;//����
	data.worlddata.pos.x = data.worlddata.pos.x - (direction.x *data.movespeed);
	data.worlddata.pos.z = data.worlddata.pos.z - (direction.z *data.movespeed);
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

	_oldvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion(modelname, data.init.axis, data.init.angle);//�����p��
	ge->SetFBXRotateQuaternion_mul(modelname, data.back.axis, data.back.angle);
	ge->SetFBXRotateQuaternion_Matrix(modelname, pout);
	auto newvec = ge->GetFBXRotateQuaternion(modelname);
	ge->SetFBXRotateQuaternion_Slerp(modelname, _oldvec, newvec, data.tspeed);

	Character::SetCharacterData(data);
}
const Vector3& Cow::GetWorldPos() {
	return Character::GetCharacterData().worlddata.pos;
}

#pragma region AI
void Cow::AIUpdate(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos,const int DISRUNMAX,const int DISMOVEMAX,const int DISDEATHMAX) {
	(this->*_updateAIFunc)(modelname,ge, targetpos);
	auto data = Character::GetCharacterData();
	_updateAIFunc = &Cow::AIIdle;//�ҋ@

	//��ԑJ��
	if (Character::GetDeathF()) {//�����Ă�����

		
		//�t���[���^�C�}�[��ݒ肵�A�����_���Ȓl���擾����
		++_randposFrame.frameTime;
		if (_randposFrame.frameTime > 60) {
			_randposFrame.frameTime = 0;
			++_randposFrame.frameCount;
		}
	
		if (FRAMETIMECOUNTMAX < _randposFrame.frameCount) {
			_randtargetpos.randX = ge->GetRandFloatRengeMt(-(MAXPOSDIS-10), MAXPOSDIS-10);//-10���đ����E�������
			_randtargetpos.randZ = ge->GetRandFloatRengeMt(-(MAXPOSDIS-10), MAXPOSDIS-10);
			_randposFrame.frameCount = 0;
		}
		

		//�G�ɂ�����x�ڋ߂��ꂽ��
		auto dis = Character::GetEntiy()->Distance(targetpos, data.worlddata.pos);
		if (dis < DISRUNMAX) {//�����ɐ؂�ւ�
			_updateAIFunc = &Cow::AIRun;
			if (dis < DISDEATHMAX) {//�H�ׂ�ꂽ
				_updateAIFunc = &Cow::AIDeath;//���S
			}
		}
		else {
			//�ʏ�̋����A�a�����ߒ��S�����ړ�����
			auto discenter = Character::GetEntiy()->Distance(//���a���������_���ȏꏊ��ڎw���悤�Ɂ@���t���[���܂���n�t���[�����ƂɍX�V�ł�����
				Vector3(
					_randtargetpos.randX,
					1,//�X�^�b�N������������邽�߂�+����
					_randtargetpos.randZ),
				data.worlddata.pos
			);
			if (discenter > DISMOVEMAX) {
				_updateAIFunc = &Cow::AIMove;
			}
		}
	}
	else {//����ł���
		_updateAIFunc = &Cow::AIEscape;//���݂�����
	}
}

void Cow::AIIdle(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Cow::PlayIdleMotion;//�ҋ@

}
void Cow::AIRun(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Cow::PlayWorkMotion;//������
	MoveApproachback(modelname,ge, targetpos);//������
}
void Cow::AIMove(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_updateAnimationFunc = &Cow::PlayWorkMotion;//������
	MoveApproachforward(modelname,ge, Vector3(_randtargetpos.randX, 1, _randtargetpos.randZ));
}
void Cow::AIDeath(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	_animationstopF = false;//Animation Stop
	Character::SetDeathF(false);//���S
	_updateAnimationFunc = &Cow::PlayDeathMotion;
}
void Cow::AIEscape(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos) {
	auto data = Character::GetCharacterData();
	data.worlddata.pos.x = 99999;
	data.worlddata.pos.z = 99999;
	_characterFadeFrame.frameTime++;
	if (_characterFadeFrame.frameTime > 60) {
		_characterFadeFrame.frameTime = 0;
		_characterFadeFrame.frameCount++;
	}
	if (_characterFadeFrame.frameCount > _initrandpackage.frametimecountmax) {//�w��t���[���҂��A���ł�����
		_animationstopF = true;//Animation Play
		Character::SetDeathF(true);//����
		data.worlddata.pos = _initrandpackage.randpos;
		data.worlddata.scale = _initrandpackage.randscale;
		_characterFadeFrame.frameCount = 0;
		_characterFadeFrame.frameTime = 0;
	}
	Character::SetCharacterData(data);
}
#pragma endregion

#pragma region Animation
void Cow::PlayWorkMotion() {
	_nextmotionname = "Work";
}
void Cow::PlayIdleMotion() {
	_nextmotionname = "Idle";
}
void Cow::PlayDeathMotion() {
	_nextmotionname = "Deth";//TODO:
}
#pragma endregion
