#include "Tree.h"
#include "GameEngine/GameEngine.h"
using namespace DirectX;
using namespace std;


namespace {
	vector<string> trees;
}

Tree::Tree() {
	
}
Tree::~Tree() {

}
void Tree::Initialize(std::shared_ptr<GameEngine>& ge) {

	//判定が必要な木のロード
	_treehandles.resize(TREEMAX);
	_treePostions.resize(TREEMAX);
	_treeScale.resize(TREEMAX);
	trees.resize(TREEMAX);

	for (int i = 0; i < TREEMAX; i++) {
		auto str = std::to_string(i);
		trees[i] = "tree"+ str;
		ge->LoadFBXModelDR(trees[i],"resource/FBX/Tree.fbx", false);
		_treeScale[i] = Vector3(1, 1, 1);
		ge->SetFBXScaleQuaternion(trees[i], _treeScale[i]);
		ge->SetFBXRotateQuaternion(trees[i], Vector3(1, 0, 0), XMConvertToRadians(-90));
		
	}
	_treePostions[0] = Vector3(40, 0, 0);
	_treePostions[1] = Vector3(0, 0, -50);
	_treePostions[2] = Vector3(-40, 0, 0);
	_treePostions[3] = Vector3(-9, 0, 29);
	_treePostions[4] = Vector3(17, 0, 29);
	//木オブジェのずらす座標の全体指定
	_offsetpos = Vector3(0, 0, 0);
	_offsetpos.x = -11;
	_offsetpos.y = 4;
	_offsetpos.z = 0;
	//上の座標ずらし量
	_moveoffset_y = _treeScale[0].y+1;//scale + offset

	
}
void Tree::Update(std::shared_ptr<GameEngine>& ge) {

	
	//木を配置する
	for (int i = 0; i < TREEMAX; i++) {
		ge->SetFBXPostionQuaternion(trees[i], Vector3(_treePostions[i].x+ _offsetpos.x, _treePostions[i].y+ _offsetpos.y, _treePostions[i].z+ _offsetpos.z));
		ge->SetFBXScaleQuaternion(trees[i], _treeScale[i]+ _offsetscale);
		ge->DrawFBXModelDR(trees[i]);
	}

#ifdef _DEBUG
	ge->imguiAddMeshFloat(_moveoffset_y, string("o_y"), string("_moveoffset_y"), 0.0f, 30.0f);
#endif
}
std::vector<Vector3>& Tree::GetPostion() {
	return _treePostions;
}
std::vector<Vector3>& Tree::GetPostion_Offset() {
	_treePostions_offset = _treePostions;

	//座標オフセットを加味した中心座標から上へoffsetした座標を返す
	_treePostions_offset[0] = Vector3((_treePostions[0].x + _offsetpos.x), (_treePostions[0].y+ _offsetpos.y) + _moveoffset_y, (_treePostions[0].z+ _offsetpos.z));
	_treePostions_offset[1] = Vector3((_treePostions[1].x+ _offsetpos.x), (_treePostions[1].y+ _offsetpos.y) + _moveoffset_y, (_treePostions[1].z+ _offsetpos.z));
	_treePostions_offset[2] = Vector3((_treePostions[2].x+ _offsetpos.x), (_treePostions[2].y+ _offsetpos.y)+ _moveoffset_y, (_treePostions[2].z+ _offsetpos.z));
	_treePostions_offset[3] = Vector3((_treePostions[3].x+ _offsetpos.x), (_treePostions[3].y+ _offsetpos.y)+ _moveoffset_y, (_treePostions[3].z+ _offsetpos.z));
	_treePostions_offset[4] = Vector3((_treePostions[4].x+ _offsetpos.x), (_treePostions[4].y+ _offsetpos.y)+ _moveoffset_y, (_treePostions[4].z+ _offsetpos.z));

	return _treePostions_offset;
}