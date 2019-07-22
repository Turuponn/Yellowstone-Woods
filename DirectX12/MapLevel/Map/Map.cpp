#include "Map.h"
#include "GameEngine/GameEngine.h"
#include "Character/Character.h"
using namespace DirectX;
using namespace std;

namespace {
	const string modeltreemapname = "treemap";
	const string modelfloorname = "floor";

}


Map::Map() {

}
Map::~Map() {

}
void Map::Initialize(std::shared_ptr<GameEngine>& ge) {
	//Trees
	ge->LoadFBXModelDR(modeltreemapname,"resource/FBX/TreeMap.fbx", false);
	_mapscale = Vector3(17, 17, 17);
	_mappostion = Vector3(0,42,0);
	ge->SetFBXScaleQuaternion(modeltreemapname, _mapscale);
	ge->SetFBXRotateQuaternion(modeltreemapname, Vector3(1, 0, 0), XMConvertToRadians(-90));
	//Floor
	ge->LoadFBXModelDR(modelfloorname,"resource/FBX/floor.fbx", false);
	_floorscale = Vector3(1000, GROUNDPOS_Y, 5000);
	_floorpostion = Vector3(0, 0, 500);
	ge->SetFBXScaleQuaternion(modelfloorname, _floorscale);
	ge->SetFBXRotateQuaternion(modelfloorname, Vector3(1, 0, 0), XMConvertToRadians(180));


}
void Map::Update(std::shared_ptr<GameEngine>& ge) {
	//Trees
	ge->SetFBXScaleQuaternion(modeltreemapname, _mapscale);
	ge->SetFBXPostionQuaternion(modeltreemapname, _mappostion);
	ge->DrawFBXModelDR(modeltreemapname);
	//Floor
	ge->SetFBXScaleQuaternion(modelfloorname, _floorscale);
	ge->SetFBXPostionQuaternion(modelfloorname, _floorpostion);
	ge->DrawFBXModelDR(modelfloorname);

#ifdef _DEBUG
	ge->imguiAddMeshVector3(_mappostion, string("mappos"), string("mp_x"), string("mp_y"), string("mp_z"), 0.0f, 50.0f);
	ge->imguiAddMeshVector3(_floorscale, string("floorscale"), string("fs_x"), string("fs_y"), string("fs_z"), 0.0f, 1000.0f);

#endif
}
Vector3 Map::GetFloorPostion() {
	return _floorpostion;
}
Vector3 Map::GetTreesPostion() {
	return _mappostion;
}
