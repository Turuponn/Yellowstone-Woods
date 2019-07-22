#pragma once

#include "Geometori.h"
#include <memory>
#include <string>
#include <vector>

class GameEngine;

struct CAMERAINFO {
	Vector3 postion;//�J�����ړ���
	Vector3 rotate;//�J������]��
	float camrenge;//�J��������
	float cam_renge_y;//�J����Look_Y���W
	float cam_sppeed;//�J�����ړ����x
	std::string maincameraname;//���C���̃J������

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
	virtual ~Scene();//���������[�N�΍�virtual
	virtual void Init(std::shared_ptr<GameEngine>& ge) = 0;
	virtual int Update(std::shared_ptr<GameEngine>& ge) = 0;
	

private:
};
