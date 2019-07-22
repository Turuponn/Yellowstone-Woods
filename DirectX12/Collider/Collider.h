#pragma once

#include "Geometori.h"
#include <vector>


struct AABB {
	Vector3 min;
	Vector3 max;
};


class Collider {
public:
	Collider();
	~Collider();

public://AABB
	//2�_���玲���s�o�E���f�B���O�{�b�N�X�ɂ��Փ˔�����s���܂�
	bool AABBHitCheck(const Vector3& point);
	bool AABBHitCheck_BB(const AABB& box2);
	//AABB���\�z���܂�
	void UpdateAABBMinMax(const Vector3& point);

	AABB GetAABB();

private://AABB
	AABB _box;

};
