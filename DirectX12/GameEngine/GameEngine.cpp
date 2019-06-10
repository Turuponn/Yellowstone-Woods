#include "GameEngine.h"
#include <d3d12.h>
#include "Graphics\Graphics.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "constance.h"
#include "WindowInit.h"
#include "DirectXManagers\DirectInput\DirectInputManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\Light\DirectionalLight\DirectionalLightManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\DxGI\DxGIManager.h"
#include "Camera\Camera.h"
#include "DirectXManagers\FBX\FBXManager.h"
#include "DepthRender\DepthRenderManager.h"
#include <dxgidebug.h>//解放忘れレポート用
#include <wrl.h>//COM
#include <dxgi1_4.h>
#include <tchar.h>
#include "Library\DirectX12Create\Rand.h"
#include "CubeMap\CubeMapManager.h"
#include "FowardLayer/FowardLayerManager.h"
#include "DirectXManagers\GbufferRendering\GbufferRenderManager.h"
#include "WhiteTexture\WhiteTextureManager.h"
#include "DeferredShading/DeferredShading.h"
#include "PostProsess/PostProsessManager.h"
#include "GPGPUManager\GPGPUManager.h"
//#debug
#include "imguiManager\ImguiManager.h"



#include "DirectXManagers/RenderTarget/RenderTargetManager.h"


using namespace Microsoft::WRL;
using namespace std;
using namespace DirectX;


