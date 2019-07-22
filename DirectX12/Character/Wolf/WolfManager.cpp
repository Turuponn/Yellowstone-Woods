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
	const int DISEATMAX = 5;//食べるまでの必要距離
	const int DISHANTMAX = 50;//索敵範囲
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
	//UI: hpbar　
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
	


	//UI: 肉
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
	_meateatuianimF = false;//非表示
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

	//HPをフレームで減少させる
	_hpframetime++;
	if (_info._hpframetimelimit < _hpframetime) {
		_hpframetime = 0;
		hp = hp - 1;
		if (hp < 0) {//三項を使った方法だと挙動がおかしくなるためこちらにする
			hp = 0;
		}
	}
	//お肉を食べたら回復する
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
	_meateatuianimF = _meat->GetAnimF();//アニメーション終了の知らせをもらいます

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
	//肉
	MeatUpdate(ge);


	//描画
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

	//一番近い、生きている牛を探索
	auto index = cowmanager->GetNearCow(_wolf->GetWorldPos());
	if (index != INITINDEX) {
		if (_nearcowindex == INITINDEX) {//初期化
			_nearcowindex = index;
		}
		auto dis = _wolf->GetEntity()->Distance(Vector3(0, 0, 0), cowmanager->GetWorldPos(_nearcowindex));
		if (cowmanager->GetDeath(_nearcowindex) == false ||  DISHANTMAX < dis) {//死んでいた場合または、対象が索敵範囲を超えていた場合、中心から近い敵に索敵更新
			_nearcowindex = index;
			if (_meateatuianimF == false) {
				_eatdeathMeatRecoveryF = true;
				_meateatuianimF = true;
			}
		}
	}
	else {//探索終了した場合最後のindexを使用する

	}

	_wolf->AIUpdate(ge, cowmanager->GetWorldPos(_nearcowindex), DISHANTMAX, DISEATMAX);//追跡開始


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