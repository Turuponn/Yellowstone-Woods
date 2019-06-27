#include "Character.h"
#include "GameEngine/GameEngine.h"
#include "Entity/Entity.h"

Character::Character() {
	init();
}
Character::~Character() {

}

void Character::init() {
	std::shared_ptr<Entity> e(new Entity());
	_entity = e;
}
std::shared_ptr<Entity>& Character::GetEntiy() {
	return _entity;
}