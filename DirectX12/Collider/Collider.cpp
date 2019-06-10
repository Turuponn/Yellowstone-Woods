#include "Collider.h"
using namespace DirectX;

Collider::Collider() {

}
Collider::~Collider() {

}
bool Collider::AABBHitCheck(const Vector3& point) {
	if (point.x < _box.min.x) {
		return false;
	}
	if (point.x > _box.max.x) {
		return false;
	}
	if (point.y < _box.min.y) {
		return false;
	}
	if (point.y > _box.max.y) {
		return false;
	}
	if (point.z < _box.min.z) {
		return false;
	}
	if (point.z > _box.max.z) {
		return false;
	}
	
	return true;//hit
}
bool Collider::AABBHitCheck_BB(const AABB& box2) {
	if (_box.min.x + 5 > box2.max.x+5) { return false; }
	if (_box.max.x < box2.min.x) { return false; }
	if (_box.min.y > box2.max.y) { return false; }
	if (_box.max.y < box2.min.y) { return false; }
	if (_box.min.z > box2.max.z) { return false; }
	if (_box.max.z < box2.min.z) { return false; }

	return true;//hit
}
void Collider::UpdateAABBMinMax(const Vector3& point) {
	_box.max.x = XMMax(_box.max.x,point.x);
	_box.max.y = XMMax(_box.max.y, point.y);
	_box.max.z = XMMax(_box.max.z, point.z);
	_box.min.x = XMMin(_box.min.x, point.x);
	_box.min.y = XMMin(_box.min.y, point.y);
	_box.min.z = XMMin(_box.min.z, point.z);
}
AABB Collider::GetAABB() {
	return _box;
}