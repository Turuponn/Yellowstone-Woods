#include "HPbar.h"
#include "GameEngine/GameEngine.h"

HPbar::HPbar() {
	_uihandle = 0;
}
HPbar::~HPbar() {

}
void HPbar::UpdateInfo(std::shared_ptr<GameEngine>& ge) {
	ge->SetPosUI(_uihandle, _hpbarinfo.pos);
	ge->SetScaleUI(_uihandle, _hpbarinfo.scale);
}
void HPbar::CreateUI(std::shared_ptr<GameEngine>& ge,const std::string& filepath) {
	_uihandle = ge->CreateRECTUIHandle(filepath);
}
void HPbar::DrawUI(std::shared_ptr<GameEngine>& ge,const int camerahandle) {
	UpdateInfo(ge);//XV
	ge->DrawRECTUI(_uihandle, camerahandle);
}
void HPbar::SetPos(const Vector3& newpos) {
	_hpbarinfo.pos = newpos;
}
void HPbar::SetScale(const Vector3& newscale) {
	_hpbarinfo.scale = newscale;
}