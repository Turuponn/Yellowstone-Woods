#include "DirectInputManager.h"
#define DIRECTINPUT_VERSION     0x0800  //ver 8使用
#include  <dinput.h>
#include <d3d12.h>
#include "Library\GameError.h"
#include "constance.h"
#include "WindowInit.h"

//参考にしたURL http://www.charatsoft.com/develop/otogema/page/07input/dinput.html

#define DIKBIT 0x80

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")


LPDIRECTINPUT8    lpDI = NULL;    
LPDIRECTINPUTDEVICE8    lpKeyboard = NULL; 


// キーの入力　
BYTE key[256];

DirectInputManager::DirectInputManager() {

}
DirectInputManager::~DirectInputManager() {
	lpKeyboard->Release();
	lpDI->Release();
}
void DirectInputManager::Initialize(WindowInit& windowinit) {
		HRESULT result = E_FAIL;
		// デバイスの作成：IDirectInput8の作成 
		auto hInstance = GetModuleHandle(0);
		result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDI,nullptr);
		if (result != S_OK) {
			// 作成に失敗
			throw(1);
		}


		//キーボードデバイスの取得 ：IDirectInputDevice8の取得
		result = lpDI->CreateDevice(
			GUID_SysKeyboard,//デフォルトのシステムキーボード
			&lpKeyboard,
			NULL
		);
		if (result != S_OK) {
			// 作成に失敗
			throw(1);
		}


		// 入力データ形式のセット
		result = lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (result != S_OK) {
			// 作成に失敗
			lpKeyboard->Release();
			lpDI->Release();
			throw(1);
		}

		// 排他制御のセット
		result = lpKeyboard->SetCooperativeLevel(
			windowinit.GetWindowHwnd(),
			DISCL_FOREGROUND | //Dis・・・前　前景の場合のみ処理　手前にある場合のみ入力を受け付ける
			DISCL_NONEXCLUSIVE | //　使用しているデバイスを当アプリで常に占有しない
			DISCL_NOWINKEY // Windowsキーを使えない　ように
		);
		if (result != S_OK) {
			// 作成に失敗
			lpKeyboard->Release();
			lpDI->Release();
			throw(1);
		}

		int stoped = 0;

}


void DirectInputManager::InputUpdate() {
	HRESULT result = E_FAIL;
	//キー入力
	ZeroMemory(key, sizeof(key));
	result = lpKeyboard->GetDeviceState(sizeof(key), key);
	if (result != S_OK) {
		// 失敗なら再開させてもう一度取得
		lpKeyboard->Acquire();
		lpKeyboard->GetDeviceState(sizeof(key), key);
	}
		
}
const int DirectInputManager::CheckHitKey(const int keycode) {
	//キーが押されたら
	if (key[keycode] & DIKBIT) {
		return 1;
	}
	return 0;
}
