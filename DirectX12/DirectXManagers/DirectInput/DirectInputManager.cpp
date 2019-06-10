#include "DirectInputManager.h"
#define DIRECTINPUT_VERSION     0x0800  //ver 8�g�p
#include  <dinput.h>
#include <d3d12.h>
#include "Library\GameError.h"
#include "constance.h"
#include "WindowInit.h"

//�Q�l�ɂ���URL http://www.charatsoft.com/develop/otogema/page/07input/dinput.html

#define DIKBIT 0x80

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")


LPDIRECTINPUT8    lpDI = NULL;    
LPDIRECTINPUTDEVICE8    lpKeyboard = NULL; 


// �L�[�̓��́@
BYTE key[256];

DirectInputManager::DirectInputManager() {

}
DirectInputManager::~DirectInputManager() {
	lpKeyboard->Release();
	lpDI->Release();
}
void DirectInputManager::Initialize(WindowInit& windowinit) {
		HRESULT result = E_FAIL;
		// �f�o�C�X�̍쐬�FIDirectInput8�̍쐬 
		auto hInstance = GetModuleHandle(0);
		result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDI,nullptr);
		if (result != S_OK) {
			// �쐬�Ɏ��s
			throw(1);
		}


		//�L�[�{�[�h�f�o�C�X�̎擾 �FIDirectInputDevice8�̎擾
		result = lpDI->CreateDevice(
			GUID_SysKeyboard,//�f�t�H���g�̃V�X�e���L�[�{�[�h
			&lpKeyboard,
			NULL
		);
		if (result != S_OK) {
			// �쐬�Ɏ��s
			throw(1);
		}


		// ���̓f�[�^�`���̃Z�b�g
		result = lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (result != S_OK) {
			// �쐬�Ɏ��s
			lpKeyboard->Release();
			lpDI->Release();
			throw(1);
		}

		// �r������̃Z�b�g
		result = lpKeyboard->SetCooperativeLevel(
			windowinit.GetWindowHwnd(),
			DISCL_FOREGROUND | //Dis�E�E�E�O�@�O�i�̏ꍇ�̂ݏ����@��O�ɂ���ꍇ�̂ݓ��͂��󂯕t����
			DISCL_NONEXCLUSIVE | //�@�g�p���Ă���f�o�C�X�𓖃A�v���ŏ�ɐ�L���Ȃ�
			DISCL_NOWINKEY // Windows�L�[���g���Ȃ��@�悤��
		);
		if (result != S_OK) {
			// �쐬�Ɏ��s
			lpKeyboard->Release();
			lpDI->Release();
			throw(1);
		}

		int stoped = 0;

}


void DirectInputManager::InputUpdate() {
	HRESULT result = E_FAIL;
	//�L�[����
	ZeroMemory(key, sizeof(key));
	result = lpKeyboard->GetDeviceState(sizeof(key), key);
	if (result != S_OK) {
		// ���s�Ȃ�ĊJ�����Ă�����x�擾
		lpKeyboard->Acquire();
		lpKeyboard->GetDeviceState(sizeof(key), key);
	}
		
}
const int DirectInputManager::CheckHitKey(const int keycode) {
	//�L�[�������ꂽ��
	if (key[keycode] & DIKBIT) {
		return 1;
	}
	return 0;
}
