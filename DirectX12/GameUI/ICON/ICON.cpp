#include "ICON.h"
#include "GameEngine/GameEngine.h"


ICON::ICON() {

}
ICON::~ICON() {

}

void ICON::CreateUI(std::shared_ptr<GameEngine>& ge, const UIDATA& uidata, const std::string& filepath) {
	SetUIData(uidata);
	GameUI::CreateUI(ge,filepath);
}
void ICON::DrawUI(std::shared_ptr<GameEngine>& ge,const std::string& cameraname) {
	GameUI::DrawUI(ge, _data, cameraname);
}
void ICON::SetUIData(const UIDATA& uidata) {
	_data = uidata;
}
const UIDATA& ICON::GetUIData() {
	return _data;
}