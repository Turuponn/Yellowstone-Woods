#pragma once

class WindowInit;

class DirectInputManager {
public:
	DirectInputManager();
	~DirectInputManager();

	void Initialize(WindowInit& windowinit);

	//���͍X�V:�@��ɓ��͏�Ԃ𒲂ׂ�
	void InputUpdate();

	//�L�[�������ꂽ��
	//@param keycode DIK_�Z�Z�@�Ƃ����L�[�ɑΉ������萔������
	//[out] �����ꂽ: 1 ������Ă��Ȃ� : 0
	const int CheckHitKey(const int keycode);


private:
};