#pragma once

#include "MapLevel/MapLevel.h"

class Map {
public:
	Map();
	virtual ~Map();
	virtual void Initialize(std::shared_ptr<GameEngine>& ge);
	virtual void Update(std::shared_ptr<GameEngine>& ge);
	

	Vector3 GetFloorPostion();
	Vector3 GetTreesPostion();

private:
	int _maphandle;
	int _floorhandle;
	Vector3 _mapscale;
	Vector3 _mappostion;
	Vector3 _floorscale;
	Vector3 _floorpostion;
	Vector3 _floorrotate;

};