#pragma once

#include "Character/Character.h"



struct RANDPOS {
	float randX;
	float randY;
	float randZ;
};
struct RANDPACKAGE {
	Vector3 randpos;
	Vector3 randscale;
	int frametimecountmax;//�ǂ̂��炢�t���[���ő҂Ă΂������ő�l
};

class Cow : public Character {
private:
	void EscapeUpdate(std::shared_ptr<GameEngine>& ge, const int ESCAPEDIS);//���͈͂𒴂����ꍇ�A�����؂����Ƃ݂Ȃ����荞�ݏ����𔭐�������
private://AI
	void (Cow::*_updateAIFunc)(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIIdle(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIRun(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);//�������[�h
	void AIMove(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);//�a�����߂Ĉړ�����
	void AIDeath(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
	void AIEscape(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& targetpos);
private:
	void MoveToDeath();// ���S�㎀�̂��̂���Ȃ��悤�ɗy���ޕ��֔�΂�����
private://Animation
	void UpdateAnimation(const std::string& modelname,std::shared_ptr<GameEngine>& ge);//�A�j���[�V�����X�V
	void (Cow::*_updateAnimationFunc)();
	void PlayWorkMotion();// �������[�V�������Đ����܂�
	void PlayIdleMotion();// �ҋ@���[�V�������Đ����܂�
	void PlayDeathMotion();// ���S���[�V�������Đ����܂�

public:
	Cow();
	~Cow();
	void Initialize(std::shared_ptr<GameEngine>& ge, const WORLDDATA& wdata, const CHARACTERPARAMETERDATA& cdata, const std::string& modelname);

	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="ESCAPEDIS">�����؂�۔���p���a</param>
	/// <param name="randpackage">�����_���������p</param>
	void Update(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const int ESCAPEDIS,const RANDPACKAGE& randpackage);
	/// <summary>
	/// AI�̍X�V
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="targetpos"></param>
	/// <param name="DISRUNMAX">����ꍇ�A�����͈̔�</param>
	/// <param name="DISMOVEMAX">���S�Ɉړ�����ꍇ�A�����͈̔�</param>
	/// <param name="DISDEATHMAX">���S����ꍇ�A�����͈̔�</param>
	void AIUpdate(
		const std::string& modelname,
		std::shared_ptr<GameEngine>& ge,
		const Vector3& targetpos,
		const int DISRUNMAX, 
		const int DISMOVEMAX,
		const int DISDEATHMAX
	);
	/// <summary>
	/// �w��|�C���g�֑O�i�ړ����Ȃ���߂Â��܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproachforward(const std::string& modelname,std::shared_ptr<GameEngine>& ge,const Vector3& pointpos);
	/// <summary>
	/// �w��|�C���g�����Č�ވړ����Ȃ���ނ��܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="pointpos"></param>
	void MoveApproachback(const std::string& modelname,std::shared_ptr<GameEngine>& ge, const Vector3& pointpos);
	/// <summary>
	/// ���S���Ă��邩�ǂ���
	/// </summary>
	/// <returns>true:�@�����Ă��� false:�@���S���Ă���</returns>
	bool GetCowDeathF();
	/// <summary>
	/// ���[���h���W��Ԃ�
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();

	
private:
	
	
	DirectX::XMVECTOR _oldvec;
	int _animframecount;
	int _alivecount;//�����p�J�E���^
	

	std::string _nextmotionname;//�����[�V�����̖��O�����܂�
	bool _animationstopF;//�A�j���[�V�������g�p���邩�ǂ��� true:�@���� false:�@���Ȃ�
	bool _fadeF;//���ł��Ă��邩 true:���ł��Ă��� false:���ł��Ă��Ȃ�
	RANDPOS _randtargetpos;//�����_���Ȓ����_
	FRAMETIME _randposFrame;
	RANDPACKAGE _initrandpackage;//�������p������ۑ����Ă���
	FRAMETIME _characterFadeFrame;//���ł����ꍇ�p�t���[������
};