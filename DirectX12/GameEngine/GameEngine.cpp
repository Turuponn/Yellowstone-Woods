#include "GameEngine.h"
#include <d3d12.h>
#include "DirectXManagers/Fence/FenceManager.h"
#include "DirectXManagers/comand/ComandManager.h"
#include "DirectXManagers/Device/D3D12DeviceManager.h"
#include "DirectXManagers/DirectInput/DirectInputManager.h"
#include "DirectXManagers/Texture/TextureManager.h"
#include "DirectXManagers/Light/DirectionalLight/DirectionalLightManager.h"
#include "DirectXManagers/rootsignature/RootSignatureManager.h"
#include "DirectXManagers/DxGI\DxGIManager.h"
#include "DirectXManagers/swapchain/SwapChainManager.h"
#include "DirectXManagers/FBX/FBXManager.h"
#include "DirectXManagers/GbufferRendering/GbufferRenderManager.h"
#include "DirectXManagers/RenderTarget/RenderTargetManager.h"

#include "Graphics/Graphics.h"
#include "constance.h"
#include "WindowInit.h"
#include "Camera/Camera.h"
#include "DepthRender/DepthRenderManager.h"
#include <dxgidebug.h>//����Y�ꃌ�|�[�g�p
#include <wrl.h>//COM
#include <dxgi1_4.h>
#include <tchar.h>
#include "Library/DirectX12Create/Rand.h"
#include "CubeMap/CubeMapManager.h"
#include "FowardLayer/FowardLayerManager.h"
#include "WhiteTexture/WhiteTextureManager.h"
#include "DeferredShading/DeferredShading.h"
#include "PostProsess/PostProsessManager.h"
#include "GPGPUManager/GPGPUManager.h"
#include "UI/RECT/RECTUI.h"

//#debug
#include "imguiManager/ImguiManager.h"


using namespace Microsoft::WRL;
using namespace std;
using namespace DirectX;


void EnableDebugLayer()
{
	ID3D12Debug* debugController;
	HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
	if (SUCCEEDED(result))
		debugController->EnableDebugLayer();
	debugController->Release();

}

