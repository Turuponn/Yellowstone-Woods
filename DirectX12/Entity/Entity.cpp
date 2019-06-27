#include "Entity.h"

Entity::Entity() {

}
Entity::~Entity() {

}

float Entity::Distance(const Vector3& pos,const Vector3& pos2) {
	Vector3 dis = {};
	dis.x = (pos.x+pos2.x)*(pos.x + pos2.x);
	dis.y = (pos.y + pos2.y)*(pos.y + pos2.y);
	dis.z = (pos.z+ pos2.z)*(pos.z + pos2.z);
	return sqrt(dis.x+ dis.y+ dis.z);
}