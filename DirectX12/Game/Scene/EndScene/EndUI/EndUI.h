#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

class UIDefault;
class GameEngine;
struct UIDATA;

class EndUI {
private:
	void CursorInput(std::shared_ptr<GameEngine>& ge);
	void CursorUpdate(std::shared_ptr<GameEngine>& ge);
private:
	//ui‚ð’Ç‰Á‚µ‚Ü‚·
	void InsartPtrMaps(std::shared_ptr<GameEngine>& ge, const std::string& filepath, const std::string& item);

public:
	EndUI();
	~EndUI();



	void Init(std::shared_ptr<GameEngine>& ge);
	void Draw(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);

private:
	std::map<std::string, std::shared_ptr<UIDefault>> _uimap;
	std::shared_ptr<UIDATA> _debugdata;
private:
};