#include "GameScene.h"
#include "WindowInit.h"
#include <string>
#include <chrono>  // chrono::system_clock
#include <sstream> //stringstream
#include <iomanip>//put_time
#include <DirectXMath.h>

#include "GameEngine\GameEngine.h"
#include "Scene/Scene.h"
#include "Scene/TitleScene/TitleScene.h"//NextScene
#include "Scene/Stage1/Stage1.h"//Debug
#include "Scene/EndScene/EndScene.h"


using namespace std;
using namespace DirectX;

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")



GameScene::GameScene(){
	_scene = nullptr;
	Init();
}
GameScene::~GameScene() {
	delete _scene;
	WindowInit::USE().destroy();
}




void GameScene::Init() {
	//マウスカーソルを非表示にする　TODO:コントローラ
	//ShowCursor(FALSE);


	//windowInit
	WindowInit::Instance();
	WindowInit::USE().WindowInitialize();
	ShowWindow(WindowInit::USE().GetWindowHwnd(), SW_SHOW);
	UpdateWindow(WindowInit::USE().GetWindowHwnd());

	//GameEngine Init
	std::shared_ptr<GameEngine> ge(new GameEngine());
	_ge = ge;
	_ge->Initialize(WindowInit::USE());
	//InitScene
	ChengeScene(new TitleScene());
	//ChengeScene(new EndScene());
	//ChengeScene(new Stage1());
}



void GameScene::Run() {
	//Mainloop
	GAMEMAIN gm = {};
	clock_t deltaTime = 0;
	unsigned int frameTime = 0;
	MSG msg = {};
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			break;
		}

		//Sleep法を使用し、固定フレームレートを実現する
		WindowInit::USE().FixedFrameTime();
		//Update
		clock_t beginFrame = clock();//プログラム実行開始からの経過時間
		gm.deltatime = (deltaTime / CLOCKS_PER_SEC);//ミリ秒にしない。
		frameTime = (frameTime + gm.deltatime);
		gm.frameTime = frameTime;
		_ge->Run();
#ifdef _DEBUG
		_ge->imguiPre();
#endif	
		//シーン切り替え
		if (_scene->Update(_ge) < 0) {//終了コールがあれば
			break;//終了
		}
#ifdef _DEBUG
		_ge->imguiPost();
#endif
		_ge->ScreenFilip();
		clock_t endFrame = clock();

		//1秒ごとにフレームをリセットし、オーバーフローを避けます
		deltaTime += endFrame - beginFrame;
		if ((deltaTime / CLOCKS_PER_SEC)*1000.0 > 1000.0) {
			deltaTime -= CLOCKS_PER_SEC;
			frameTime = 0;
		}


	}
	//DebugMemoryLog
#if defined(_DEBUG) + defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF + _CRTDBG_LEAK_CHECK_DF);
#endif
}

void GameScene::ChengeScene(Scene* scene) {
	if (_scene != nullptr) {//中身があったらデリート
		delete  _scene;
		_scene = 0;
	}
	_scene = scene;
	_scene->Init(_ge);
}
GameScene& GameScene::Instance() {
	static GameScene instance;
	return instance;
}