#ifndef GAMEERROR_H
#define GAMEERROR_H

#include <exception> 
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>


namespace GameErrorNS {
	const int WARNING = 1;//�x��
	const int FATAL_ERROR = -1;//�����I��
}

namespace DirectX12ErrorNS {
	const int DEVICELOST = 2;//�f�o�C�X�폜�G���[
}

class GameError : public std::exception {
public:
	GameError() {}
	~GameError() {}
	/// <summary>
	/// �G���[���X���[���܂�
	/// </summary>
	/// <param name="code"></param>
	/// <param name="s"></param>
	GameError(int code, const LPCWSTR &s) throw() : errorCode(code), message(s) {}
	/// <summary>
	/// �G���[���b�Z�[�W��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	LPCWSTR& GetErrorMessage() { return this->message; }
	/// <summary>
	/// �t�@�C�������������܂�
	/// </summary>
	/// <returns></returns>
	LPCWSTR& GetError_filename() { return this->filename; }
	/// <summary>
	/// �G���[�R�[�h��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	int& GetError_code() { return this->errorCode; }
	/// <summary>
	/// �t�@�C���G���[�֌W���X���[���܂�
	/// </summary>
	/// <param name="code"></param>
	/// <param name="erroemsg"></param>
	/// <param name="filename"></param>
	GameError(int code, const LPCWSTR &erroemsg, const LPCWSTR &filename) throw() : errorCode(code), message(erroemsg), filename(filename) {}
	/// <summary>
	/// �G���[����
	/// </summary>
	/// <returns>[out] ����Ȃ�0��Ԃ��@����ȊO��0�ȉ��̒l��Ԃ�</returns>
	int ErrorUpdata() {
		switch (this->GetError_code()) {
		case GameErrorNS::FATAL_ERROR://�ُ�I��
#ifdef _DEBUG  //�f�o�b�O�̂�
			printf("FATAL_ERROR�@Code:%d   ErrorMessage:  %ls\n", this->GetError_code(), this->GetErrorMessage());
			MessageBox(nullptr, this->GetErrorMessage(), _T("FATAL_ERROR!"), MB_OK);
			return GameErrorNS::FATAL_ERROR;
#endif
#ifndef _DEBUG //�����[�X�̂�
			MessageBox(nullptr, this->GetErrorMessage(), _T("FATAL_ERROR!"), MB_OK);
			return GameErrorNS::FATAL_ERROR;
#endif
			break;
		case GameErrorNS::WARNING://�x�� : �I���͂����p������
#ifdef _DEBUG  //�f�o�b�O�̂�
			printf("WARNING�@Code:%d   ErrorMessage:  %ls\n", this->GetError_code(), this->GetErrorMessage());
			MessageBox(nullptr, this->GetErrorMessage(), _T("WARNING!"), MB_OK);
#endif
#ifndef _DEBUG //�����[�X�̂�
			MessageBox(nullptr, this->GetErrorMessage(), _T("FATAL_ERROR!"), MB_OK);
#endif
			break;
		default:
#ifdef _DEBUG  //�f�o�b�O�̂�
			printf("Unknown�@Code: UnknownCood  ErrorMessage: UnknownError\n");
			MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
			return GameErrorNS::WARNING;
#endif
#ifndef _DEBUG //�����[�X�̂�
			MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
			return GameErrorNS::WARNING;
#endif
		}
		return 0;
	}

	//DirectX�n�̃G���[
	void DirectXErrorUpdata(HRESULT hr) {
		switch (this->GetError_code()) {
		case DirectX12ErrorNS::DEVICELOST:
#ifdef _DEBUG  //�f�o�b�O�̂�
			HrToStr(hr);//�G���[��\��
#endif
#ifndef _DEBUG //�����[�X�̂�
			MessageBox(nullptr, nullptr, _T("devicelost!"), MB_OK);
#endif
			break;
		default:
			break;
		}
	}
private:
	// FormatMessage ���g��
	void HrToStr(HRESULT hr) {
		LPVOID string;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&string,
			0,
			NULL);
		if (string != NULL) {
			OutputDebugString((LPCWSTR)string);
		}
		LocalFree(string);
	}
public:
	/// <summary>
	///�s���G���[�̏ꍇ�p 
	/// </summary>
	/// <returns>[out] �K��-1��Ԃ�</returns>
	int UnknowError() {
#ifdef _DEBUG  //�f�o�b�O�̂�

		printf("Unknown  Code: NONE  ErrorMessage: UnknownError\n");
		MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
		return -1;
#endif
#ifndef _DEBUG //�����[�X�̂�
		MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
		return -1;
#endif
	}

private:
	int errorCode;
	LPCWSTR message;
	LPCWSTR filename;
};


#endif