GameEngine::GameEngine() {
	
}
GameEngine::~GameEngine() {

}
void GameEngine::SetRootSignature() {
	_comand->GetGraphicsCommandList()->SetGraphicsRootSignature(_graphics->GetRootSignature()->GetRootSignature().Get());
}
void GameEngine::Initialize(WindowInit& windowinstance) {
	//�f�o�b�O���C���[�L��
#ifdef _DEBUG
	EnableDebugLayer();
#endif
	std::shared_ptr<D3D12DeviceManager> d(new D3D12DeviceManager());
	_device = d;
	std::shared_ptr<FenceManager> f(new FenceManager());
	_fencemanager = f;
	std::shared_ptr<ComandManager> c(new ComandManager());
	_comand = c;
	std::shared_ptr<Graphics> g(new Graphics());
	_graphics = g;
	std::shared_ptr<DxGIManager> dxgi(new DxGIManager());
	_dxgimanager = dxgi;
	std::shared_ptr<SwapChainManager> sc(new SwapChainManager());
	_sc = sc;
	std::shared_ptr<Rand> randpacage(new Rand());
	_randpacage = randpacage;
	std::shared_ptr<GbufferRenderManager> dr(new GbufferRenderManager());
	_drM = dr;
	std::shared_ptr<WhiteTextureManager> wTexM(new WhiteTextureManager());
	_whiteTexM = wTexM;
	std::shared_ptr<FowardLayerManager> f_layer(new FowardLayerManager());
	_f_ayer = f_layer;
	std::shared_ptr<DeferredShading> ds(new DeferredShading());
	_ds = ds;
	std::shared_ptr<PostProsessManager> pp(new PostProsessManager());
	_pp = pp;
	//dxgi
	_dxgimanager->CreateDxGiFactory();
	//input
	InputInit(windowinstance);
	//d3d12device
	_device->CreateD3DDevice(_dxgimanager);
	//comand1
	_comand->CreateComandQueue(_device);
	//swapchain
	_sc->Initialize(_device, _comand, dxgi, windowinstance.GetWindowHwnd());
	//comand2
	_comand->CreateComandAllocators(_device, _sc);
	//comand3
	_comand->CreateComandList(_device,_sc);
	//fence
	_fencemanager->Initialize(_device);
	//rtv
	_graphics->Initialize(_comand, _device, _dxgimanager, _sc);

	//
	//depth
	//DepthRenderInit();
	//imgui
	imgui(windowinstance);
	//layersystem
	_f_ayer->CreateLayer(_device, _graphics->GetRootSignature());
	//g-buffer
	_drM->CreateGbuffer(_device,_comand,_graphics->GetRootSignature());
	//whitetexture
	_whiteTexM->Initialize(_device, _comand);
	//pass
	_ds->Initialize(_device, _comand, _graphics->GetRootSignature());
	//pass
	_pp->Initialize(_device, _comand, _graphics->GetRootSignature());
	
	//���������[�N�̏ڍׂȌ^����\��������
	ID3D12DebugDevice* debugInterface;
	if (SUCCEEDED(_device->GetDevice()->QueryInterface(&debugInterface)))
	{
		debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
		debugInterface->Release();
	}
}
#pragma region DepthRender
void GameEngine::DepthRenderInit() {
	std::shared_ptr<DepthRenderManager> dmanager(new DepthRenderManager());
	_dmanager = dmanager;
	_dmanager->DepthRenderInit(_device);
}
void GameEngine::DepthRenderPre() {
	_dmanager->DepthRenderPre(_comand);
}
void GameEngine::DepthRenderPost() {
	_dmanager->DepthRenderPost(_comand,_fencemanager);
}
#pragma endregion
void GameEngine::Run() {
	_imgui->ResetimGuiCheck();
	SetRootSignature();
	InputRun();
}
#pragma region ���͌n
void GameEngine::InputRun() {
	_directinputmanager->InputUpdate();
}
void GameEngine::InputInit(WindowInit& windowinstance) {
	std::shared_ptr<DirectInputManager> input(new DirectInputManager());
	_directinputmanager = input;
	_directinputmanager->Initialize(windowinstance);


	//TODO:�@Xinput
	//std::shared_ptr<XInput> xinput(new XInput());
	//_xinput = xinput;
	//_xinput->Init();
}
const int GameEngine::CheckHitKey(const int keycode) {
	return _directinputmanager->CheckHitKey(keycode);
}
#pragma endregion
void GameEngine::ScreenFilip() {
	_graphics->PostRTV(_comand,_sc);		
	_graphics->ScreenFlip(_comand, _fencemanager, _sc);

	//SwapChainBuffer UI Test
	//_graphics->D2DFlip(_comand, _fencemanager, _sc);
}
#pragma region 
const int GameEngine::LoadImagehandle(const std::string& filepath) {
	std::shared_ptr<TextureManager> tex(new TextureManager());
	int imagehandle = _randpacage->Rand_mt();
	tex->WICLoadTexture(_device,_comand, filepath);
	_imagedatas.insert(std::make_pair(imagehandle, tex));
	return imagehandle;
}
const int GameEngine::LoadBumpImagehandle(const std::string& filepath) {
	std::shared_ptr<TextureManager> tex(new TextureManager());
	int imagehandle = _randpacage->Rand_mt();
	tex->WICLoadTexture(_device, _comand, filepath);
	_imagedatas.insert(std::make_pair(imagehandle, tex));
	return imagehandle;
}
void GameEngine::DrawImage(const int handle) {
	auto img = _imagedatas.at(handle);
	if (img != nullptr) {
		img->DrawImage(_comand,1, TEX_TEXTURE);
	}
}
#pragma endregion
#pragma region Light
const int GameEngine::DirectionalLightInit() {
	std::shared_ptr<DirectionalLightManager> dirlight(new DirectionalLightManager());
	int handle = _randpacage->Rand_mt();
	dirlight->DirectionalLightCreate(_device, _graphics->GetRootSignature());
	_dirlights.insert(std::make_pair(handle, dirlight));
	return handle;
}
void GameEngine::DirectionallightUpdate(const int handle) {
	auto dirlight = _dirlights.at(handle);
	if (dirlight != nullptr) {
		dirlight->Update(_comand);
	}
}
void GameEngine::DirectionallightPos(const int handle,const Vector3& lightdir) {
	auto dirlight = _dirlights.at(handle);
	if (dirlight != nullptr) {
		dirlight->SetLightPos(lightdir);
	}	
}
void GameEngine::DirectionallightIntensity(const int handle,const float lightintensity) {
	auto dirlight = _dirlights.at(handle);
	if (dirlight != nullptr) {
		dirlight->SetLightIntensity(lightintensity);
	}
}
#pragma endregion
#pragma region Camera
void GameEngine::CreateCamera(const std::string& cameraname) {
	std::shared_ptr<Camera> cam(new Camera());
	cam->CreateCamera(_device);
	_cameras.insert(std::make_pair(cameraname, cam));
}
void GameEngine::CreateCameraHandle(const std::string& cameraname) {
	if (_cameras.size() > 0) {//���ɃJ���������݂���ꍇ
		auto cam = _cameras.at(cameraname);
		if (cam != nullptr) {
			//�������Ȃ�
		}
		else {//�w�薼�����݂��Ȃ��ꍇ�V�K�쐬
			CreateCamera(cameraname);
		}
	}
	else {//�Ȃ��ꍇ�V�K�쐬
		CreateCamera(cameraname);
	}
	
}
void GameEngine::UpdateCamera(const std::string& cameraname) {
	//SetRootSignature();
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		cam->Update(_comand);
	}
}
void GameEngine::SetCameraRotate(const std::string& cameraname,const Vector3& newpoint, const Vector3& newcamerarotate,const float camerarenge) {
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		cam->CameraRotate(newpoint.x, newpoint.y, newpoint.z, newcamerarotate.x, newcamerarotate.y, newcamerarotate.z, camerarenge);
	}	
}
void GameEngine::SetCameraPosition(const std::string& cameraname,const Vector3& pos) {
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		cam->SetCameraPostion(pos.x, pos.y, pos.z);
	}
}
Vector3 GameEngine::GetCameraPosition(const std::string& cameraname) {
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		return cam->GetCameraPosition();
	}
	return Vector3(0,0,0);
}
Vector3 GameEngine::GetCameraLookAt(const std::string& cameraname) {
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		return cam->GetCameraLookAt();
	}
	return Vector3(0, 0, 0);
}
DirectX::XMMATRIX GameEngine::GetCameraViewMat(const std::string& cameraname) {
	XMMATRIX mat = XMMatrixIdentity();
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		mat = cam->GetCameraView();
		return mat;
	}
	return mat;
}
#pragma endregion
#pragma region FBX
void GameEngine::CreateFBXModel(const std::string& modelname, const std::string& fbxfilepath, bool animationF) {
	std::shared_ptr<FBXManager> fbx(new FBXManager());
	fbx->LoadModelDR(FBX_DRAW(_device, _comand, _graphics->GetRootSignature()), _fencemanager, fbxfilepath, animationF);
	_fbxs.insert(std::make_pair(modelname, fbx));
}
void GameEngine::LoadFBXModelDR(const std::string& modelname,const std::string& filepath, bool animationF) {
	if (_fbxs.size() > 0) {//���ɑ��݂���ꍇ
		decltype(_fbxs)::iterator it = _fbxs.find(modelname);
		if (it != _fbxs.end()) { // ��������
			//��������
		}
		else {//������Ȃ��̂Œǉ�����
			CreateFBXModel(modelname, filepath, animationF);
		}
	}
	else {//�Ȃ��ꍇ�V�K�쐬
		CreateFBXModel(modelname, filepath, animationF);
	}
	
	
}
void GameEngine::DrawFBXModelDR(const std::string& modelname) {
	SetRootSignature();
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) { 
		auto fbx = _fbxs.at(modelname);
		_drM->SetDrawPipeline(_comand);
		fbx->DrawModelDR(FBX_DRAW(_device, _comand, _graphics->GetRootSignature()), TEX_DR, _whiteTexM, true);
	}
}
void GameEngine::FBXAnimationPlay(const std::string& modelname,const std::string& animname,const int animframe) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) { 
		auto fbx = _fbxs.at(modelname);
		fbx->AnimationPlay(animname, animframe);
	}
}
void GameEngine::FBXAnimationEND(const std::string& modelname) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) { 
		auto fbx = _fbxs.at(modelname);
		fbx->AnimationEND();
	}
}

