#pragma once

#include "GameUI/GameUI.h"

class GameEngine;



struct HPINFO {
	int hp;//����HP
	int maxhp;//�ő�HP
};


class HPbar : public GameUI{
public:
	HPbar();
	~HPbar();

	void CreateUI(std::shared_ptr<GameEngine>& ge, const UIDATA& ddata,const std::string& filepath);
	void DrawUI(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void SetUIData(const UIDATA& uidata);
	const UIDATA& GetUIData();


	/// <summary>
	/// HP�o�[��HP�ʂ������Ń����N�����܂�
	/// </summary>
	void ReduceUpdate(std::shared_ptr<GameEngine>& ge, const HPINFO& hinfo);

private:
	UIDATA _defaultuidata;
	UIDATA _uidata;
};