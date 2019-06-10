#pragma once


#include "MapLevel/MapLevel.h"

#define TREEMAX 5

class Tree : public MapLevel {
public:
	Tree();
	virtual ~Tree();


	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	virtual void Update(std::shared_ptr<GameEngine>& ge);
	std::vector<Vector3>& GetPostion();
	std::vector<Vector3>& GetPostion_Offset();
private:
	std::vector<int> _treehandles;//判定が必要なオブジェクトの最大数
	std::vector<Vector3> _treePostions;
	std::vector<Vector3> _treePostions_offset;//幅高さを補正した値
	std::vector<Vector3> _treeScale;
	Vector3 _offsetpos;
	Vector3 _offsetscale;

	Vector3 _offsettreepos1;
	Vector3 _offsettreepos2;
	Vector3 _offsettreepos3;
	Vector3 _offsettreepos4;
	Vector3 _offsettreepos5;
};