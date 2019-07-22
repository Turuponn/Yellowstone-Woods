#pragma once

#include "Character/Character.h"



class HPbar;





class Player : public Character {
private://Animation
	void UpdateAnimation(std::shared_ptr<GameEngine>& ge);
	void (Player::*_updateAnimationFunc)();
	void PlayCryMotion();
	void PlayFlyingMotion();
	void PlayIdleMotion();
	void PlayStartflyMotion();

private://Input
	//���͌n
	void Input(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
public:
	Player();
	~Player();
	void Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata);

	
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="ge"></param>
	void Update(std::shared_ptr<GameEngine>& ge,const std::string& cameraname);
	/// <summary>
	/// �|�C���g�̕���������
	/// </summary>
	void Approachforward(std::shared_ptr<GameEngine>& ge, const Vector3& pointpos);

	void InputCry(std::shared_ptr<GameEngine>& ge);

	/// <summary>
	/// ���[���h���W��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();
	const float GetHP();
	void SetHP(const float newhp);
	/// <summary>
	/// ���ԃ{�^���������ꂽ�ꍇ true:�@�����ꂽ false:�@������Ă��Ȃ�
	/// </summary>
	/// <returns></returns>
	bool GetPushShout();

private:
	DirectX::XMVECTOR _oldvec;//�O�̉�]�x�N�g��
	int _fbxhandle;//���f���n���h��
	bool _pushF;//�����ꂽ�ꍇ true: false:
	bool _pushShoutF;//�����ꂽ�ꍇ true:�����ꂽ�@false:������Ă��Ȃ�
	int _animframecount;
	std::string _nextmotionname;//�����[�V�����̖��O�����܂�
	
};