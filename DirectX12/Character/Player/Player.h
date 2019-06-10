#pragma once

#include "Character/Character.h"






class Player : public Character {
public:
	Player();
	virtual ~Player();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="camerahandle">�J�����ƃL�����N�^�[��΂ɂ��܂�</param>
	void Update(std::shared_ptr<GameEngine>& ge, const int camerahandle);
	/// <summary>
	/// �L�[��������Ă��邩�ǂ�����Ԃ��܂�
	/// </summary>
	/// <returns>true: ������Ă��� false: ������Ă��Ȃ�</returns>
	bool PushKey();
	/// <summary>
	/// �v���C���[�̒��S���W��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	Vector3 GetPlayerPos();
	/// <summary>
	/// �����炵�����S���W���O��������͂��܂�
	/// </summary>
	/// <param name="newp"></param>
	void SetPlayerPos(const Vector3& newp);

private:
	Posture _pinit;//�����p��
	Posture _pforward;//�O
	Posture _pback;//���
	Posture _pleft;//��
	Posture _pright;//�E
	DirectX::XMVECTOR _oldvec;//�O�̉�]�x�N�g��
	Vector3 _playerPostion;
	Vector3 _playerScale;
	int _fbxhandle;//���f���n���h��
	bool _pushF;//�����ꂽ�ꍇ true: false:
	int _animframecount;
	float _t;//���ʐ��`��Ԃ̕�ԗp�ϐ�
	float _tspeed;//��ԑ��x
	float _movespeed;//�L�����N�^�[�ړ����x
};