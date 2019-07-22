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
	if (!(_data.color.w < 0)) {//透過値が最大からなら
		_data.color.w = _data.color.w - fadeinspeed;
	}
	/*
	Note:
	フォワードで表示でもしないと奥の情報が描画されていないので
	ディファードだと黒とブレンドされる
	ディザパターンで透過自体は表現できるがアルファをブレンドできるわけではない(結局黒とブレンドされる)
	・アルファ値をテクスチャに保存する->のちに合成させる・・・
	*/
	GameUI::DrawUI(ge, _data, cameraname);
}
void FadeInOut::FadeOut(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, const float fadeoutspeed) {
	if (!(_data.color.w > 1)) {//透過値が最小からなら
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