#include "TitleUI.h"
#include "constance.h"
#include "GameUI/UIDefault/UIDefault.h"
#include "GameUI/FadeInOut/FadeInOut.h"
#include "GameEngine/GameEngine.h"
#include "GameUI/Button/Button.h"

using namespace std;
namespace {
	const string titlebackgroundmizutamafilepath = "resource/Texture/title/BackGround/backGround2.png";
	const string titlebackGroundBoardFilepath = "resource/Texture/title/BackGround/backGround.png";
	const string startbuttonFilepath = "resource/Texture/Button/startbutton.png";
	const string endbuttonFilepath = "resource/Texture/Button/endbutton.png";
	const string titlerogoFilepath = "resource/Texture/title/Title.png";
	const string pleasepushFilepath = "resource/Texture/title/pleasepushspacekey.png";
	//KeyBoard
	const string upbuttonFilepath = "resource/Texture/Keyboard/up.png";
	const string downbuttonFilepath = "resource/Texture/Keyboard/Down.png";
	const string leftbuttonFilepath = "resource/Texture/Keyboard/Left.png";
	const string rightbuttonFilepath = "resource/Texture/Keyboard/Right.png";
	

	const int screensize_x = SCREEN_SIZE_X;
	const int screensize_y = SCREEN_SIZE_Y;

}

