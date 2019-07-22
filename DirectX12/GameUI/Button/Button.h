#pragma once


#include "GameUI/GameUI.h"


class Button : public GameUI {
public:
	Button();
	~Button();

	void Create(std::shared_ptr<GameEngine>& ge, const UIDATA& uidata, const float countspeed, const std::string& filepath);
	/// <summary>
	/// �Z���N�g���͓_�ł����܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="cameraname"></param>
	/// <param name="selectF">true: �_�� false: ��_��</param>
	void DrawSelect(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, bool selectF);
	/// <summary>
	/// �Z���N�g�����J�[�\���ɍ��킹�ăL�[�{�[�h���������܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="cameraname"></param>
	/// <param name="selectF"></param>
	void DrawSelectPush(std::shared_ptr<GameEngine>& ge, const std::string& cameraname, bool selectF);
	/// <summary>
	/// ���ʂɕ`�悵�܂�
	/// </summary>
	/// <param name="ge"></param>
	/// <param name="cameraname"></param>
	/// <param name="selectF"></param>
	void Draw(std::shared_ptr<GameEngine>& ge, const std::string& cameraname);
	void SetData(const UIDATA& uidata);
	const UIDATA& GetData();


private:
	UIDATA _data;
	float _selectcolorpattern_a;//�Z���N�g���J���[�J�E���^
	float _scolorcount;
};