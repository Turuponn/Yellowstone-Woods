#include "Map.h"
#include "GameEngine/GameEngine.h"
#include "Character/Character.h"
using namespace DirectX;
using namespace std;
Map::Map() {
	_maphandle = 0;
	_floorhandle = 0;
}
Map::~Map() {

}
void Map::Initialize(std::shared_ptr<GameEngine>& ge) {
	//Trees
	_maphandle = ge->LoadFBXModelDR("resource/FBX/TreeMap.fbx", false);
	_mapscale = Vector3(17, 17, 17);
	_mappostion = Vector3(0,42,0);
	ge->SetFBXScaleQuaternion(_maphandle, _mapscale);
	ge->SetFBXRotateQuaternion(_maphandle, Vector3(1, 0, 0), XMConvertToRadians(-90));
	//Floor
	_floorhandle = ge->LoadFBXModelDR("resource/FBX/floor.fbx", false);
	_floorscale = Vector3(1000, GROUNDPOS_Y, 5000);
	_floorpostion = Vector3(0, 0, 500);
	ge->SetFBXScaleQuaternion(_floorhandle, _floorscale);
	ge->SetFBXRotateQuaternion(_floorhandle, Vector3(1, 0, 0), XMConvertToRadians(180));


}
void Map::Update(std::shared_ptr<GameEngine>& ge) {
	//Trees
	ge->SetFBXScaleQuaternion(_maphandle, _mapscale);
	ge->SetFBXPostionQuaternion(_maphandle, _mappostion);
	ge->DrawFBXModelDR(_maphandle);
	//Floor
	ge->SetFBXScaleQuaternion(_floorhandle, _floorscale);
	ge->SetFBXPostionQuaternion(_floorhandle, _floorpostion);
	ge->DrawFBXModelDR(_floorhandle);

#ifdef _DEBUG
	ge->imguiAddMeshVector(_mappostion, string("mappos"), string("mp_x"), string("mp_y"), string("mp_z"), 0.0f, 50.0f);
	ge->imguiAddMeshVector(_floorscale, string("floorscale"), string("fs_x"), string("fs_y"), string("fs_z"), 0.0f, 1000.0f);

#endif
}
Vector3 Map::GetFloorPostion() {
	return _floorpostion;
}
Vector3 Map::GetTreesPostion() {
	return _mappostion;
}
