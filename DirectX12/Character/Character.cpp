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
	//Status:Å@Alive
	_deathF = true;
}
std::shared_ptr<Entity>& Character::GetEntiy() {
	return _entity;
}
bool Character::GetDeathF() {
	return _deathF;
}
void Character::SetDeathF(bool newstatus) {
	_deathF = newstatus;
}
const CHARACTERDATA& Character::GetCharacterData() {
	return _characterdata;
}
void Character::SetCharacterData(const CHARACTERDATA& newcharacterdata) {
	_characterdata = newcharacterdata;
}
void Character::SetCharacterParameterData(const CHARACTERPARAMETERDATA& cparamdata) {
	_cparamdata = cparamdata;
}
const CHARACTERPARAMETERDATA& Character::GetCharacterParameterData() {
	return _cparamdata;
}