#pragma once



#include <memory>
#include <string>
#include "Geometori.h"
#define GROUNDPOS_Y 1 //Y���Woffset�f�[�^

class GameEngine;
class Entity;


//�p��
struct POSTURE {
	Vector3 axis;
	float angle;
};
//�L�����pHPbar
struct CHARACTERHPBAR {
	Vector3 pos;
	Vector3 scale;
};
//���[���h�s��p�f�[�^
struct WORLDDATA {
	Vector3 pos;
	Vector3 scale;
	Vector3 rotate;
};
//�L�����N�^�[�p�ۗL�f�[�^
struct CHARACTERDATA {
	WORLDDATA worlddata;//���[���h�s��p�f�[�^
	POSTURE init;//�����p��
	POSTURE forward;//�O
	POSTURE back;//���
	POSTURE left;//��
	POSTURE right;//�E
	float movespeed;//�ړ����x
	float tspeed;//���ʐ��`��Ԕ}��ϐ��ψʑ��x
};
struct CHARACTERPARAMETERDATA {
	float hp;
};


struct FRAMETIME {
	unsigned int frameTime;//�t���[�����J�E���g����
	unsigned int frameCount;//�t���[���������J�E���g������
};



class Character {
private:
	void init();
protected:
	Character();
	



	///�A�N�Z�b�T====================================
	/// <summary>
	/// �R���W�����}�l�[�W���[��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<Entity>& GetEntiy();
	/// <summary>
	/// ���S���Ă��邩�ǂ�����Ԃ��܂�
	/// </summary>
	/// <returns>true: �����Ă��� false:�@���S���Ă���</returns>
	bool GetDeathF();
	/// <summary>
	/// ���S����ׂ����ǂ������X�V���܂�
	/// </summary>
	/// <param name="newstatus">true:�@�����Ă��� false:�@���S���Ă���</param>
	void SetDeathF(bool newstatus);
	/// <summary>
	/// �L�����N�^�[�ێ��f�[�^��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	const CHARACTERDATA& GetCharacterData();
	/// <summary>
	/// �L�����N�^�[�ێ��f�[�^���X�V���܂�
	/// </summary>
	/// <param name="newcharacterdata"></param>
	void SetCharacterData(const CHARACTERDATA& newcharacterdata);
	/// <summary>
	/// �L�����N�^�[�ێ��f�[�^:�p�����[�^�@���X�V���܂�
	/// </summary>
	/// <param name="cparamdata"></param>
	void SetCharacterParameterData(const CHARACTERPARAMETERDATA& cparamdata);
	/// <summary>
	/// �L�����N�^�[�ێ��f�[�^:�p�����[�^�@��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	const CHARACTERPARAMETERDATA& GetCharacterParameterData();
	///�������z�֐�==================================
	
public:
	virtual ~Character();
	
private:
	std::shared_ptr<Entity> _entity;
	CHARACTERDATA _characterdata;
	CHARACTERPARAMETERDATA _cparamdata;
	bool _deathF;//���S���Ă��ĕ����̗P�\���Ȃ��ꍇ true:�@�����Ă� false:�@�����Ă��Ȃ�
};