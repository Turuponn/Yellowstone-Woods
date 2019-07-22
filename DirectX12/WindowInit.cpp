#include "WindowInit.h"
#include "Library\GameError.h"
#include "constance.h"
#include "imgui.h"
#include "imguiManager\imgui\imgui_impl_win32.h"
#include "imguiManager\imgui\imgui_impl_dx12.h"
#include <d2d1.h>
#include <mmsystem.h>//frameTimer


WindowInit* WindowInit::mInstance = 0;
const TCHAR* CLASS_NAME = _T("イエローストーンの森");



namespace {
	//FrameTime
	LARGE_INTEGER _timeStart;
	LARGE_INTEGER _timeEnd;
	LARGE_INTEGER _timeFreq;
	const float MIN_FREAM_TIME = 1.0f / 60;
}

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
WindowInit::WindowInit() {
	_imguiResetF = false;
	_swapchainResetF = false;
	_rtvResetF = false;
	_frameTime = 0;
	_fps = 0;
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

	//TODO:　imgui resize UI TestsFunc
	WindowInit::USE().SetimGuiResetF(false);
	WindowInit::USE().SetSwapChainResetF(false);
	WindowInit::USE().SetRtvResetF(false);

	
	CreateFrameTimer();
	

}
void WindowInit::FixedFrameTime() {
	//Sleep法をつかって固定フレームレートにする
	QueryPerformanceCounter(&_timeEnd);
	_frameTime = static_cast<float>(_timeEnd.QuadPart - _timeStart.QuadPart) / static_cast<float>(_timeFreq.QuadPart);
	if (_frameTime < MIN_FREAM_TIME) {
		// ミリ秒に変換
		DWORD sleepTime = static_cast<DWORD>((MIN_FREAM_TIME - _frameTime) * 1000);
		timeBeginPeriod(1);
		Sleep(sleepTime);   
		timeEndPeriod(1); 
		return;
	}
	if (_frameTime > 0.0) {
		_fps = (_fps*0.99f) + (0.01f / _frameTime);
	}
	_timeStart = _timeEnd;
}
float WindowInit::GetFps() {
	return _fps;
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
void WindowInit::CreateFrameTimer() {
	//精度取得
	if (QueryPerformanceFrequency(&_timeFreq) == FALSE) {
		throw(1);//未対応扱い
	}
	QueryPerformanceCounter(&_timeStart);
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
	case WM_PAINT:
		
		break;

	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