TitleUI::TitleUI() {

}
TitleUI::~TitleUI() {
}
void TitleUI::InsartPtrMaps(std::shared_ptr<GameEngine>& ge, const std::string& filepath,const std::string& item) {
	std::shared_ptr<UIDefault> t(new UIDefault());
	UIDATA titleui = {};
	t->Create(ge, titleui, filepath);
	_uimap.insert(std::make_pair(item, t));

}
void TitleUI::Init(std::shared_ptr<GameEngine>& ge) {
	_select_startbuttonF = true;//デフォルトはここで固定
	_select_endbuttonF = false;


	//ui:InitData
	InsartPtrMaps(ge, titlebackgroundmizutamafilepath, "背景水玉");
	InsartPtrMaps(ge, titlebackGroundBoardFilepath, "背景ボード");
	InsartPtrMaps(ge, titlerogoFilepath, "タイトルロゴ");
	InsartPtrMaps(ge, pleasepushFilepath, "スペースキーを押してください");


	//ui:InitParam
	auto ui = _uimap.at("背景水玉");
	UIDATA p = {};
	p.pos = { (float)screensize_x / 2,(float)screensize_y / 2,0 };
	p.scale = { 1,1,1 };
	ui->SetData(p);
	std::shared_ptr<UIDATA> d(new UIDATA());
	_ddata_mizutama = d;
	*_ddata_mizutama = p;

	auto board = _uimap.at("背景ボード");
	UIDATA bp = {};
	bp.pos = { (float)screensize_x / 2,(float)screensize_y / 2,0 };
	bp.scale = { 0.8,0.8,1 };
	board->SetData(bp);
	std::shared_ptr<UIDATA> b(new UIDATA());
	_ddata_board = b;
	*_ddata_board = bp;

	auto titlerogo = _uimap.at("タイトルロゴ");
	UIDATA tp = {};
	tp.pos = { 687,((float)screensize_y / 2),0 };
	tp.scale = { 1,1,1 };
	titlerogo->SetData(tp);
	std::shared_ptr<UIDATA> td(new UIDATA());
	_ddata_titlerogo = td;
	*_ddata_titlerogo = tp;


	auto pskey = _uimap.at("スペースキーを押してください");
	UIDATA psk = {};
	psk.pos = { 486,((float)screensize_y / 2),0 };
	psk.scale = { 0.4,0.09,1 };
	pskey->SetData(psk);
	std::shared_ptr<UIDATA> psd(new UIDATA());
	_ddata_pleasespacekey = psd;
	*_ddata_pleasespacekey = psk;

	//StartButton
	std::shared_ptr<Button> start(new Button());
	_startbutton = start;
	UIDATA sp = {};
	sp.pos = { 973,327,0 };
	sp.scale = { 0.1,0.2,1 };
	sp.color = { 1,1,1,1 };
	_startbutton->Create(ge,sp,0.2, startbuttonFilepath);
	std::shared_ptr<UIDATA> sd(new UIDATA());

	//EndButton
	std::shared_ptr<Button> end(new Button());
	_endbutton = end;
	UIDATA ep = {};
	ep.pos = { 973,527,0 };
	ep.scale = { 0.1,0.2,1 };
	ep.color = { 1,1,1,1 };
	_endbutton->Create(ge, ep, 0.2, endbuttonFilepath);
	std::shared_ptr<UIDATA> ed(new UIDATA());

	//KeyBoad
	InitButton(ge);
}
void TitleUI::InitButton(std::shared_ptr<GameEngine>& ge) {
	std::shared_ptr<Button> keyup(new Button());
	std::shared_ptr<Button> keydown(new Button());
	std::shared_ptr<Button> keyleft(new Button());
	std::shared_ptr<Button> keyright(new Button());
	_keybutton_up = keyup;
	_keybutton_down = keydown;
	_keybutton_left = keyleft;
	_keybutton_right = keyright;

	UIDATA up = {};
	up.pos = { 1103,327,0 };
	up.scale = { 0.05,0.1,1 };
	UIDATA down = {};
	down.pos = { 1103,527,0 };
	down.scale = { 0.05,0.1,1 };
	UIDATA left = {};
	UIDATA right = {};
	_keybutton_up->Create(ge, up,0, upbuttonFilepath);
	_keybutton_down->Create(ge, down,0, downbuttonFilepath);
	_keybutton_left->Create(ge, left,0, leftbuttonFilepath);
	_keybutton_right->Create(ge, right, 0, rightbuttonFilepath);

	_select_keybutton_upF = false;
	_select_keybutton_downF = false;
	_select_keybutton_startexitF = true;//start
}
void TitleUI::UpdateButton(std::shared_ptr<GameEngine>& ge, const std::string& cameraname) {
	auto data = _keybutton_down->GetData();
	auto data2 = _keybutton_up->GetData();

	//押下された場合色を変更します
	if (_select_keybutton_downF == true) {
		data.color = Vector4(1,1,1,0.5);
		_select_keybutton_startexitF = false;//end

	}
	else {
		data.color = Vector4(1, 1, 1, 1);
	}
	if (_select_keybutton_upF == true) {
		data2.color = Vector4(1, 1, 1, 0.5);
		_select_keybutton_startexitF = true;//start
	}
	else {
		data2.color = Vector4(1, 1, 1, 1);
	}

	_keybutton_down->SetData(data);
	_keybutton_up->SetData(data2);

	_keybutton_down->Draw(ge, cameraname);
	_keybutton_up->Draw(ge, cameraname);
}
void TitleUI::DrawTitleUI(std::shared_ptr<GameEngine>& ge,const std::string& cameraname) {
	//ui: Input
	CursorUpdate(ge);
	

	//ui: Draw
	auto spacekey = _uimap.at("スペースキーを押してください");
	spacekey->Draw(ge, cameraname);
	auto titlerogo = _uimap.at("タイトルロゴ");
	titlerogo->Draw(ge, cameraname);
	UpdateButton(ge, cameraname);
	_endbutton->DrawSelect(ge,cameraname, _select_endbuttonF);
	_startbutton->DrawSelect(ge, cameraname, _select_startbuttonF);
	auto board = _uimap.at("背景ボード");
	board->Draw(ge, cameraname);
	auto mizutama = _uimap.at("背景水玉");
	mizutama->Draw(ge, cameraname);


	
}
bool TitleUI::GetKeyButtonStartExit() {
	return _select_keybutton_startexitF;
}
#pragma region Cursor
void TitleUI::CursorInput(std::shared_ptr<GameEngine>& ge) {
	_select_keybutton_upF = false;
	_select_keybutton_downF = false;
	//SelectButton
	if (ge->CheckHitKey(DIK_UP)) {
		_select_startbuttonF = true;
		_select_endbuttonF = false;
		_select_keybutton_upF = true;
	}
	if (ge->CheckHitKey(DIK_DOWN)) {
		_select_startbuttonF = false;
		_select_endbuttonF = true;
		_select_keybutton_downF = true;
	}

}
void TitleUI::CursorUpdate(std::shared_ptr<GameEngine>& ge) {
	CursorInput(ge);


#ifdef _DEBUG
	auto mizutama = _uimap.at("背景水玉");
	ge->imguiAddMeshFloat(_ddata_mizutama->rotate, string("mizutamarotate"), string("m_rotation"), 10, -10);
	ge->imguiAddMeshVector3(_ddata_mizutama->rotateorigin,
		string("m_rotateorigin"),
		string("mo_x"),
		string("mo_y"),
		string("mo_z"),
		10, -10);
	ge->imguiAddMeshVector4(_ddata_mizutama->color,
		string("m_color"),
		string("mc_x"),
		string("mc_y"),
		string("mc_z"),
		string("mc_w"),
		1, 0);
	mizutama->SetData(*_ddata_mizutama);

	auto bored = _uimap.at("背景ボード");
	ge->imguiAddMeshFloat(
		_ddata_board->rotate,
		string("boared_rotate"),
		string("b_r_num"),
		10, -10);
	ge->imguiAddMeshVector3(_ddata_board->rotateorigin,
		string("board_rotateorigin"),
		string("bo_x"),
		string("bo_y"),
		string("bo_z"),
		10, -10);
	ge->imguiAddMeshVector4(_ddata_board->color,
		string("board_color"),
		string("bc_x"),
		string("bc_y"),
		string("bc_z"),
		string("bc_w"),
		1, 0);
	ge->imguiAddMeshVector3(_ddata_board->scale,
		string("board_scale"),
		string("bs_x"),
		string("bs_y"),
		string("bs_z"),
		1, 0);
	ge->imguiAddMeshFloat(_ddata_board->pos.x,
		string("board_pos_x"),
		string("bp_x"),
		screensize_x,-screensize_x);
	ge->imguiAddMeshFloat(_ddata_board->pos.y,
		string("board_pos_y"),
		string("bp_y"),
		screensize_y, -screensize_y);

	bored->SetData(*_ddata_board);

	auto titlerogo = _uimap.at("タイトルロゴ");
	ge->imguiAddMeshFloat(
		_ddata_titlerogo->rotate,
		string("trogo_rotate"),
		string("trogo_r_num"),
		10, -10);
	ge->imguiAddMeshVector3(
		_ddata_titlerogo->rotateorigin,
		string("trogo_rotateorigin"),
		string("tro_x"),
		string("tro_y"),
		string("tro_z"),
		10, -10);
	ge->imguiAddMeshVector4(
		_ddata_titlerogo->color,
		string("trogo_color"),
		string("trc_x"),
		string("trc_y"),
		string("trc_z"),
		string("trc_w"),
		1, 0);
	ge->imguiAddMeshVector3(
		_ddata_titlerogo->scale,
		string("trogo_scale"),
		string("trs_x"),
		string("trs_y"),
		string("trs_z"),
		1, 0);
	ge->imguiAddMeshFloat(
		_ddata_titlerogo->pos.x,
		string("trogo_pos_x"),
		string("trp_x"),
		screensize_x, -screensize_x);
	ge->imguiAddMeshFloat(
		_ddata_titlerogo->pos.y,
		string("trogo_pos_y"),
		string("trp_y"),
		screensize_y, -screensize_y);

	titlerogo->SetData(*_ddata_titlerogo);

	auto spasekey = _uimap.at("スペースキーを押してください");
	ge->imguiAddMeshFloat(
		_ddata_pleasespacekey->rotate,
		string("spk_rotate"),
		string("spk_r_num"),
		10, -10);
	ge->imguiAddMeshVector3(
		_ddata_pleasespacekey->rotateorigin,
		string("spk_rotateorigin"),
		string("spko_x"),
		string("spko_y"),
		string("spko_z"),
		10, -10);
	ge->imguiAddMeshVector4(
		_ddata_pleasespacekey->color,
		string("spk_color"),
		string("spkc_x"),
		string("spkc_y"),
		string("spkc_z"),
		string("spkc_w"),
		1, 0);
	ge->imguiAddMeshVector3(
		_ddata_pleasespacekey->scale,
		string("spk_scale"),
		string("spks_x"),
		string("spks_y"),
		string("spks_z"),
		1, 0);
	ge->imguiAddMeshFloat(
		_ddata_pleasespacekey->pos.x,
		string("spk_pos_x"),
		string("spkp_x"),
		screensize_x, -screensize_x);
	ge->imguiAddMeshFloat(
		_ddata_pleasespacekey->pos.y,
		string("spk_pos_y"),
		string("spkp_y"),
		screensize_y, -screensize_y);

	spasekey->SetData(*_ddata_pleasespacekey);

	

	
#endif

}
#pragma endregion