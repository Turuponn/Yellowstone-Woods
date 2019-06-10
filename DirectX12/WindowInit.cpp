#include "WindowInit.h"
#include "Library\GameError.h"
#include "constance.h"
#include "imgui.h"
#include "imguiManager\imgui\imgui_impl_win32.h"
#include "imguiManager\imgui\imgui_impl_dx12.h"


WindowInit* WindowInit::mInstance = 0;


const TCHAR* CLASS_NAME = _T("イエローストーンの森");
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

WindowInit::WindowInit() {
	_imguiResetF = false;
	_swapchainResetF = false;
	_rtvResetF = false;
}

WindowInit::~WindowInit() {
	UnregisterClass(w.lpszClassName, hInst);
}
void WindowInit::create() {
	
	if (mInstance != nullptr) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("WindowInit"), _T("!mInstance")));
	}
	
	mInstance = new WindowInit();
}


void WindowInit::WindowInitialize(WINDOWCREATE& newwindow) {
	WINDOWCREATE windowinit;
	windowinit.CLASS_NAME = CLASS_NAME;
	windowinit.messagefunc = &WindowProcedure;
	windowinit.screensize.width = SCREEN_SIZE_X;
	windowinit.screensize.height = SCREEN_SIZE_Y;
	
	hInst = GetModuleHandle(nullptr);


	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, (WNDPROC)newwindow.messagefunc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, newwindow.CLASS_NAME, NULL };
	w = wc;
	auto atom = RegisterClassEx(&w);

	RECT wrcs = { 0,0,(LONG)newwindow.screensize.width ,(LONG)newwindow.screensize.height };
	wrc = wrcs;
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);	 
	_hwnd = CreateWindow(
		w.lpszClassName,
		newwindow.CLASS_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrcs.right - wrcs.left,
		wrcs.bottom - wrcs.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr 
		);


}
void WindowInit::WindowInitialize() {
	WINDOWCREATE windowinit;

	windowinit.CLASS_NAME = CLASS_NAME;
	windowinit.messagefunc = &WindowProcedure;
	windowinit.screensize.width = SCREEN_SIZE_X;
	windowinit.screensize.height = SCREEN_SIZE_Y;

	hInst = GetModuleHandle(nullptr);

	w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)windowinit.messagefunc;
	w.lpszClassName = windowinit.CLASS_NAME;
	w.hInstance = GetModuleHandle(0);
	auto atom = RegisterClassEx(&w);


	RECT wrcs = { 0,0,(LONG)windowinit.screensize.width ,(LONG)windowinit.screensize.height };
	wrc = wrcs;
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	_hwnd = CreateWindow(
		w.lpszClassName,
		windowinit.CLASS_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrcs.right - wrcs.left,
		wrcs.bottom - wrcs.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr 
	);

	WindowInit::USE().SetimGuiResetF(false);
	WindowInit::USE().SetSwapChainResetF(false);
	WindowInit::USE().SetRtvResetF(false);
}
void WindowInit::destroy() {
	SAFE_DELETE(mInstance)
}

WindowInit* WindowInit::Instance() {
	create();
	return mInstance;
}
WindowInit& WindowInit::USE() {
	if (mInstance == nullptr) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("WindowInit"), _T("mInstance == nullptr")));
	}
	return *mInstance;
}
HWND& WindowInit::GetWindowHwnd() {
	return _hwnd;
}
bool WindowInit::GetimGuiResetF() {
	return _imguiResetF;
}
bool WindowInit::GetSwapChainResetF() {
	return _swapchainResetF;
}
bool WindowInit::GetRtvResetF() {
	return _rtvResetF;
}
void WindowInit::SetimGuiResetF(bool newf) {
	_imguiResetF = newf;
}
void WindowInit::SetSwapChainResetF(bool newf) {
	_swapchainResetF = newf;
}
void WindowInit::SetRtvResetF(bool newf) {
	_rtvResetF = newf;
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) { return true; }

	switch (msg) {
	case WM_DESTROY://終了リクエスト //Window閉じるリクエストがきたら
		PostQuitMessage(0);//OSに対してアプリ終了を伝える
		return 0;
		break;
	case WM_CLOSE://Alt+F4対応
				  if (MessageBox(hwnd, _T("Really quit?"), _T("game"), MB_OKCANCEL) == IDOK)
				  {
				  DestroyWindow(hwnd);
				  }
				  else {
					  return 0;
				  }
				  // Else: ユーザーがキャンセルし、何もしない
		DestroyWindow(hwnd);
		return 0;
	case WM_SIZE:
		if (wparam != SIZE_MINIMIZED)
		{
			//サイズを切り替える
			/*ImGui_ImplDX12_InvalidateDeviceObjects();
			CleanupRenderTarget();
			ResizeSwapChain(hWnd, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
			CreateRenderTarget();
			ImGui_ImplDX12_CreateDeviceObjects();*/
			// TODO:
			WindowInit::USE().SetimGuiResetF(true);
			WindowInit::USE().SetSwapChainResetF(true);
			WindowInit::USE().SetRtvResetF(true);
		}
		return 0;

		break;

	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}