void GameEngine::SetFBXRotateQuaternion(const std::string& modelname, const Vector3& axis, float angle) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetRotateQuaternion(axis, angle);
	}
}
void GameEngine::SetFBXPostionQuaternion(const std::string& modelname, const Vector3& pos) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetPostionQuaternion(pos);
	}
}
void GameEngine::SetFBXScaleQuaternion(const std::string& modelname, const Vector3& scale) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetScaleQuaternion(scale);
	}
}
void GameEngine::SetFBXRotateQuaternion_mul(const std::string& modelname, const Vector3& newaxis, float newangle) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetRotateQuaternion_mul(newaxis, newangle);
	}
}
DirectX::XMVECTOR GameEngine::GetFBXRotateQuaternion(const std::string& modelname) {
	XMVECTOR v = { 0,0,0 };
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		return fbx->GetRotateQuaternion();
	}
	return v;
}
void GameEngine::SetFBXRotateQuaternion_Slerp(const std::string& modelname,const DirectX::XMVECTOR& oldvec,const DirectX::XMVECTOR& newvec, float t) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetRotateQuaternion_Slerp(oldvec, newvec, t);
	}
}
DirectX::XMVECTOR GameEngine::CreateFBXRotateQuaternion(const std::string& modelname,const Vector3& axis, float angle) {
	DirectX::XMVECTOR p = {0,0,0};
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		return fbx->CreateRotateQuaternion(axis, angle);
	}
	return p;
}
void GameEngine::SetFBXRotateQuaternion_Euler(const std::string& modelname, const Vector3& newrotate) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetRotateQuaternion_Euler(newrotate);
	}
}
void GameEngine::SetFBXRotateQuaternionOrigin(const std::string& modelname, const Vector3& neworigin) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetRotateQuaternionOrigin(neworigin);
	}
}
void GameEngine::SetFBXRotateQuaternion_Matrix(const std::string& modelname, DirectX::XMMATRIX& newmat) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		fbx->SetRotateQuaternion_Matrix(newmat);
	}
}
int GameEngine::GetAnimFrameEndPos(const std::string& modelname, const std::string& animname) {
	decltype(_fbxs)::iterator it = _fbxs.find(modelname);
	if (it != _fbxs.end()) {
		auto fbx = _fbxs.at(modelname);
		return fbx->GetAnimFrameEndPos(animname);
	}
	return 0;
}
#pragma endregion
#pragma region CubeMap
void GameEngine::CreateCubeMap(const std::string& cubemapname, const std::string& texfilepath, const std::string& fbxfilepath) {
	std::shared_ptr<CubeMapManager> cbmap(new CubeMapManager());
	cbmap->LoadCubeMap(_device, _comand, texfilepath);
	cbmap->CreateFBXMesh(_device, _comand, _graphics->GetRootSignature(), _fencemanager, fbxfilepath);
	_cubemap.insert(std::make_pair(cubemapname, cbmap));
}
void GameEngine::LoadCubeMap(const std::string& cubemapname,const std::string& texfilepath,const std::string& fbxfilepath) {
	
	if (_cubemap.size() > 0) {
		auto cubemap = _cubemap.at(cubemapname);
		if (cubemap != nullptr) {
		//�������Ȃ�
		}
		else {
			CreateCubeMap(cubemapname, texfilepath, fbxfilepath);
		}
	}
	else {
		CreateCubeMap(cubemapname, texfilepath, fbxfilepath);
	}


}
void GameEngine::PreCubeMap(const std::string& cubemapname) {
	SetRootSignature();
	auto cubemap = _cubemap.at(cubemapname);
	if (cubemap != nullptr) {
		_drM->SetCMapPipeline(_comand);
		cubemap->PreUpdate(_device, _comand, _graphics->GetRootSignature(),_fencemanager,_graphics->GetDepth(),_whiteTexM);
	}
}
void GameEngine::SetCubeMapScaleQuaternion(const std::string& cubemapname,const Vector3& newscale) {
	auto cubemap = _cubemap.at(cubemapname);
	if (cubemap != nullptr) {
		cubemap->SetScaleQuaternion(newscale);
	}
}
void GameEngine::SetCubeMapPostionQuaternion(const std::string& cubemapname, const Vector3& newpos) {
	auto cubemap = _cubemap.at(cubemapname);
	if (cubemap != nullptr) {
		cubemap->SetPostionQuaternion(newpos);
	}
}
void GameEngine::SetCubeMapRotateQuaternion(const std::string& cubemapname, const Vector3& newaxis,float angle) {
	auto cubemap = _cubemap.at(cubemapname);
	if (cubemap != nullptr) {
		cubemap->SetRotateQuaternion(newaxis,angle);
	}
}
#pragma endregion
#pragma region imgui
void GameEngine::imgui(WindowInit& windowinfo) {
	std::shared_ptr<ImguiManager> imgui(new ImguiManager());
	_imgui = imgui;
	if (_imgui->Initialize(_device,_graphics, windowinfo.GetWindowHwnd()) != true) { throw(1); }
}
void GameEngine::Drawimgui() {
	_imgui->DrawimGui(_comand);
}
void GameEngine::imguiAddItemLightIntensity(float& lightintensity) {
	_imgui->AdditemLightIntensity(lightintensity);
}
void GameEngine::imguiAddItemDirLightPos(Vector3& d_pos) {
	_imgui->AdditemDirLightPos(d_pos);
}
void GameEngine::imguiCubeMapScale(Vector3& d_cubemap) {
	_imgui->CubeMapMeshScale(d_cubemap);
}
void GameEngine::imguiAddMeshScale(Vector3* newscale, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z,float maxsize) {
	_imgui->ShowAddMeshScale(newscale,text, label_x,label_y, label_z, maxsize);
}
void GameEngine::imguiAddMeshVector4(Vector4& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, std::string& label_w, float maxsize, float minsize) {
	_imgui->ShowAddMeshVector4(newparam, text, label_x, label_y, label_z, label_w, maxsize, minsize);
}
void GameEngine::imguiAddMeshVector3(Vector3& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize,float minsize) {
	_imgui->ShowAddMeshVector3(newparam, text, label_x, label_y, label_z, maxsize, minsize);
}
void GameEngine::imguiAddMeshFloat(float& newparam, std::string& text, std::string& label, float maxsize, float minsize) {
	_imgui->ShowAddMeshFloat(newparam, text, label,maxsize, minsize);
}
void GameEngine::imguiAddMeshInt(int& newparam, std::string& text, std::string& label, int maxsize, int minsize) {
	_imgui->ShowAddMeshInt(newparam, text, label, maxsize, minsize);
}
void GameEngine::imguiPre() {
	_imgui->PreGui(_comand);
}
void GameEngine::imguiPost() {
	_imgui->PostGui(_comand);
}
#pragma endregion
#pragma region DR
void GameEngine::DR_Pre() {
	_drM->PreRender(_device,_comand,_graphics,_sc);
}
void GameEngine::DR_Post() {
	_drM->PostRender(_comand, _fencemanager);
}
#pragma endregion
void GameEngine::DrawScreen(const std::string& cameraname) {
	SetRootSignature();
	_graphics->RTVSwapChainUpdate(_device, _comand, _sc);
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		_f_ayer->Draw(_device, _comand, cam,_fencemanager);
	}
	else {
		//Not Display
		throw(1);
	}
	
}
#pragma region DS
void GameEngine::PreDeferredShadingRender(const std::string& cameraname) {
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		_ds->PreRender(_device, _comand, _graphics,_sc,cam,_fencemanager);
	}
	else {
		//Not Display
		throw(1);
	}
	
}
void GameEngine::PostDeferredShadingRender() {
	_ds->PostRender(_comand, _fencemanager);
}
#pragma endregion
#pragma region PP
void GameEngine::PrePostProsessRender(const std::string& cameraname) {
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		_pp->PreRender(_device, _comand, _graphics,_sc, cam, _fencemanager);
	}
	else {
		//Not Display
		throw(1);
	}

}
void GameEngine::PostPostProsessRender() {
	_pp->PostRender(_comand, _fencemanager);
}
#pragma endregion
float GameEngine::GetRandMt() {
	return _randpacage->Rand_mt();
}
const float GameEngine::GetRandFloatRengeMt(const float min, const float max) {
	return _randpacage->Rand_mt_float(min,max);
}
const int GameEngine::GetRandIntRengeMt(const int min, const int max) {
	return _randpacage->Rand_mt_int(min, max);
}
#pragma region UI
const int GameEngine::CreateRECTUIHandle(const std::string& texfilepath) {
	std::shared_ptr<RECTUI> ui(new RECTUI());
	ui->CreateUIRect(_device,_comand,_graphics->GetRootSignature(), texfilepath);
	int handle = GetRandMt();
	_uis.insert(std::make_pair(handle, ui));
	return handle;
}

