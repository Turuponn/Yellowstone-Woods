#include "Button.h"
#include "GameEngine/GameEngine.h"
using namespace std;


Button::Button() {
	
}
Button::~Button() {

}
void Button::Create(std::shared_ptr<GameEngine>& ge, const UIDATA& uidata,const float countspeed,const std::string& filepath) {
	SetData(uidata);
	GameUI::CreateUI(ge, filepath);
	//�J���[�J�E���^�̃��Z�b�g
	_selectcolorpattern_a = countspeed;
	_scolorcount = 0;
}
void Button::DrawSelect(std::shared_ptr<GameEngine>& ge, const std::string& cameraname,bool selectF) {
	
	//�F��0~1��
	if (selectF == true) {
		_scolorcount = _scolorcount + _selectcolorpattern_a;
		_data.color.w = (sinf(_scolorcount) + 1.2);
		if (_scolorcount > 1000) {
			_scolorcount = 0;
		}
	}
	else {
		_data.color.w = 1;
		_scolorcount = 0;
	}
	GameUI::DrawUI(ge, _data, cameraname);
}
void Button::DrawSelectPush(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, bool selectF) {
	//����ρ@���ʂ� plase push key �ɂ��邩
}
void Button::Draw(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	GameUI::DrawUI(ge, _data, cameraname);
}
void Button::SetData(const UIDATA& uidata) {
	_data = uidata;
}
const UIDATA& Button::GetData() {
	return _data;
}
