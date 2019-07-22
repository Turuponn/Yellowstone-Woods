#pragma once

#include <Windows.h>
#include <memory>

namespace WindowsNS {
	struct SCREENSIZE {
		unsigned int width;
		unsigned int height;
	};
}
struct WINDOWCREATE {
	const TCHAR* CLASS_NAME;//�A�v���l�[��
	LRESULT (*messagefunc)(HWND, UINT , WPARAM , LPARAM);
	WindowsNS::SCREENSIZE screensize;
};
//���C�����[�v�Ŏg�p������J�p�����[�^
struct GAMEMAIN {
	float deltatime;//�Ō�̃t���[������̌o�ߎ���
	float frameTime;
};

class WindowInit {
private:
	WindowInit();
	WindowInit(const WindowInit&);
	WindowInit& operator=(const WindowInit&);
   
	static void create();
	

public:
	virtual ~WindowInit();
	static WindowInit* Instance();
	static WindowInit& USE();
	static void destroy();
	void WindowInitialize(WINDOWCREATE& newwindow);
	void WindowInitialize();
	HWND& GetWindowHwnd();
	bool GetimGuiResetF();
	bool GetSwapChainResetF();
	bool GetRtvResetF();
	void SetimGuiResetF(bool newf);
	void SetSwapChainResetF(bool newf);
	void SetRtvResetF(bool newf);
	void CreateFrameTimer();
	void FixedFrameTime();
	float GetFps();
private:
	static WindowInit* mInstance;
	HINSTANCE hInst;
	WNDCLASSEX w;
	RECT wrc;
	HWND _hwnd;
	bool _imguiResetF;
	bool _swapchainResetF;
	bool _rtvResetF;
	float _fps;
	float _frameTime;

};