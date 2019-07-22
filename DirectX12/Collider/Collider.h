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
	//2点から軸並行バウンディングボックスによる衝突判定を行います
	bool AABBHitCheck(const Vector3& point);
	bool AABBHitCheck_BB(const AABB& box2);
	//AABBを構築します
	void UpdateAABBMinMax(const Vector3& point);

	AABB GetAABB();

private://AABB
	AABB _box;

};
