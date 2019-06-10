#include "GameScene.h"
#include "WindowInit.h"
#include <string>
#include <DirectXMath.h>
#include "Collider/Collider.h"
#include "GameEngine\GameEngine.h"
#include "Character/Player/Player.h"
#include "MapLevel/Tree/Tree.h"
#include "MapLevel/Map/Map.h"
#include "Character/Wolf/Wolf.h"
#include "Character/Cow/Cow.h"

using namespace std;
using namespace DirectX;




const std::string _cubeFilepath = "resource/CubeMapModel/shpiae.fbx";


int directionallighthandle = 0;//平行光源
int camera1Handle = 0;//カメラ
int cubemaphandle = 0;




Vector3 lightdir = {1.0f,1.0f,0.5f};

Vector3 cubemapscale = {5000.0f,5000.0f,5000.0f};
Vector3 cubemapPostion = {0,0,0};









float lightdircounter = 0.0f;

float lightintensity = 1.4f;//ライト強さ
float angleTestparam = 0.0f;
float Testcount = 0;




std::string cubemap_filepath = "resource/Texture/SkyBox/panorama2048.dds";



GameScene::GameScene(){

}
GameScene::~GameScene() {

}


float cam_sppeed = 0.05f;



void GameScene::Initialize(WindowInit& windowinstance) {
	std::shared_ptr<GameEngine> ge(new GameEngine());
	_ge = ge;
	_ge->Initialize(windowinstance);
	//ライト初期化
	directionallighthandle = _ge->DirectionalLightInit();
	_ge->DirectionallightPos(directionallighthandle, lightdir);
	//CubeMap
	cubemaphandle = _ge->LoadCubeMap(cubemap_filepath, _cubeFilepath);
	_ge->SetCubeMapRotateQuaternion(cubemaphandle, Vector3(1, 0, 0), 0);
	//カメラ生成
	camera1Handle = _ge->CreateCameraHandle();
	_ge->SetCameraPosition(camera1Handle, 1.6f, 0.0, -10.6f);
		
	//Player
	std::shared_ptr<Player> player(new Player());
	_player = player;
	_player->Initialize(_ge);
	//MapObj: trees
	std::shared_ptr<Tree> tree(new Tree());
	_tree = tree;
	_tree->Initialize(_ge);
	//Map
	std::shared_ptr<Map> map(new Map());
	_map = map;
	_map->Initialize(_ge);
	//狼
	std::shared_ptr<Wolf> wolf(new Wolf());
	_wolf = wolf;
	_wolf->Initialize(_ge);
	std::shared_ptr<Cow> cow(new Cow());
	_cow = cow;
	_cow->Initialize(_ge);
}

//回転量
Vector3 c_rotate = {0,0,0};
float camrenge = 23;
float moveindex = 0;

void GameScene::Updata() {
	_ge->Run();
#ifdef _DEBUG
	_ge->imguiPre();
#endif
	
	//カメラ
	_ge->SetCameraRotate(camera1Handle, _player->GetPlayerPos().x, 10, _player->GetPlayerPos().z, c_rotate.x, c_rotate.y, c_rotate.z, camrenge);
	_ge->UpdateCamera(camera1Handle);


	//ライト
	_ge->DirectionallightUpdate(directionallighthandle);//平行光源設置
	_ge->DirectionallightPos(directionallighthandle, lightdir);//平行光源
	_ge->DirectionallightIntensity(directionallighthandle, lightintensity);
	


	//GeometoryStage===========================
	//1pass----------------GbufferRender
	_ge->DR_Pre();

	//CubeMap
	_ge->SetCubeMapPostionQuaternion(cubemaphandle, cubemapPostion);
	_ge->SetCubeMapScaleQuaternion(cubemaphandle, cubemapscale);
	_ge->PreCubeMap(cubemaphandle);

	
	_player->Update(_ge, camera1Handle);
	_wolf->Update(_ge);
	_cow->Update(_ge);
	_tree->Update(_ge);
	_player->SetPlayerPos(Vector3(_tree->GetPostion_Offset()[(int)moveindex].x, _tree->GetPostion_Offset()[(int)moveindex].y, _tree->GetPostion_Offset()[(int)moveindex].z));
	_map->Update(_ge);



	_ge->DR_Post();

	//LightingStage==========================
	//1pass---------------DeferredShading
	_ge->PreDeferredShadingRender(camera1Handle);
	_ge->PostDeferredShadingRender();
	//シェーダー側
	//PostProsessStage=======================
	//1pass---------------PostEffect
	_ge->PrePostProsessRender(camera1Handle);
	_ge->PostPostProsessRender();
	//ForwardRenderingStage==================
	_ge->Render();
	//Draw
	_ge->DrawScreen(camera1Handle);

#ifdef _DEBUG
	//ライト
	_ge->imguiAddMeshVector(lightdir, string("LightDir"), string("light_d_x"), string("light_d_y"), string("light_d_z"), -1.0f, 1.0f);
	_ge->imguiAddMeshFloat(lightintensity, string("lightintensity"), string("l_intensity"), 0.0f, 10.0f);
	//CubeMap
	_ge->imguiCubeMapScale(cubemapscale);
	//カメラ
	_ge->imguiAddMeshFloat(camrenge, string("camrenge"), string("renge"), -50.0f, 50.0f);
	//MoveTest
	_ge->imguiAddMeshFloat(moveindex, string("moveindex"), string("idx"), 0.0f, 4.0f);
#endif
	
	
	//カメラ回転
	if (_ge->CheckHitKey(DIK_UP) == 1) {
		c_rotate.x += cam_sppeed;
	}
	if (_ge->CheckHitKey(DIK_DOWN) == 1) {
		c_rotate.x -= cam_sppeed;
	}
	if (_ge->CheckHitKey(DIK_RIGHT) == 1) {
		c_rotate.y -= cam_sppeed;
	}
	if (_ge->CheckHitKey(DIK_LEFT) == 1) {
		c_rotate.y += cam_sppeed;
	}
#ifdef _DEBUG
	_ge->imguiPost();
#endif
	_ge->ScreenFilip();
}
