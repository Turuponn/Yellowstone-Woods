#include "GameUI/UIDefault/UIDefault.h"
#include "GameEngine/GameEngine.h"

UIDefault::UIDefault() {

}
UIDefault::~UIDefault() {

}
void UIDefault::Create(std::shared_ptr<GameEngine>& ge, const UIDATA& uidata, const std::string& filepath) {
	SetData(uidata);
	GameUI::CreateUI(ge, filepath);
}
void UIDefault::Draw(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	GameUI::DrawUI(ge, _data, cameraname);
}
void UIDefault::SetData(const UIDATA& uidata) {
	_data = uidata;
}
const UIDATA& UIDefault::GetData() {
	return _data;
}