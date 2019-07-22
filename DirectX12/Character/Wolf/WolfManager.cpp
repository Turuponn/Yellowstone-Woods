#include "WolfManager.h"
#include "GameEngine/GameEngine.h"
#include "Character/Wolf/WolfCharacter/Wolf.h"
#include "Character/Cow/CowManager.h"
#include "Entity/Entity.h"
#include "GameUI/HPbar/HPbar.h"
#include "GameUI/ICON/ICON.h"
#include "GameUI/Meat/Meat.h"
#include "constance.h"
using namespace std;

namespace {
	const int INITINDEX = -1;
	const int DISEATMAX = 5;//�H�ׂ�܂ł̕K�v����
	const int DISHANTMAX = 50;//���G�͈�
	const int MAXHP = 100;
}


WolfManager::WolfManager() {
	_nearcowindex = INITINDEX;
	_hpframetime = 0;
}
WolfManager::~WolfManager() {
	
}
void WolfManager::ModelInitialize(std::shared_ptr<GameEngine>& ge) {
	std::shared_ptr<Wolf> wolf(new Wolf());
	_wolf = wolf;
	WORLDDATA data = {};
	data.rotate = { 0,0,0 };
	data.scale = Vector3(2, 2, 2);
	data.pos = Vector3(-50, GROUNDPOS_Y + data.scale.y, 0);
	CHARACTERPARAMETERDATA paramdata = {};
	paramdata.hp = MAXHP;
	_wolf->Initialize(ge, data, paramdata);
}
void WolfManager::UIInitialize(std::shared_ptr<GameEngine>& ge) {
	//UI: hpbar�@
	std::shared_ptr<HPbar> hpbar(new HPbar());
	_hpbar = hpbar;
	UIDATA hpuidata = {};
	hpuidata.pos = { 350,510,0 };
	hpuidata.scale = { 0.1,0.1,1 };
	_hpbar->CreateUI(ge, hpuidata, "resource/Texture/CharacterHPbar/HPbar.png");
	_eatdeathMeatRecoveryF = false;



	//UI: hpframe
	std::shared_ptr<HPbar> hpbarframe(new HPbar());
	_hpbarframe = hpbarframe;
	UIDATA hpbarframeddata = {};
	hpbarframeddata.pos = { 350 / 2,510,0 };
	hpbarframeddata.scale = { 0.1,0.1,1 };
	_hpbarframe->CreateUI(ge, hpbarframeddata, "resource/Texture/CharacterHPbar/HPbarFrame.png");



	//UI: icon
	std::shared_ptr<ICON>	icon(new ICON());
	_icon = icon;
	UIDATA icondata = {};
	icondata.pos = { 74,496,0 };
	icondata.scale = { 0.03,0.07,1 };
	_icon->CreateUI(ge, icondata, "resource/Texture/Character/Wolf/animal_ookami.png");
	


	//UI: ��
	std::shared_ptr <Meat> meat(new Meat());
	std::shared_ptr <UIDATA> debugBeginmeatuidata(new UIDATA());
	std::shared_ptr <UIDATA> debugEndmeatuidata(new UIDATA());
	_debugBeginmeatuidata  = debugBeginmeatuidata;
	_debugEndmeatuidata = debugEndmeatuidata;
	_meat = meat;
	_debugBeginmeatuidata->pos = { 169, 413, 0 };
	_debugBeginmeatuidata->scale = { 0.1,0.1,1 };
	_debugEndmeatuidata->pos = { 169, 508, 0 };
	_debugEndmeatuidata->scale = { 0.1,0.1,1 };
	_meat->CreateUI(ge, *_debugBeginmeatuidata, *_debugEndmeatuidata,"resource/Texture/niku/manga_niku.png");
	_meateatuianimF = false;//��\��
}
void WolfManager::Initialize(std::shared_ptr<GameEngine>& ge, const WOLFINITINFO& scenewolfinitinfo) {
	_info = scenewolfinitinfo;
	ModelInitialize(ge);
	UIInitialize(ge);
}
void WolfManager::Update(std::shared_ptr<GameEngine>& ge,const std::string& cameraname) {
	//UI
	UIUpdate(ge, cameraname);
	//Model
	_wolf->Update(ge, cameraname);
}
#pragma region UI
void WolfManager::HPUpdate(std::shared_ptr<GameEngine>& ge) {
	int hp = _wolf->GetHP();

	//HP���t���[���Ō���������
	_hpframetime++;
	if (_info._hpframetimelimit < _hpframetime) {
		_hpframetime = 0;
		hp = hp - 1;
		if (hp < 0) {//�O�����g�������@���Ƌ��������������Ȃ邽�߂�����ɂ���
			hp = 0;
		}
	}
	//������H�ׂ���񕜂���
	if (_eatdeathMeatRecoveryF == true) {
		hp = (hp + _info._hpRecovery);
		if (hp > MAXHP) {
			hp = MAXHP;
		}
		_eatdeathMeatRecoveryF = false;
	}
	_wolf->SetHP(hp);

}
void WolfManager::HPbarHPUpdate(std::shared_ptr<GameEngine>& ge) {
	HPINFO info = {};
	info.hp = _wolf->GetHP();
	info.maxhp = MAXHP;
	_hpbar->ReduceUpdate(ge, info);
}
void WolfManager::MeatUpdate(std::shared_ptr<GameEngine>& ge) {
	auto data = _meat->GetUIData();
	MEATINFO info = {};
	info.animspeed = 5;
	_meat->AnimationMeat(data, info, _meateatuianimF);
	_meateatuianimF = _meat->GetAnimF();//�A�j���[�V�����I���̒m�点�����炢�܂�

#ifdef _DEBUG

	ge->imguiAddMeshVector3(
		_debugEndmeatuidata->pos,
		string("wmeatpos"),
		string("wmeatpos_x"),
		string("wmeatpos_y"),
		string("wmeatpos_z"),
		-50.0f, 50.0f);
	_meat->SetUIEndData(*_debugEndmeatuidata);
#endif
}
void WolfManager::UIUpdate(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	//HP
	HPUpdate(ge);
	HPbarHPUpdate(ge);
	//��
	MeatUpdate(ge);


	//�`��
	_hpbarframe->DrawUI(ge, cameraname);
	_hpbar->DrawUI(ge, cameraname);
	_icon->DrawUI(ge, cameraname);
	if (_meateatuianimF == true) {
		_meat->DrawUI(ge, cameraname);
	}
}
#pragma endregion
#pragma region AI
void WolfManager::AIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<CowManager>& cowmanager) {

	//��ԋ߂��A�����Ă��鋍��T��
	auto index = cowmanager->GetNearCow(_wolf->GetWorldPos());
	if (index != INITINDEX) {
		if (_nearcowindex == INITINDEX) {//������
			_nearcowindex = index;
		}
		auto dis = _wolf->GetEntity()->Distance(Vector3(0, 0, 0), cowmanager->GetWorldPos(_nearcowindex));
		if (cowmanager->GetDeath(_nearcowindex) == false ||  DISHANTMAX < dis) {//����ł����ꍇ�܂��́A�Ώۂ����G�͈͂𒴂��Ă����ꍇ�A���S����߂��G�ɍ��G�X�V
			_nearcowindex = index;
			if (_meateatuianimF == false) {
				_eatdeathMeatRecoveryF = true;
				_meateatuianimF = true;
			}
		}
	}
	else {//�T���I�������ꍇ�Ō��index���g�p����

	}

	_wolf->AIUpdate(ge, cowmanager->GetWorldPos(_nearcowindex), DISHANTMAX, DISEATMAX);//�ǐՊJ�n


}
#pragma endregion
const Vector3& WolfManager::GetWorldPos() {
	return _wolf->GetWorldPos();
}
bool WolfManager::GetEatDeathMeatRecoveryF() {
	return _eatdeathMeatRecoveryF;
}
float WolfManager::GetHP() {
	return _wolf->GetHP();
}