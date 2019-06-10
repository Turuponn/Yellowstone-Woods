#include "Map.h"
#include "GameEngine/GameEngine.h"
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
	_maphandle = ge->LoadFBXModelDR("resource/FBX/map.fbx", false);
	_mapscale = Vector3(17, 17, 17);
	_mappostion = Vector3(0,0,0);
	ge->SetFBXScaleQuaternion(_maphandle, _mapscale);
	ge->SetFBXRotateQuaternion(_maphandle, Vector3(1, 0, 0), XMConvertToRadians(-90));
	//Floor
	_floorhandle = ge->LoadFBXModelDR("resource/FBX/floor.fbx", false);
	_floorscale = Vector3(50, 50, 1);
	_floorpostion = Vector3(0, 0, 0);
	ge->SetFBXScaleQuaternion(_floorhandle, _floorscale);
	ge->SetFBXRotateQuaternion(_floorhandle, Vector3(1, 0, 0), XMConvertToRadians(-90));


}
void Map::Update(std::shared_ptr<GameEngine>& ge) {
	//Trees
	_mappostion.x = 0;
	_mappostion.y = 22;
	_mappostion.z = 0;
	ge->SetFBXScaleQuaternion(_maphandle, _mapscale);
	ge->SetFBXPostionQuaternion(_maphandle, _mappostion);
	ge->DrawFBXModelDR(_maphandle);
	//Floor
	ge->SetFBXPostionQuaternion(_floorhandle, _floorpostion);
	ge->DrawFBXModelDR(_floorhandle);


	//ge->imguiAddMeshVector(_mapscale, string("mapscale"), string("ms_x"), string("ms_y"), string("ms_z"), 0.0f, 50.0f);
	//ge->imguiAddMeshVector(_mappostion, string("mappos"), string("mp_x"), string("mp_y"), string("mp_z"), 0.0f, 50.0f);
}
Vector3 Map::GetFloorPostion() {
	return _floorpostion;
}
Vector3 Map::GetTreesPostion() {
	return _mappostion;
}
