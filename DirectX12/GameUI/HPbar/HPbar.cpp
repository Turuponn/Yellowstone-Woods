#include "HPbar.h"
#include "GameEngine/GameEngine.h"
#include "constance.h"

HPbar::HPbar() {
	
}
HPbar::~HPbar() {

}
void HPbar::CreateUI(std::shared_ptr<GameEngine>& ge, const UIDATA& ddata,const std::string& filepath) {
	_defaultuidata = ddata;
	SetUIData(ddata);
	GameUI::CreateUI(ge, filepath);
}
void HPbar::DrawUI(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	GameUI::DrawUI(ge, _uidata, cameraname);
}
void HPbar::SetUIData(const UIDATA& uidata) {
	_uidata = uidata;
}
const UIDATA& HPbar::GetUIData() {
	return _uidata;
}
void HPbar::ReduceUpdate(std::shared_ptr<GameEngine>& ge, const HPINFO& hinfo) {
	//HPbar�������Ŋg�k���܂�
	float hprate = (float)hinfo.hp / (float)hinfo.maxhp;//����
	_uidata.scale.x = _defaultuidata.scale.x * hprate;//��������X�P�[���l���v�Z
	int screenn_size_x = SCREEN_SIZE_X;//���肦�Ȃ��l�ɂȂ�̂ŉ��
	auto dposx = ((1 - -1)*((_defaultuidata.pos.x / 2) - -screenn_size_x)) / (screenn_size_x - -screenn_size_x) + -1;//�X�N���[�����W->-1~1�ɐ��K���A����=�E+��=�������W�Ȃ̂�/2�����A���������߂�
	auto positionx = dposx - _defaultuidata.scale.x * (1 - hprate) * 0.5;//-1~1��ԏ��x���W���Z�o
	auto p = ((screenn_size_x - -screenn_size_x)*(positionx - -1)) / (1 - -1) + -screenn_size_x;//-1~1->�X�N���[�����W�ɕϊ�
	_uidata.pos.x = p;//x���W���X�P�[���ƍ��킹�ē�����
}