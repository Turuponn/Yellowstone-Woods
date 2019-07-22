#include "EndScene.h"
#include "GameEngine/GameEngine.h"
#include "Game/Scene/TitleScene/TitleScene.h"//NextStage
#include "Game/GameScene.h"
#include "EndUI/EndUI.h"
using namespace std;

namespace {
	const string maincameraname = "メインカメラ";
}


EndScene::EndScene() {

}
EndScene::~EndScene() {

}



void EndScene::InitCamera(std::shared_ptr<GameEngine>& ge) {
	//カメラ生成
	ge->CreateCameraHandle(maincameraname);
	_caminfo.postion.x = 0;
	_caminfo.postion.y = 0;
	_caminfo.postion.z = 0;
	_caminfo.camrenge = 1;
	_caminfo.maincameraname = maincameraname;
	ge->SetCameraPosition(maincameraname, _caminfo.postion);

}
void EndScene::InitUI(std::shared_ptr<GameEngine>& ge) {
	//ui
	std::shared_ptr<EndUI> ui(new EndUI());
	_ui = ui;
	_ui->Init(ge);
}
void EndScene::Init(std::shared_ptr<GameEngine>& ge) {
	InitCamera(ge);
	InitUI(ge);
	frametimecount = 0;
	frametimerate = 0;
}
int EndScene::Update(std::shared_ptr<GameEngine>& ge) {
	//カメラ
	ge->SetCameraRotate(maincameraname, Vector3(0, 0, 0), Vector3(0, 0, 0), _caminfo.camrenge);
	ge->UpdateCamera(maincameraname);

	//Gbuffer
	ge->DR_Pre();
	_ui->Draw(ge, _caminfo.maincameraname);
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


#ifdef _DEBUG
	ge->imguiAddMeshInt(frametimecount, string("frametimecount"), string("f_count"), 0, 100);
#endif

	if (ge->CheckHitKey(DIK_SPACE) && frametimecount > 1) {
		GameScene::Instance().ChengeScene(new TitleScene());
	}
	return 0;
}
