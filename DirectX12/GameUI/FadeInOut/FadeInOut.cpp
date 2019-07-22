#include "FadeInOut.h"


FadeInOut::FadeInOut() {

}
FadeInOut::~FadeInOut() {

}
void FadeInOut::LoadResoce(std::shared_ptr<GameEngine>& ge, const UIDATA& data,const std::string& filepath) {
	_data = data;
	GameUI::CreateUI(ge,filepath);
}

void FadeInOut::FadeIn(std::shared_ptr<GameEngine>& ge, const std::string& cameraname,const float fadeinspeed) {
	if (!(_data.color.w < 0)) {//���ߒl���ő傩��Ȃ�
		_data.color.w = _data.color.w - fadeinspeed;
	}
	/*
	Note:
	�t�H���[�h�ŕ\���ł����Ȃ��Ɖ��̏�񂪕`�悳��Ă��Ȃ��̂�
	�f�B�t�@�[�h���ƍ��ƃu�����h�����
	�f�B�U�p�^�[���œ��ߎ��͕̂\���ł��邪�A���t�@���u�����h�ł���킯�ł͂Ȃ�(���Ǎ��ƃu�����h�����)
	�E�A���t�@�l���e�N�X�`���ɕۑ�����->�̂��ɍ���������E�E�E
	*/
	GameUI::DrawUI(ge, _data, cameraname);
}
void FadeInOut::FadeOut(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, const float fadeoutspeed) {
	if (!(_data.color.w > 1)) {//���ߒl���ŏ�����Ȃ�
		_data.color.w = _data.color.w + fadeoutspeed;
	}
	GameUI::DrawUI(ge, _data, cameraname);
}
void FadeInOut::SetUIData(const UIDATA& uidata) {
	_data = uidata;
}
const UIDATA& FadeInOut::GetUIData() {
	return _data;
}