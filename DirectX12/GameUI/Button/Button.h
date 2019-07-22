#pragma once


#include "GameUI/GameUI.h"


class Button : public GameUI {
public:
	Button();
	~Button();

	void Create(std::shared_ptr<GameEngine>& ge, const UIDATA& uidata, const float countspeed, const std::string& filepath);
	/// <summary>
	/// セレクト中は点滅させます
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="cameraname"></param>
	/// <param name="selectF">true: 点滅 false: 非点滅</param>
	void DrawSelect(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, bool selectF);
	/// <summary>
	/// セレクトしたカーソルに合わせてキーボードを押させます
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="cameraname"></param>
	/// <param name="selectF"></param>
	void DrawSelectPush(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, bool selectF);
	/// <summary>
	/// 普通に描画します
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="cameraname"></param>
	/// <param name="selectF"></param>
	void Draw(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void SetData(const UIDATA& uidata);
	const UIDATA& GetData();


private:
	UIDATA _data;
	float _selectcolorpattern_a;//セレクト中カラーカウンタ
	float _scolorcount;
};