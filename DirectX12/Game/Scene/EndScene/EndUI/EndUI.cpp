#include "EndUI.h"
#include "constance.h"
#include "GameUI/UIDefault/UIDefault.h"
#include "GameEngine/GameEngine.h"
using namespace std;
namespace {
	const string pleasepushFilepath = "resource/Texture/title/pleasepushspacekey.png";

	const int screensize_x = SCREEN_SIZE_X;
	const int screensize_y = SCREEN_SIZE_Y;
}

EndUI::EndUI() {

}
EndUI::~EndUI() {

}
void EndUI::InsartPtrMaps(std::shared_ptr<GameEngine>& ge, const std::string& filepath, const std::string& item) {
	std::shared_ptr<UIDefault> t(new UIDefault());
	UIDATA titleui = {};
	t->Create(ge, titleui, filepath);
	_uimap.insert(std::make_pair(item, t));
}
void EndUI::Init(std::shared_ptr<GameEngine>& ge) {
	//ui:InitData
	InsartPtrMaps(ge, pleasepushFilepath, "スペースキーを押してください");



	//ui:InitParam
	auto ui = _uimap.at("スペースキーを押してください");
	if (ui != nullptr) {
		UIDATA p = {};
		p.pos = { (float)screensize_x / 2,(float)screensize_y / 2,0 };
		p.scale = { 0.4,0.09,1 };
		ui->SetData(p);
		std::shared_ptr<UIDATA> d(new UIDATA());
		_debugdata = d;
		*_debugdata = p;
	}


}
void EndUI::Draw(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	//ui: Input
	CursorUpdate(ge);


	//ui: Draw
	auto ui = _uimap.at("スペースキーを押してください");
	if (ui != nullptr) {
		ui->Draw(ge, cameraname);
	}


}
#pragma region Cursor
void EndUI::CursorInput(std::shared_ptr<GameEngine>& ge) {
	if (ge->CheckHitKey(DIK_UP)) {

	}
	if (ge->CheckHitKey(DIK_DOWN)) {

	}
	if (ge->CheckHitKey(DIK_RIGHT)) {

	}
	if (ge->CheckHitKey(DIK_LEFT)) {

	}
	
	
}
void EndUI::CursorUpdate(std::shared_ptr<GameEngine>& ge) {
	CursorInput(ge);
}
#pragma endregion
