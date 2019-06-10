#ifndef GAMEERROR_H
#define GAMEERROR_H

#include <exception> 
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>


namespace GameErrorNS {
	const int WARNING = 1;//警告
	const int FATAL_ERROR = -1;//強制終了
}

namespace DirectX12ErrorNS {
	const int DEVICELOST = 2;//デバイス削除エラー
}

class GameError : public std::exception {
public:
	GameError() {}
	~GameError() {}
	/// <summary>
	/// エラーをスローします
	/// </summary>
	/// <param name="code"></param>
	/// <param name="s"></param>
	GameError(int code, const LPCWSTR &s) throw() : errorCode(code), message(s) {}
	/// <summary>
	/// エラーメッセージを返します
	/// </summary>
	/// <returns></returns>
	LPCWSTR& GetErrorMessage() { return this->message; }
	/// <summary>
	/// ファイル名をかえします
	/// </summary>
	/// <returns></returns>
	LPCWSTR& GetError_filename() { return this->filename; }
	/// <summary>
	/// エラーコードを返します
	/// </summary>
	/// <returns></returns>
	int& GetError_code() { return this->errorCode; }
	/// <summary>
	/// ファイルエラー関係をスローします
	/// </summary>
	/// <param name="code"></param>
	/// <param name="erroemsg"></param>
	/// <param name="filename"></param>
	GameError(int code, const LPCWSTR &erroemsg, const LPCWSTR &filename) throw() : errorCode(code), message(erroemsg), filename(filename) {}
	/// <summary>
	/// エラー処理
	/// </summary>
	/// <returns>[out] 正常なら0を返す　それ以外は0以下の値を返す</returns>
	int ErrorUpdata() {
		switch (this->GetError_code()) {
		case GameErrorNS::FATAL_ERROR://異常終了
#ifdef _DEBUG  //デバッグのみ
			printf("FATAL_ERROR　Code:%d   ErrorMessage:  %ls\n", this->GetError_code(), this->GetErrorMessage());
			MessageBox(nullptr, this->GetErrorMessage(), _T("FATAL_ERROR!"), MB_OK);
			return GameErrorNS::FATAL_ERROR;
#endif
#ifndef _DEBUG //リリースのみ
			MessageBox(nullptr, this->GetErrorMessage(), _T("FATAL_ERROR!"), MB_OK);
			return GameErrorNS::FATAL_ERROR;
#endif
			break;
		case GameErrorNS::WARNING://警告 : 終了はせず継続する
#ifdef _DEBUG  //デバッグのみ
			printf("WARNING　Code:%d   ErrorMessage:  %ls\n", this->GetError_code(), this->GetErrorMessage());
			MessageBox(nullptr, this->GetErrorMessage(), _T("WARNING!"), MB_OK);
#endif
#ifndef _DEBUG //リリースのみ
			MessageBox(nullptr, this->GetErrorMessage(), _T("FATAL_ERROR!"), MB_OK);
#endif
			break;
		default:
#ifdef _DEBUG  //デバッグのみ
			printf("Unknown　Code: UnknownCood  ErrorMessage: UnknownError\n");
			MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
			return GameErrorNS::WARNING;
#endif
#ifndef _DEBUG //リリースのみ
			MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
			return GameErrorNS::WARNING;
#endif
		}
		return 0;
	}

	//DirectX系のエラー
	void DirectXErrorUpdata(HRESULT hr) {
		switch (this->GetError_code()) {
		case DirectX12ErrorNS::DEVICELOST:
#ifdef _DEBUG  //デバッグのみ
			HrToStr(hr);//エラーを表示
#endif
#ifndef _DEBUG //リリースのみ
			MessageBox(nullptr, nullptr, _T("devicelost!"), MB_OK);
#endif
			break;
		default:
			break;
		}
	}
private:
	// FormatMessage を使う
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
	///不明エラーの場合用 
	/// </summary>
	/// <returns>[out] 必ず-1を返す</returns>
	int UnknowError() {
#ifdef _DEBUG  //デバッグのみ

		printf("Unknown  Code: NONE  ErrorMessage: UnknownError\n");
		MessageBox(nullptr, _T("UnknownError"), _T("Unknown!"), MB_OK);
		return -1;
#endif
#ifndef _DEBUG //リリースのみ
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
