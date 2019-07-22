#pragma once



#include "Geometori.h"
#include <memory>
#include <string>


struct UIDATA {
	Vector3 pos;
	Vector3 scale;
	Vector3 rotateorigin;
	Vector4 color;
	float rotate;
	UIDATA() : 
		pos(0, 0, 0),
		scale(1,1,1),
		rotateorigin(0,0,0),
		color(1,1,1,1),
		rotate(0)
	{}
	UIDATA(
		const Vector3& newpos,
		const Vector3& newscale,
		const Vector3& newrotateorigin,
		const Vector4& newcolor,
		const float	   newrotate
	) :
		pos(newpos),
		scale(newscale),
		rotateorigin(newrotateorigin),
		color(newcolor),
		rotate(newrotate)
	{}
	~UIDATA() {}



};

class GameEngine;


class GameUI {
private:
	void UpdateInfo(std::shared_ptr<GameEngine>& ge,const UIDATA& data);
protected:
	GameUI();
	/// <summary>
	/// çÏê¨ÇµÇ‹Ç∑
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="filepath"></param>
	void CreateUI(std::shared_ptr<GameEngine>& ge, const std::string& filepath);
	/// <summary>
	/// ï`âÊÇµÇ‹Ç∑
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="data"></param>
	void DrawUI(std::shared_ptr<GameEngine>& ge, const UIDATA& data, const std::string& cameraname);

public:
	virtual ~GameUI();
	
	
	

private:
	int _uihandle;

};