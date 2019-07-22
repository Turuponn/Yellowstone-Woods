#pragma once

class WindowInit;

class DirectInputManager {
public:
	DirectInputManager();
	~DirectInputManager();

	void Initialize(WindowInit& windowinit);

	//入力更新:　常に入力状態を調べる
	void InputUpdate();

	//キーが押されたら
	//@param keycode DIK_〇〇　というキーに対応した定数を入れる
	//[out] 押された: 1 押されていない : 0
	const int CheckHitKey(const int keycode);


private:
};