GameEngine::GameEngine() {
	
}
GameEngine::~GameEngine() {

	
}
void GameEngine::SetRootSignature() {
	_comand->GetGraphicsCommandList()->SetGraphicsRootSignature(_graphics->GetRootSignature()->GetRootSignature());
}
void EnableDebugLayer()
{
	ComPtr<ID3D12Debug> debugController;
	HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
	if (SUCCEEDED(result))
		debugController->EnableDebugLayer();
}
void GameEngine::Initialize(WindowInit& windowinstance) {
	//デバッグレイヤー有効
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

	_dxgimanager->CreateDxGiFactory();
	InputInit(windowinstance);
	_device->CreateD3DDevice(_dxgimanager);
	_comand->Initialize(_device);
	_fencemanager->Initialize(_device);
	_graphics->Initialize(_comand, _device, _dxgimanager, windowinstance.GetWindowHwnd());
	DepthRenderInit();
	imgui(windowinstance);
	_f_ayer->CreateLayer(_device, _graphics->GetRootSignature());
	_drM->CreateGbuffer(_device,_comand,_graphics->GetRootSignature());
	_whiteTexM->Initialize(_device, _comand);
	_ds->Initialize(_device, _comand, _graphics->GetRootSignature());
	_pp->Initialize(_device, _comand, _graphics->GetRootSignature());



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
void GameEngine::Render() {
	_graphics->Updata(_comand);
}
#pragma region 入力系
void GameEngine::InputRun() {
	_directinputmanager->InputUpdate();
}
void GameEngine::InputInit(WindowInit& windowinstance) {
	std::shared_ptr<DirectInputManager> input(new DirectInputManager());
	_directinputmanager = input;
	_directinputmanager->Initialize(windowinstance);
}
const int GameEngine::CheckHitKey(const int keycode) {
	return _directinputmanager->CheckHitKey(keycode);
}
#pragma endregion
void GameEngine::ScreenFilip() {
	_graphics->GetRTV()->PostRTV(_comand);
	_graphics->ScreenFlip(_comand,_fencemanager);
}
#pragma region 
const int GameEngine::LoadImagehandle(const std::string& filepath) {
	std::shared_ptr<TextureManager> tex(new TextureManager());
	int imagehandle = _randpacage->Rand_mt();
	tex->WICLoadTexture(_device,_comand, _fencemanager, filepath);
	_imagedatas.insert(std::make_pair(imagehandle, tex));
	return imagehandle;
}
const int GameEngine::LoadBumpImagehandle(const std::string& filepath) {
	std::shared_ptr<TextureManager> tex(new TextureManager());
	int imagehandle = _randpacage->Rand_mt();
	tex->WICLoadTexture(_device, _comand, _fencemanager, filepath);
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
const int GameEngine::CreateCameraHandle() {
	std::shared_ptr<Camera> cam(new Camera());
	cam->CreateCamera(_device);
	int handle = _randpacage->Rand_mt();
	_cameras.insert(std::make_pair(handle, cam));
	return handle;
}
void GameEngine::UpdateCamera(const int handle) {
	SetRootSignature();
	auto cam = _cameras.at(handle);
	if (cam != nullptr) {
		cam->Update(_comand);
	}
}
void GameEngine::SetCameraRotate(const int camerahandle, float x, float y, float z, float camx, float camy, float camz,float camerarenge) {
	auto cam = _cameras.at(camerahandle);
	if (cam != nullptr) {
		cam->CameraRotate(x, y, z,camx,camy,camz, camerarenge);
	}	
}
void GameEngine::SetCameraPosition(const int camerahandl,float x, float y, float z) {
	auto cam = _cameras.at(camerahandl);
	if (cam != nullptr) {
		cam->SetCameraPostion(x,y,z);
	}
}
Vector3 GameEngine::GetCameraPosition(const int camerahandl) {
	auto cam = _cameras.at(camerahandl);
	if (cam != nullptr) {
		return cam->GetCameraPosition();
	}
	return Vector3(0,0,0);
}
Vector3 GameEngine::GetCameraLookAt(const int camerahandl) {
	auto cam = _cameras.at(camerahandl);
	if (cam != nullptr) {
		return cam->GetCameraLookAt();
	}
	return Vector3(0, 0, 0);
}
DirectX::XMMATRIX GameEngine::GetCameraViewMat(const int handle) {
	XMMATRIX mat = XMMatrixIdentity();
	auto cam = _cameras.at(handle);
	if (cam != nullptr) {
		mat = cam->GetCameraView();
		return mat;
	}
	return mat;
}
#pragma endregion
#pragma region FBX
const int GameEngine::LoadFBXModelDR(const std::string& filepath, bool animationF) {
	std::shared_ptr<FBXManager> fbx(new FBXManager());
	fbx->LoadModelDR(FBX_DRAW(_device, _comand, _graphics->GetRootSignature()), _fencemanager, filepath, animationF);
	int handle = _randpacage->Rand_mt();
	_fbxs.insert(std::make_pair(handle, fbx));
	return handle;
}
void GameEngine::DrawFBXModelDR(const int handle) {
	SetRootSignature();
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		_drM->SetDrawPipeline(_comand);
		fbx->DrawModelDR(FBX_DRAW(_device, _comand, _graphics->GetRootSignature()), TEX_DR, _whiteTexM, true);
	}
}
void GameEngine::FBXAnimationPlay(const int handle,const std::string& animname,const int animframe) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->AnimationPlay(animname, animframe);
	}
}
void GameEngine::FBXAnimationEND(const int handle) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->AnimationEND();
	}
}

