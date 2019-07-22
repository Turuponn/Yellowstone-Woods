#include "CowManager.h"
#include "GameEngine/GameEngine.h"
#include "CowCharacter/Cow.h"
#include "Entity/Entity.h"
#include "Character/Wolf/WolfManager.h"
#include <random>
using namespace std;
namespace {
	const int DISRUNMAX = 15;//������܂ł̏�ԑJ�ڗp�͈�
	const int DISDEATHMAX = 6;//���S����p�����萔
	const int DISMOVEMAX = 10;
	const int MAXHP = 100;
	const int INITINDEX = -1;
	const int ALIVERATE = 1;//�����J�E���g���[�g
	const int ALIVERATEMAX = 3;//�����J�E���g�ő吔
	const int INITPOSMAX = 40;
	const int ESCAPEDISMAX = 50;
	const int SCALEMAX = 8;
	const int SCALEMIN = 1;

	vector<string> modelnamecows;
}

CowManager::CowManager() {
	_nearcowindex = INITINDEX;
	_frameTime = 0;
}
CowManager::~CowManager() {

}
void CowManager::Initialize(std::shared_ptr<GameEngine>& ge,const int maxcows) {
	_maxcows = maxcows;
	_dises.resize(_maxcows);
	modelnamecows.resize(_maxcows);
	//create new Cows
	_cows.resize(maxcows);
	CHARACTERPARAMETERDATA paramdata = {};
	paramdata.hp = MAXHP;
	for (int i = 0; i < maxcows; i++) {
		std::shared_ptr<Cow> c(new Cow);
		_cows[i] = c;
		WORLDDATA data = {};
		auto s = ge->GetRandFloatRengeMt(SCALEMIN, SCALEMAX);
		data.scale = Vector3(s, s, s);
		data.pos = Vector3(
			ge->GetRandFloatRengeMt(-(INITPOSMAX), INITPOSMAX),
			GROUNDPOS_Y + data.scale.y,
			ge->GetRandFloatRengeMt(-(INITPOSMAX), INITPOSMAX)
		);
		
		auto str = std::to_string(i);
		modelnamecows[i] = "cow"+ str;
		_cows[i]->Initialize(ge, data, paramdata, modelnamecows[i]);
	}
	std::shared_ptr<Entity> entity(new Entity());
	_entity = entity;
}
void CowManager::Update(std::shared_ptr<GameEngine>& ge) {
	RANDPACKAGE rpackage = {};
	auto s = ge->GetRandFloatRengeMt(SCALEMIN, SCALEMAX);
	rpackage.randscale = { s, s, s };
	rpackage.randpos = Vector3(
		ge->GetRandFloatRengeMt(-(INITPOSMAX), INITPOSMAX),
		GROUNDPOS_Y + rpackage.randscale.y,
		ge->GetRandFloatRengeMt(-(INITPOSMAX), INITPOSMAX)
	);
	rpackage.frametimecountmax = 1;
	for (int i = 0; i < _maxcows; i++) {
		_cows[i]->Update(modelnamecows[i],ge, ESCAPEDISMAX, rpackage);
	}
}
void CowManager::AIUpdate(std::shared_ptr<GameEngine>& ge, std::shared_ptr<WolfManager>& wolfmanager) {
	_frameTime++;
	for (int i = 0; i < _maxcows; i++) {
		_cows[i]->AIUpdate(modelnamecows[i],ge, wolfmanager->GetWorldPos(), DISRUNMAX, DISMOVEMAX, DISDEATHMAX);
	}
}
const int CowManager::GetNearCow(const Vector3& targetpos) {
	bool notindex = false;
	//��ԋ߂����W��Ԃ�
	for (int i = 0; i < _maxcows; i++) {
		_dises[i] = 99999;
		if (_cows[i]->GetCowDeathF() == true) {//�����Ă�������index��Ԃ�
			auto d = _entity->Distance(_cows[i]->GetWorldPos(), targetpos);
			_dises[i] = d;
			notindex = true;
		}
	}
	size_t index = -1;
	if (notindex != false) {//�S�ł����ꍇ�T�������Ȃ�
		if (!(_dises.empty())) {
			auto it = std::min_element(_dises.begin(), _dises.end());
			index = std::distance(_dises.begin(), it);
		}
	}


	return index;
}
void CowManager::MoveShout(std::shared_ptr<GameEngine>& ge,const Vector3& playerpos) {
	//��ԋ߂����W�������Ă���Ώۂ݂̂ɑ΂��A���S�ֈړ�����悤�ɑ���
	auto index = GetNearCow(playerpos);
	if (index != INITINDEX) {
		if (_nearcowindex == INITINDEX) {//������
			_nearcowindex = index;
		}
		if (GetDeath(_nearcowindex) == false) {//����ł����ꍇ�X�V
			_nearcowindex = index;
		}
	}
	else {//�T���I�������ꍇ�Ō��index���g�p����

	}
	for (int i = 0; i < _maxcows; i++) {
		_cows[_nearcowindex]->MoveApproachforward(modelnamecows[i], ge, Vector3(0, 0, 0));
	}
}
const Vector3& CowManager::GetWorldPos(const int index) {
	return  _cows[index]->GetWorldPos();
}
bool CowManager::GetDeath(const int index) {
	return _cows[index]->GetCowDeathF();
}
