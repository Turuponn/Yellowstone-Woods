#include "GameUI.h"
#include "GameEngine/GameEngine.h"
using namespace std;


GameUI::GameUI() {
	_uihandle = 0;

}
GameUI::~GameUI() {
	
}
void GameUI::UpdateInfo(std::shared_ptr<GameEngine>& ge,const UIDATA& data) {
	Vector3 newpos = {};
	newpos = data.pos;
	newpos.y= -data.pos.y;
	ge->SetPosUI(_uihandle, newpos);
	ge->SetScaleUI(_uihandle, data.scale);
	ge->SetRotateUI(_uihandle, data.rotate);
	ge->SetRotateOriginUI(_uihandle, data.rotateorigin);
	ge->SetColorUI(_uihandle, data.color);
}
void GameUI::CreateUI(std::shared_ptr<GameEngine>& ge, const std::string& filepath) {
	_uihandle = ge->CreateRECTUIHandle(filepath);
}
void GameUI::DrawUI(std::shared_ptr<GameEngine>& ge, const UIDATA& data,const std::string& cameraname) {
	UpdateInfo(ge, data);//XV
	ge->DrawRECTUI(_uihandle, cameraname);
}