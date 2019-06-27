#pragma once


#include "Character/Character.h"

class HPbar;

class Wolf : public Character {
private://UI
	void HPbarUpdateWorld();
	void HPbarUpdate(std::shared_ptr<GameEngine>& ge, const int camerahandle);
public:
	Wolf();
	virtual ~Wolf();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	virtual const Vector3& GetPostion();
	virtual const Vector3& GetScale();
	virtual void SetPostion(const Vector3& newpos);
	virtual void SetScale(const Vector3& newscale);


	void Update(std::shared_ptr<GameEngine>& ge, const int camerahandle);
	/// <summary>
	/// �w��|�C���g�ֈړ����Ȃ���߂Â��܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproach(std::shared_ptr<GameEngine>& ge,const Vector3& pointpos);
	/// <summary>
	/// �H�ׂ郂�[�V�������Đ����܂�
	/// </summary>
	void PlayEatMotion();
	/// <summary>
	/// �������[�V�������Đ����܂�
	/// </summary>
	void PlayWorkMotion();
	/// <summary>
	/// �ҋ@���[�V�������Đ����܂�
	/// </summary>
	void PlayIdleMotion();
	/// <summary>
	/// ���S���[�V�������Đ����܂�
	/// </summary>
	void PlayDethMotion();


private:
	Posture _winit;//�����p��
	Posture _wforward;//�O
	Posture _wback;//���
	Posture _wleft;//��
	Posture _wright;//�E
	int _fbxhandle;//���f���n���h��
	DirectX::XMVECTOR _oldvec;//�O�̉�]�x�N�g��
	Vector3 _wolfPostion;
	Vector3 _wolfScale;
	Vector3 _wolfPosOffset;
	int _animframecount;
	std::string _nextmotionname;//�����[�V�����̖��O�����܂�
	float _movespeed;//�ړ����x
	float _tspeed;//���ʐ��`��Ԕ}��ϐ��ψʑ��x
	//UI
	std::shared_ptr<HPbar> _hpbar;
	CharacterHPbar _hpparinfo;
};