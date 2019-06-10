#include "Tree.h"
#include "GameEngine/GameEngine.h"
using namespace DirectX;
using namespace std;

Tree::Tree() {
	
}
Tree::~Tree() {

}
void Tree::Initialize(std::shared_ptr<GameEngine>& ge) {

	//判定が必要な木のロード
	_treehandles.resize(TREEMAX);
	_treePostions.resize(TREEMAX);
	_treeScale.resize(TREEMAX);
	for (int i = 0; i < TREEMAX; i++) {
		_treehandles[i] = ge->LoadFBXModelDR("resource/FBX/Tree.fbx", false);
		_treeScale[i] = Vector3(1, 1, 1);
		ge->SetFBXScaleQuaternion(_treehandles[i], _treeScale[i]);
		ge->SetFBXRotateQuaternion(_treehandles[i], Vector3(1, 0, 0), XMConvertToRadians(-90));
		
	}
	//_treePostions[0] = Vector3(8, 0, -4);
	//_treePostions[1] = Vector3(11, 0, 16);
	//_treePostions[2] = Vector3(4, 0, 4);
	//_treePostions[3] = Vector3(18, 0, 4);
	//_treePostions[4] = Vector3(12, 0, -4);
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



	
}
void Tree::Update(std::shared_ptr<GameEngine>& ge) {
	//_treePostions[0] = _offsettreepos1;
	//_treePostions[1] = _offsettreepos2;
	//_treePostions[2] = _offsettreepos3;
	//_treePostions[3] = _offsettreepos4;
	//_treePostions[4] = _offsettreepos5;
	
	//木を配置する
	for (int i = 0; i < TREEMAX; i++) {
		ge->SetFBXPostionQuaternion(_treehandles[i], Vector3(_treePostions[i].x+ _offsetpos.x, _treePostions[i].y+ _offsetpos.y, _treePostions[i].z+ _offsetpos.z));
		ge->SetFBXScaleQuaternion(_treehandles[i], _treeScale[i]+ _offsetscale);
		ge->DrawFBXModelDR(_treehandles[i]);
	}

	/*ge->imguiAddMeshVector(_offsetpos, string("Alltreeofsetpostion"), string("ofsetp_x"), string("ofsetp_y"), string("ofsetp_z"), -50.0f, 50.0f);
	ge->imguiAddMeshVector(_offsetscale, string("ofsetscale"), string("ofsets_x"), string("ofsets_y"), string("ofsets_z"), 0.0f, 50.0f);
	ge->imguiAddMeshVector(_offsettreepos1, string("tree1ofsetpostion"), string("ofset1p_x"), string("ofset1p_y"), string("ofset1p_z"), -50.0f, 50.0f);
	ge->imguiAddMeshVector(_offsettreepos2, string("tree2ofsetpostion"), string("ofset2p_x"), string("ofset2p_y"), string("ofset2p_z"), -50.0f, 50.0f);
	ge->imguiAddMeshVector(_offsettreepos3, string("tree3ofsetpostion"), string("ofset3p_x"), string("ofset3p_y"), string("ofset3p_z"), -50.0f, 50.0f);
	ge->imguiAddMeshVector(_offsettreepos4, string("tree4ofsetpostion"), string("ofset4p_x"), string("ofset4p_y"), string("ofset4p_z"), -50.0f, 50.0f);
	ge->imguiAddMeshVector(_offsettreepos5, string("tree5ofsetpostion"), string("ofset5p_x"), string("ofset5p_y"), string("ofset5p_z"), -50.0f, 50.0f);*/
}
std::vector<Vector3>& Tree::GetPostion() {
	return _treePostions;
}
std::vector<Vector3>& Tree::GetPostion_Offset() {
	_treePostions_offset = _treePostions;
	const int offsety = 6;
	const int offsetx = -11;
	_treePostions_offset[0] = Vector3(_treePostions[0].x+ offsetx, _treePostions[0].y+ offsety, _treePostions[0].z);
	_treePostions_offset[1] = Vector3(_treePostions[1].x+ offsetx, _treePostions[1].y + offsety, _treePostions[1].z);
	_treePostions_offset[2] = Vector3(_treePostions[2].x+ offsetx, _treePostions[2].y + offsety, _treePostions[2].z);
	_treePostions_offset[3] = Vector3(_treePostions[3].x+ offsetx, _treePostions[3].y + offsety, _treePostions[3].z);
	_treePostions_offset[4] = Vector3(_treePostions[4].x+ offsetx, _treePostions[4].y + offsety, _treePostions[4].z);

	return _treePostions_offset;
}