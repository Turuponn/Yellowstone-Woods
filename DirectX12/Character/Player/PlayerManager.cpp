#include "PlayerManager.h"
#include  "PlayerCharacter/Player.h"
#include "GameEngine/GameEngine.h"
#include "GameUI/HPbar/HPbar.h"
#include "GameUI/ICON/ICON.h"
#include "GameUI/Meat/Meat.h"
#include "Character/Wolf/WolfManager.h"
#include "constance.h"
using namespace std;

namespace {
	const float MAXHP = 100;

}

PlayerManager::PlayerManager() {
	_hpframetime = 0;
	
}
PlayerManager::~PlayerManager() {
	
}
void PlayerManager::UIInitialize(std::shared_ptr<GameEngine>& ge) {
	
	//UI: hpbar　
	std::shared_ptr<HPbar> hpbar(new HPbar());
	_hpbar = hpbar;
	UIDATA hpdefaultdata = {};
	hpdefaultdata.pos = { 350,654,0 };
	hpdefaultdata.scale = { 0.15,0.15,1 };
	_hpbar->CreateUI(ge, hpdefaultdata, "resource/Texture/CharacterHPbar/HPbar.png");
	

	//UI: hpbarFrame
	std::shared_ptr<HPbar> hpbarframe(new HPbar());
	_hpbarframe = hpbarframe;
	UIDATA hpframedefaultdata = {};
	hpframedefaultdata.pos = { 350 / 2,654,0 };
	hpframedefaultdata.scale = { 0.15,0.15,1 };
	_hpbarframe->CreateUI(ge, hpframedefaultdata, "resource/Texture/CharacterHPbar/HPbarFrame.png");



	//UI: ICON
	std::shared_ptr<ICON> icon(new ICON());
	_icon = icon;
	UIDATA icondata = {};
	icondata.pos = { (350 / 2) - 140,654,0 };
	icondata.scale = { 0.03,0.07,1 };
	_icon->CreateUI(ge, icondata,"resource/Texture/Character/Crow/bird_karasu_kowai.png");
	


	//UI:　肉
	std::shared_ptr<Meat> meat(new Meat());
	_meathalf = meat;
	std::shared_ptr<UIDATA> dmeathalfbegindata(new UIDATA());
	_debugmeathalfbegindata = dmeathalfbegindata;
	_debugmeathalfbegindata->pos = { 169,550,0 };
	_debugmeathalfbegindata->scale = { 0.1f,0.1f,1 };
	std::shared_ptr<UIDATA> dmeathalfenddata(new UIDATA());
	_debugmeathalfenddata = dmeathalfenddata;
	_debugmeathalfenddata->pos = { 169,645,0 };
	_debugmeathalfenddata->scale = { 0.1f,0.1f,1 };
	_meathalf->CreateUI(ge, *_debugmeathalfbegindata, *_debugmeathalfenddata, "resource/Texture/niku/manga_niku_half.png");
	_meateatuianimF = false;

}
void PlayerManager::ModelInitialize(std::shared_ptr<GameEngine>& ge) {
	//Model
	std::shared_ptr<Player> p(new Player());
	_player = p;
	WORLDDATA wdata = {};
	wdata.pos = { 0,GROUNDPOS_Y + 5,0 };//初期リスポーン位置
	wdata.scale = { 1,1,1 };
	wdata.rotate = { 0,0,0 };
	CHARACTERPARAMETERDATA paramdata = {};
	paramdata.hp = MAXHP;
	_player->Initialize(ge, wdata, paramdata);
}
void PlayerManager::Initialize(std::shared_ptr<GameEngine>& ge, const PLAYERINITINFO& sceneplayerinitinfo) {
	_info = sceneplayerinitinfo;
	ModelInitialize(ge);
	UIInitialize(ge);

}

void PlayerManager::Update(std::shared_ptr<GameEngine>& ge,std::shared_ptr<WolfManager>& wolf, const std::string& cameraname) {
	//UI
	UIUpdate(ge,wolf, cameraname);
	//Model
	_player->Update(ge, cameraname);
}
#pragma region UI


void PlayerManager::HPbarHPUpdate(std::shared_ptr<GameEngine>& ge) {
	HPINFO info = {};
	info.maxhp = MAXHP;
	info.hp = _player->GetHP();
	_hpbar->ReduceUpdate(ge, info);
}
void PlayerManager::MeatUpdate(std::shared_ptr<GameEngine>& ge) {
	auto data = _meathalf->GetUIData();
	MEATINFO info = {};
	info.animspeed = 5;
	_meathalf->AnimationMeat(data, info, _meateatuianimF);
	_meateatuianimF= _meathalf->GetAnimF();//アニメーション終了の知らせをもらいます

#ifdef _DEBUG

	ge->imguiAddMeshVector3(
		_debugmeathalfenddata->pos,
		string("phalfmeatpos"),
		string("phalfmeatpos_x"),
		string("phalfmeatpos_y"),
		string("phalfmeatpos_z"),
		-50.0f, 50.0f);
	_meathalf->SetUIEndData(*_debugmeathalfenddata);
#endif
	
}
void PlayerManager::HPUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf) {
	int hp = _player->GetHP();
	//HPをフレームで減少させる
	_hpframetime++;
	if (_info._hpframetimelimit < _hpframetime) {
		_hpframetime = 0;
		hp = hp - 1;
		if (hp < 0) {//三項を使った方法だと挙動がおかしくなるためこちらにする
			hp = 0;
		}
	}

	//お肉を食べていたらプレイヤーも回復する
	if (wolf->GetEatDeathMeatRecoveryF() == true) {
		if (_meateatuianimF == false) {//食べているのでUIのアニメーションを再生させる
			_meateatuianimF = true;
		}
		hp = (hp + _info._hpRecovery);
		if (hp > MAXHP) {
			hp = MAXHP;
		}
	}

	_player->SetHP(hp);

}
void PlayerManager::UIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf,const std::string& cameraname) {
	//HP
	HPUpdate(ge, wolf);
	HPbarHPUpdate(ge);
	//肉
	MeatUpdate(ge);


	//描画
	_hpbarframe->DrawUI(ge, cameraname);
	_hpbar->DrawUI(ge, cameraname);
	_icon->DrawUI(ge, cameraname);
	if (_meateatuianimF == true) {//表示させる
		_meathalf->DrawUI(ge, cameraname);
	}
}
#pragma endregion
void PlayerManager::LookAt(std::shared_ptr<GameEngine>& ge, const Vector3& lookpoint) {
	_player->InputCry(ge);
	_player->Approachforward(ge,lookpoint);
}
const Vector3& PlayerManager::GetWorldPos() {
	return _player->GetWorldPos();
}
bool PlayerManager::GetPushShoutF() {
	return _player->GetPushShout();
}
float PlayerManager::GetHP() {
	return _player->GetHP();
}