#pragma once

#include "Geometori.h"
#include <memory>
#include <vector>
#include <string>

class GameEngine;
class Player;
class HPbar;
class ICON;
class Meat;
class WolfManager;


struct UIDATA;



//�V�[���ɂ��O���[�o���ݒ�
struct PLAYERINITINFO {
	int _hpframetimelimit;//�t���[�����Z�b�g�^�C�~���O�p�����[�^
	int _hpRecovery;//HP�񕜗�
};

class PlayerManager {
private://Model
	void ModelInitialize(std::shared_ptr<GameEngine>& ge);

private://UI
	void UIInitialize(std::shared_ptr<GameEngine>& ge);
	//HP
	void HPbarHPUpdate(std::shared_ptr<GameEngine>& ge);//�v���C���[HP�ɂ���HPbar���X�V���܂�
	void HPUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf);
	//Meat
	void MeatUpdate(std::shared_ptr<GameEngine>& ge);


	void UIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf,const std::string& cameraname);
public:
	PlayerManager();
	~PlayerManager();
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(std::shared_ptr<GameEngine>& ge, const PLAYERINITINFO& sceneplayerinitinfo);
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolf, const std::string& cameraname);
	/// <summary>
	/// ���[���h���W��Ԃ��܂�
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos();
	/// <summary>
	/// ���ԃ{�^����Ԃ��܂� true: �����ꂽ false: ������Ă��Ȃ�
	/// </summary>
	/// <returns></returns>
	bool GetPushShoutF();
	/// <summary>
	/// ���f���ɑ΂������_�������悤�ɉ�]�����܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="lookpoint"></param>
	void LookAt(std::shared_ptr<GameEngine>& ge,const Vector3& lookpoint);
	/// <summary>
	/// ����HP��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetHP();
private:
	std::shared_ptr<Player> _player;
	std::shared_ptr<HPbar> _hpbar;
	std::shared_ptr<HPbar> _hpbarframe;
	std::shared_ptr<ICON> _icon;
	std::shared_ptr<Meat> _meathalf;
	std::shared_ptr<UIDATA> _debugmeathalfbegindata;
	std::shared_ptr<UIDATA> _debugmeathalfenddata;
	
	int _hpframetime;//hp�����p
	PLAYERINITINFO _info;
	bool _meateatuianimF;//�����H�׃A�j���[�V�����̍Đ� true:�Đ����� false:
};