void GameEngine::SetFBXRotateQuaternion(const int handle, const Vector3& axis, float angle) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetRotateQuaternion(axis,angle);
	}
}
void GameEngine::SetFBXPostionQuaternion(const int handle, const Vector3& pos) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetPostionQuaternion(pos);
	}
}
void GameEngine::SetFBXScaleQuaternion(const int handle, const Vector3& scale) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetScaleQuaternion(scale);
	}
}
void GameEngine::SetFBXRotateQuaternion_mul(const int handle, const Vector3& newaxis, float newangle) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetRotateQuaternion_mul(newaxis,newangle);
	}
}
DirectX::XMVECTOR GameEngine::GetFBXRotateQuaternion(const int handle) {
	auto fbx = _fbxs.at(handle);
	XMVECTOR v = { 0,0,0 };
	if (fbx != nullptr) {
		return fbx->GetRotateQuaternion();
	}
	return v;
}
void GameEngine::SetFBXRotateQuaternion_Slerp(const int handle,const DirectX::XMVECTOR& oldvec,const DirectX::XMVECTOR& newvec, float t) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetRotateQuaternion_Slerp(oldvec,newvec,t);
	}
}
DirectX::XMVECTOR GameEngine::CreateFBXRotateQuaternion(const int handle,const Vector3& axis, float angle) {
	DirectX::XMVECTOR p = {0,0,0};
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		return fbx->CreateRotateQuaternion(axis, angle);
	}
	return p;
}
void GameEngine::SetFBXRotateQuaternion_Euler(const int handle, const Vector3& newrotate) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetRotateQuaternion_Euler(newrotate);
	}
}
void GameEngine::SetFBXRotateQuaternionOrigin(const int handle, const Vector3& neworigin) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetRotateQuaternionOrigin(neworigin);
	}
}
void GameEngine::SetFBXRotateQuaternion_Matrix(const int handle, DirectX::XMMATRIX& newmat) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		fbx->SetRotateQuaternion_Matrix(newmat);
	}
}
int GameEngine::GetAnimFrameEndPos(const int handle, const std::string& animname) {
	auto fbx = _fbxs.at(handle);
	if (fbx != nullptr) {
		return fbx->GetAnimFrameEndPos(animname);
	}
	return 0;
}
#pragma endregion
#pragma region CubeMap
const int GameEngine::LoadCubeMap(const std::string& texfilepath,const std::string& fbxfilepath) {
	std::shared_ptr<CubeMapManager> cbmap(new CubeMapManager());
	cbmap->LoadCubeMap(_device, _comand, _fencemanager, _graphics->GetRootSignature(), texfilepath);
	cbmap->CreateFBXMesh(_device,_comand,_graphics->GetRootSignature(),_fencemanager, fbxfilepath);
	int handle = _randpacage->Rand_mt();
	_cubemap.insert(std::make_pair(handle, cbmap));
	return handle;
}
void GameEngine::PreCubeMap(const int handle) {
	SetRootSignature();
	auto cubemap = _cubemap.at(handle);
	if (cubemap != nullptr) {
		_drM->SetCMapPipeline(_comand);
		cubemap->PreUpdate(_device, _comand, _graphics->GetRootSignature(),_fencemanager,_graphics->GetDepth(),_whiteTexM);
	}
}
void GameEngine::SetCubeMapScaleQuaternion(const int handle,const Vector3& newscale) {
	auto cubemap = _cubemap.at(handle);
	if (cubemap != nullptr) {
		cubemap->SetScaleQuaternion(newscale);
	}
}
void GameEngine::SetCubeMapPostionQuaternion(const int handle, const Vector3& newpos) {
	auto cubemap = _cubemap.at(handle);
	if (cubemap != nullptr) {
		cubemap->SetPostionQuaternion(newpos);
	}
}
void GameEngine::SetCubeMapRotateQuaternion(const int handle, const Vector3& newaxis,float angle) {
	auto cubemap = _cubemap.at(handle);
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
void GameEngine::imguiAddMeshVector(Vector3& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize,float minsize) {
	_imgui->ShowAddMeshVector(newparam, text, label_x, label_y, label_z, maxsize, minsize);
}
void GameEngine::imguiAddMeshFloat(float& newparam, std::string& text, std::string& label, float maxsize, float minsize) {
	_imgui->ShowAddMeshFloat(newparam, text, label,maxsize, minsize);
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
	_drM->PreRender(_device,_comand,_graphics->GetRTV(),_graphics->GetDepth());
}
void GameEngine::DR_Post() {
	_drM->PostRender(_comand, _fencemanager);
}
#pragma endregion
void GameEngine::DrawScreen(const int attachcamerahandle) {
	SetRootSignature();
	auto cam = _cameras.at(attachcamerahandle);
	if (cam != nullptr) {
		_f_ayer->Draw(_device, _comand, cam,_fencemanager);
	}
	else {
		//Not Display
		throw(1);
	}
	
}
#pragma region DS
void GameEngine::PreDeferredShadingRender(const int attachcamerahandle) {
	auto cam = _cameras.at(attachcamerahandle);
	if (cam != nullptr) {
		_ds->PreRender(_device, _comand, _graphics->GetRTV(), _graphics->GetDepth(),cam,_fencemanager);
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
void GameEngine::PrePostProsessRender(const int attachcamerahandle) {
	auto cam = _cameras.at(attachcamerahandle);
	if (cam != nullptr) {
		_pp->PreRender(_device, _comand, _graphics->GetRTV(), _graphics->GetDepth(), cam, _fencemanager);
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