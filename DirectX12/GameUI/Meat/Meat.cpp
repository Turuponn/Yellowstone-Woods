#include "Meat.h"
#include "GameEngine/GameEngine.h"



Meat::Meat() {
	_playanimF = false;
}
Meat::~Meat() {

}

void Meat::CreateUI(std::shared_ptr<GameEngine>& ge, const UIDATA& begindata, const UIDATA& enddata, const std::string& filepath) {
	SetUIBeginData(begindata);
	SetUIData(_begindata);
	SetUIEndData(enddata);
	
	GameUI::CreateUI(ge,filepath);
}
void Meat::DrawUI(std::shared_ptr<GameEngine>& ge,const std::string& cameraname) {
	GameUI::DrawUI(ge, _data, cameraname);
}
void Meat::SetUIData(const UIDATA& uidata) {
	_data = uidata;
}
void Meat::SetUIBeginData(const UIDATA& uidata) {
	_begindata = uidata;
}
void Meat::SetUIEndData(const UIDATA& uidata) {
	_enddata = uidata;
}
const UIDATA&  Meat::GetUIBeginData() {
	return _begindata;
}
const UIDATA& Meat::GetUIEndData() {
	return _enddata;
}
const UIDATA& Meat::GetUIData() {
	return _data;
}
void Meat::AnimationMeat(const UIDATA& data, const MEATINFO& info, bool playanimF) {
	//UIAnimation
	if (playanimF == true) {//再生するなら
		if (_data.pos.y < _enddata.pos.y) {//到達地点までアニメーションさせる
			_playanimF = true;
			_data.pos.y = _data.pos.y + info.animspeed;
		}
		else {//座標を元に戻す
			_data.pos.y = _begindata.pos.y;
			_playanimF = false;
		}
	}
}
bool Meat::GetAnimF() {
	return _playanimF;
}