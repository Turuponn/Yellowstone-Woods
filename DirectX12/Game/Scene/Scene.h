#pragma once

#include "Geometori.h"
#include <memory>
#include <string>
#include <vector>

class GameEngine;

struct CAMERAINFO {
	Vector3 postion;//カメラ移動量
	Vector3 rotate;//カメラ回転量
	float camrenge;//カメラ距離
	float cam_renge_y;//カメラLook_Y座標
	float cam_sppeed;//カメラ移動速度
	std::string maincameraname;//メインのカメラ名

	CAMERAINFO() :postion(Vector3(0,0,0)), rotate(Vector3(0, 0, 0)), camrenge(1.0f), cam_renge_y(1.0f), cam_sppeed(0), maincameraname(""){

	};
	CAMERAINFO(
		const Vector3& newpos,
		const Vector3& newrotate,
		const float newcamrenge,
		const float newcamrengey,
		const float newcamspeed,
		const std::string& newcamerahandle
	) :
		postion(newpos),
		rotate(newrotate),
		camrenge(newcamrenge),
		cam_renge_y(newcamrengey),
		cam_sppeed(newcamspeed),
		maincameraname(newcamerahandle)
	{

	};
	~CAMERAINFO() {

	};
};

class Scene {
public:
	Scene();
	virtual ~Scene();//メモリリーク対策virtual
	virtual void Init(std::shared_ptr<GameEngine>& ge) = 0;
	virtual int Update(std::shared_ptr<GameEngine>& ge) = 0;
	

private:
};
