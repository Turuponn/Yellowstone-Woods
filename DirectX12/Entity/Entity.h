#pragma once


#include "Geometori.h"

class Entity {
public:
	Entity();
	~Entity();

	/// <summary>
	/// 2“_ŠÔ‚Ì‹——£‚ð•Ô‚·
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="pos2"></param>
	/// <returns></returns>
	float Distance(const Vector3& pos,const Vector3& pos2);

private:

};