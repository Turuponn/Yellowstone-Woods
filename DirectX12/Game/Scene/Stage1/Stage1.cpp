#include "Stage1.h"
#include "GameEngine/GameEngine.h"
#include "Character/Player/PlayerManager.h"
#include "Character/Cow/CowManager.h"
#include "Character/Wolf/WolfManager.h"
#include "MapLevel/Tree/Tree.h"
#include "MapLevel/Map/Map.h"
#include "Entity/Entity.h"
#include "Game/Scene/EndScene/EndScene.h"//NextStage
#include "Game/GameScene.h"

using namespace std;

namespace {
	const string cubefilepath = "resource/CubeMapModel/shpiae.fbx";
	const string cubemapfilepath = "resource/Texture/SkyBox/panorama2048.dds";
	
	
	const string maincameraname = "���C���J����";
	const string cubemapname = "Skybox";
	const int SHOUTDIS = 5;//���т͈̔�
	const int HPFRAMETIMELIMIT = 30;//HP�̌���X�s�[�h�@���� 3 ������ő��Ƃ���
}



Stage1::Stage1() {
	_cubemaphandle = 0;
}
Stage1::~Stage1() {
	
}
void Stage1::Init(std::shared_ptr<GameEngine>& ge) {
	//�J��������
	ge->CreateCameraHandle(maincameraname);
	_caminfo.postion.x = 1.6f;
	_caminfo.postion.y = 0;
	_caminfo.postion.z = -10.6f;
	_caminfo.camrenge = 11;
	_caminfo.cam_renge_y = 4;
	_caminfo.cam_sppeed = 0.02f;
	_caminfo.maincameraname = maincameraname;
	ge->SetCameraPosition(maincameraname, _caminfo.postion);
	
	//CubeMap
	ge->LoadCubeMap(cubemapname,cubemapfilepath, cubefilepath);
	ge->SetCubeMapRotateQuaternion(cubemapname, Vector3(1, 0, 0), 0);
	_cubemapscale = {5000.0f,5000.0f,5000.0f};
	_cubemapPostion = {0,0,0};
	//Player
	std::shared_ptr<PlayerManager> player(new PlayerManager());
	_player = player;
	PLAYERINITINFO playerinfo = {};
	playerinfo._hpframetimelimit = HPFRAMETIMELIMIT/2;
	playerinfo._hpRecovery = 5;
	_player->Initialize(ge,playerinfo);
	//MapObj: trees
	std::shared_ptr<Tree> tree(new Tree());
	_tree = tree;
	_tree->Initialize(ge);
	//Map
	std::shared_ptr<Map> map(new Map());
	_map = map;
	_map->Initialize(ge);
	//�T
	std::shared_ptr<WolfManager> wolf(new WolfManager());
	_wolf = wolf;
	WOLFINITINFO wolfinfo = {};
	wolfinfo._hpframetimelimit = HPFRAMETIMELIMIT;
	wolfinfo._hpRecovery = 10;
	_wolf->Initialize(ge, wolfinfo);
	//��
	std::shared_ptr<CowManager> cow(new CowManager());
	_cow = cow;
	_cow->Initialize(ge,5);
	//Entity
	std::shared_ptr<Entity> e(new Entity());
	_entity = e;

	
	/*
	�X�y�[�X�L�[�Ŗ����Ȃ�����������������Ȃ�
	*/

	
}
int Stage1::Update(std::shared_ptr<GameEngine>& ge) {

	//�J����
	ge->SetCameraRotate(
		maincameraname,
		Vector3(_player->GetWorldPos().x, _caminfo.cam_renge_y, _player->GetWorldPos().z),
		_caminfo.rotate,
		_caminfo.camrenge
	);
	ge->UpdateCamera(maincameraname);

	//Gbuffer
	ge->DR_Pre();

	//CubeMap
	ge->SetCubeMapPostionQuaternion(cubemapname, _cubemapPostion);
	ge->SetCubeMapScaleQuaternion(cubemapname, _cubemapscale);
	ge->PreCubeMap(cubemapname);
	

	//ModelsDrawUpdate
	_cow->AIUpdate(ge, _wolf);
	_wolf->AIUpdate(ge, _cow);

	_player->Update(ge, _wolf, _caminfo.maincameraname);
	_wolf->Update(ge, _caminfo.maincameraname);
	_cow->Update(ge);
	_tree->Update(ge);
	_map->Update(ge);

	ge->DR_Post();
	//Lighting
	ge->PreDeferredShadingRender(maincameraname);
	ge->PostDeferredShadingRender();
	//PostProsess
	ge->PrePostProsessRender(maincameraname);
	ge->PostPostProsessRender();
	//Draw
	ge->DrawScreen(maincameraname);


#ifdef _DEBUG
	//�J����
	ge->imguiAddMeshFloat(_caminfo.camrenge, string("camrenge"), string("renge"), -50.0f, 50.0f);
	ge->imguiAddMeshFloat(_caminfo.cam_renge_y, string("camrenge_y"), string("renge_y"), -30.0f, 30.0f);
#endif

	//�J������]
	if (ge->CheckHitKey(DIK_UP)) {
		_caminfo.rotate.x += _caminfo.cam_sppeed;
	}
	if (ge->CheckHitKey(DIK_DOWN)) {
		_caminfo.rotate.x -= _caminfo.cam_sppeed;
	}
	if (ge->CheckHitKey(DIK_RIGHT)) {
		_caminfo.rotate.y -= _caminfo.cam_sppeed;
	}
	if (ge->CheckHitKey(DIK_LEFT)) {
		_caminfo.rotate.y += _caminfo.cam_sppeed;
	}

	
	//Player
	//�؃I�u�W�F�N�g�͈͂ɋ߂Â�����
	for (auto t_gp : _tree->GetPostion_Offset()) {
		auto dis = _entity->Distance(_player->GetWorldPos(), t_gp);//����
		if (dis < SHOUTDIS) {//�V���E�g���\�ł���
			_player->LookAt(ge, Vector3(0, 0, 0));
			if (_player->GetPushShoutF()) {//�V���E�g���ꂽ��
				//��
				//�v���C���[�͈̔͂ɂ��鋍�͒��S�Ɍ�����
				_cow->MoveShout(ge, _player->GetWorldPos());
			}
		}
	}

	//���̃V�[������
	if (_wolf->GetHP() <= 0 || _player->GetHP() <= 0) {//HP���Ȃ��Ȃ�����
		GameScene::Instance().ChengeScene(new EndScene());//�I��
	}
	return 0;
}
