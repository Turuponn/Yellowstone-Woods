#pragma once


#include "Character/Character.h"





class Wolf : public Character {
private://Animation
	void UpdateAnimation(std::shared_ptr<GameEngine>& ge);
	void (Wolf::*_updateAnimationFunc)();
	void PlayEatMotion();// �H�ׂ郂�[�V�������Đ����܂�
	void PlayWorkMotion();// �������[�V�������Đ����܂�
	void PlayIdleMotion();// �ҋ@���[�V�������Đ����܂�
	void PlayDeathMotion();// ���S���[�V�������Đ����܂�
private://AI
	void (Wolf::*_updateAIFunc)(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIIdle(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIHunt(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);//�ǐՃ��[�h
	void AIEat(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIDeath(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
public:
	Wolf();
	~Wolf();
	void Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata);
	void Update(std::shared_ptr<GameEngine>& ge,const std::string& cameraname);
	void AIUpdate(std::shared_ptr<GameEngine>& ge, const Vector3& targetpos, const int DISHANTMAX, const int DISEATMAX);
	/// <summary>
	/// �w��|�C���g�ֈړ����Ȃ���߂Â��܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproach(std::shared_ptr<GameEngine>& ge,const Vector3& pointpos);
	/// <summary>
	/// ���[���h���W��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();
	const float GetHP();
	void SetHP(const float newhp);
	std::shared_ptr<Entity>& GetEntity();
private:
	DirectX::XMVECTOR _oldvec;//�O�̉�]�x�N�g��
	int _animframecount;
	std::string _nextmotionname;//�����[�V�����̖��O�����܂�
};