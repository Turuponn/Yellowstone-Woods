#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

class UIDefault;
class GameEngine;
class Button;
struct UIDATA;


class TitleUI {
private://Button
	void InitButton(std::shared_ptr<GameEngine>& ge);
	void UpdateButton(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
private://Cursor
	void CursorInput(std::shared_ptr<GameEngine>& ge);
	void CursorUpdate(std::shared_ptr<GameEngine>& ge);
private:
	//ui��ǉ����܂�
	void InsartPtrMaps(std::shared_ptr<GameEngine>& ge, const std::string& filepath,const std::string& item);
public:
	TitleUI();
	~TitleUI();

	void Init(std::shared_ptr<GameEngine>& ge);
	void DrawTitleUI(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	bool GetKeyButtonStartExit();

private:
	std::map<std::string, std::shared_ptr<UIDefault>> _uimap;
	std::shared_ptr<Button> _startbutton;
	std::shared_ptr<Button> _endbutton;
	std::shared_ptr<Button> _keybutton_up;
	std::shared_ptr<Button> _keybutton_down;
	std::shared_ptr<Button> _keybutton_left;
	std::shared_ptr<Button> _keybutton_right;
	std::shared_ptr<UIDATA> _ddata_mizutama;
	std::shared_ptr<UIDATA> _ddata_titlerogo;
	std::shared_ptr<UIDATA> _ddata_pleasespacekey;
	std::shared_ptr<UIDATA> _ddata_board;
	bool _select_startbuttonF;//�I�����ꂽ�ꍇ true:�I�����ꂽ false:�I������Ă��Ȃ�
	bool _select_endbuttonF;//�I�����ꂽ�ꍇ true:�I�����ꂽ false:�I������Ă��Ȃ�
	bool _select_keybutton_upF;//�I�����ꂽ�ꍇ true:�I�����ꂽ false:�I������Ă��Ȃ�
	bool _select_keybutton_downF;//�I�����ꂽ�ꍇ true:�I�����ꂽ false:�I������Ă��Ȃ�
	bool _select_keybutton_startexitF;//�I�����ꂽ�{�^���̃t���O���ǂ̃{�^���� true: start false: end
};