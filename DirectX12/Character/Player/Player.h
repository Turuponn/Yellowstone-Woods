#pragma once

#include "Character/Character.h"



class HPbar;





class Player : public Character {
private://player param
	void HPDataUpdate();

private://UI
	void HPbarUpdateWorld();
	void HPbarUpdate(std::shared_ptr<GameEngine>& ge, const int camerahandle);
private://Input

public:
	Player();
	virtual ~Player();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	virtual const Vector3& GetPostion();
	virtual const Vector3& GetScale();
	virtual void SetPostion(const Vector3& newpos);
	virtual void SetScale(const Vector3& newscale);


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


private:
	std::shared_ptr<HPbar> _hpbar;
	CharacterHPbar _hpparinfo;
	CharacterHPbar _hpdefaultinfo;
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
	float _tspeed;//���ʐ��`��Ԕ}��ϐ��ψʑ��x
	float _movespeed;//�L�����N�^�[�ړ����x

	float _hp;//�v���C���[hp
};