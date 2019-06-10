#pragma once

#include "Geometori.h"
#include <memory>
#include <vector>
#include <string>

class GameEngine;

class MapLevel {
protected:
	MapLevel();
	virtual ~MapLevel();

	virtual void Initialize(std::shared_ptr<GameEngine>& ge) = 0;
	virtual void Update(std::shared_ptr<GameEngine>& ge) = 0;
	


private:
};