void GameEngine::DrawRECTUI(const int uihandle, const std::string& cameraname) {
	auto cam = _cameras.at(cameraname);
	if (cam != nullptr) {
		auto ui = _uis.at(uihandle);
		if (ui != nullptr) {
			ui->DrawRect(_comand, cam,_whiteTexM);
		}
		else {
			//Not ui
			throw(1);
		}
	}
	else {
		//Not Display
		throw(1);
	}
}
void GameEngine::SetPosUI(const int uihandle, const Vector3& newpos) {
	auto ui = _uis.at(uihandle);
	if (ui != nullptr) {
		ui->SetPos(newpos);
	}
}
void GameEngine::SetScaleUI(const int uihandle, const Vector3& newscale) {
	auto ui = _uis.at(uihandle);
	if (ui != nullptr) {
		ui->SetScale(newscale);
	}
}
void GameEngine::SetRotateOriginUI(const int uihandle, const Vector3& newrotateorigin) {
	auto ui = _uis.at(uihandle);
	if (ui != nullptr) {
		ui->SetRotateOrigin(newrotateorigin);
	}
}
void GameEngine::SetColorUI(const int uihandle, const Vector4& newcolor) {
	auto ui = _uis.at(uihandle);
	if (ui != nullptr) {
		ui->SetColor(newcolor);
	}
}
void GameEngine::SetRotateUI(const int uihandle, const float newrotate) {
	auto ui = _uis.at(uihandle);
	if (ui != nullptr) {
		ui->SetRotate(newrotate);
	}
}


#pragma endregion
