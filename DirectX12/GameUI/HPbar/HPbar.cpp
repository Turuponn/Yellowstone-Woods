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
	//HPbarを割合で拡縮します
	float hprate = (float)hinfo.hp / (float)hinfo.maxhp;//割合
	_uidata.scale.x = _defaultuidata.scale.x * hprate;//割合からスケール値を計算
	int screenn_size_x = SCREEN_SIZE_X;//ありえない値になるので回避
	auto dposx = ((1 - -1)*((_defaultuidata.pos.x / 2) - -screenn_size_x)) / (screenn_size_x - -screenn_size_x) + -1;//スクリーン座標->-1~1に正規化、中央=右+左=初期座標なので/2をし、横幅を求める
	auto positionx = dposx - _defaultuidata.scale.x * (1 - hprate) * 0.5;//-1~1空間上でx座標を算出
	auto p = ((screenn_size_x - -screenn_size_x)*(positionx - -1)) / (1 - -1) + -screenn_size_x;//-1~1->スクリーン座標に変換
	_uidata.pos.x = p;//x座標をスケールと合わせて動かす
}