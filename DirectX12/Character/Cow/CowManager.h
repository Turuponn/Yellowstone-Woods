#pragma once

#include "Geometori.h"

#include <memory>
#include <vector>
#include <string>

class Cow;
class GameEngine;
class Entity;
class WolfManager;




class CowManager{
public:
	CowManager();
	~CowManager();
	void Initialize(std::shared_ptr<GameEngine>& ge,const int maxcows);
	void Update(std::shared_ptr<GameEngine>& ge);
	void AIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolfmanager);
	/// <summary>
	/// ��ԋ߂����̏���index��Ԃ��A�T�����I�������ꍇ-1��Ԃ�
	/// </summary>
	const int GetNearCow(const Vector3& targetpos);
	/// <summary>
	/// �w�肳�ꂽ���̍��W��Ԃ�
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWorldPos(const int index);
	/// <summary>
	/// �w�肳�ꂽ���̎��S�����Ԃ�
	/// </summary>
	/// <param name="index"></param>
	/// <returns>true: �����Ă��� false:����ł���</returns>
	bool GetDeath(const int index);
	/// <summary>
	/// �V���E�g��H�炤�Ƃ��̏���
	/// </summary>
	/// <param name="playerpos"></param>
	void MoveShout(std::shared_ptr<GameEngine>& ge,const Vector3& playerpos);
private:
	std::vector<std::shared_ptr<Cow>> _cows;
	std::shared_ptr<Entity> _entity;
	int _maxcows;
	std::vector<float> _dises;//��������
	int _nearcowindex;//��ԋ߂����W
	unsigned int _frameTime;
};