#include "TitleScene.h"
#include "GameEngine/GameEngine.h"
#include "Game/Scene/Stage1/Stage1.h"//NextStage
#include "TitleUI/TitleUI.h"
#include "Game/GameScene.h"
using namespace std;
namespace {
	const string maincameraname = "メインカメラ";
}


TitleScene::TitleScene() {

}
TitleScene::~TitleScene() {

}
void TitleScene::Init(std::shared_ptr<GameEngine>& ge) {
	
	//カメラ生成
	ge->CreateCameraHandle(maincameraname);
	_caminfo.postion.x = 0;
	_caminfo.postion.y = 0;
	_caminfo.postion.z = 0;
	_caminfo.camrenge = 1;
	_caminfo.maincameraname = maincameraname;
	ge->SetCameraPosition(maincameraname, _caminfo.postion);
	//ui
	std::shared_ptr<TitleUI> titleui(new TitleUI());
	_titleui = titleui;
	_titleui->Init(ge);
	
	frametimecount = 0;
	frametimerate = 0;

}
int TitleScene::Update(std::shared_ptr<GameEngine>& ge) {
	//カメラ
	ge->SetCameraRotate(maincameraname, Vector3(0,0,0), Vector3(0,0,0), _caminfo.camrenge);
	ge->UpdateCamera(maincameraname);

	//Gbuffer
	ge->DR_Pre();
	_titleui->DrawTitleUI(ge, _caminfo.maincameraname);
	ge->DR_Post();
	//Lighting
	ge->PreDeferredShadingRender(maincameraname);
	ge->PostDeferredShadingRender();
	//PostProsess
	ge->PrePostProsessRender(maincameraname);
	ge->PostPostProsessRender();
	//Draw
	ge->DrawScreen(maincameraname);


	frametimerate++;
	if (frametimerate > 30) {
		frametimerate = 0;
		if (frametimecount > 60) {//60までカウントした場合
			frametimecount = 60;//最大フレームとして保存
		}
		else {
			frametimecount++;
		}

	}

	//決定ボタン
	if (ge->CheckHitKey(DIK_SPACE)&& frametimecount > 1) {
		if (_titleui->GetKeyButtonStartExit() == true) {//Start
			//次のシーン
			GameScene::Instance().ChengeScene(new Stage1());
		}
		else {
			return -1;
		}
		
	}
	return 0;
}
