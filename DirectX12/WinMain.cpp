#include <Windows.h>
#include "d3dx12.h"
#include <iostream>
#include "WindowInit.h"
#include "Library\GameError.h"
#include "constance.h"
#include "Game\GameScene.h"


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

HRESULT result = E_FAIL;

GameScene* _game;

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

INT main() {
	//マウスカーソルを非表示にする
	//ShowCursor(FALSE);
	result = E_FAIL;
	try {
		_game = new GameScene();
	}
	catch (GameError& err) {
		if (err.ErrorUpdata() < 0) {
			return -1;
		}
	}
	catch (...) {
#ifdef _DEBUG 
		printf("Unknown  Code: NONE  ErrorMessage: UnknownError\n");
		MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
		return -1;
#endif
#ifndef _DEBUG
		MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
		return -1;
#endif
	}
	
	WindowInit::Instance();
	WindowInit::USE().WindowInitialize();
	ShowWindow(WindowInit::USE().GetWindowHwnd(), SW_SHOW);
	UpdateWindow(WindowInit::USE().GetWindowHwnd());
	_game->Initialize(WindowInit::USE());

#pragma region メインループ

	MSG msg = {};
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			break;
		}

		_game->Updata();

	}
#pragma endregion
	SAFE_DELETE(_game);
	WindowInit::USE().destroy();
#if defined(_DEBUG) + defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF + _CRTDBG_LEAK_CHECK_DF);
#endif
	return 0;
}