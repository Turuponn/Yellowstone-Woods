#pragma once

#include "Geometori.h"

#include <memory>
#include <vector>
#include <string>

//�V�[���ɂ��O���[�o���ݒ�
struct WOLFINITINFO {
	int _hpframetimelimit;//�t���[�����Z�b�g�^�C�~���O�p�����[�^
	int _hpRecovery;//�񕜗�
};


class GameEngine;
class Wolf;
class CowManager;
class HPbar;
class ICON;
class Meat;
struct UIDATA;

class WolfManager {
private://Model
	void ModelInitialize(std::shared_ptr<GameEngine>& ge);
private://UI
	void UIInitialize(std::shared_ptr<GameEngine>& ge);
	//HP
	void HPbarHPUpdate(std::shared_ptr<GameEngine>& ge);//�v���C���[HP�ɂ���HPbar���X�V���܂�
	void HPUpdate(std::shared_ptr<GameEngine>& ge);
	//Meat
	void MeatUpdate(std::shared_ptr<GameEngine>& ge);

	void UIUpdate(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
public:
	WolfManager();
	~WolfManager();
	void Initialize(std::shared_ptr<GameEngine>& ge,const WOLFINITINFO& scenewolfinitinfo);
	void Update(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void AIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<CowManager>& cowmanager);
	const Vector3& GetWorldPos();
	/// <summary>
	/// ����H�ׂ��ꍇ true:�@�H�ׂ� false:�@�H�ׂĂ��Ȃ�
	/// </summary>
	/// <returns></returns>
	bool GetEatDeathMeatRecoveryF();

	//���݂�HP��Ԃ��܂�
	float GetHP();

private:
	std::shared_ptr<Wolf> _wolf;
	std::shared_ptr<HPbar> _hpbar;
	std::shared_ptr<HPbar> _hpbarframe;
	std::shared_ptr<ICON> _icon;
	std::shared_ptr <Meat> _meat;
	std::shared_ptr <UIDATA> _debugBeginmeatuidata;
	std::shared_ptr <UIDATA> _debugEndmeatuidata;
	int _nearcowindex;//��ԋ߂�����index
	WOLFINITINFO _info;//�������p�p�����[�^
	
	
	int _hpframetime;//hp�����p
	bool _meateatuianimF;//���ɂȂ����ꍇ true: �\�� false:��\��
	bool _eatdeathMeatRecoveryF;//�񕜗p�t���O true:�� false:�񕜂��Ȃ�
	
};