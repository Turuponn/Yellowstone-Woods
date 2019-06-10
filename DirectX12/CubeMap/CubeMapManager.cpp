#include "CubeMapManager.h"
#include <d3d12.h>
#include "constance.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include <DirectXTex\DirectXTex.h>
#include <DDSTextureLoader\DDSTextureLoader12.h>
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\FBX\FBXManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\Shada\Vertex\VertexShadaManager.h"
#include "DirectXManagers\Shada\Pixcel\PixcelShadaManager.h"
#include "DirectXManagers\constance\ConstantManager.h"
#include "d3dx12.h"
#include "WhiteTexture\WhiteTextureManager.h"


using namespace std;


namespace {

	wchar_t* vsShadaFilepathCubemap = _T("resource/ShadaFile/CubeMap/vs/CubeMapVertexShader.hlsl");
	char* vsShadaFuncnameCubemap = "CubeMapVS";
	wchar_t* psShadaFilepathCubemap = _T("resource/ShadaFile/CubeMap/ps/CubeMapPixelShader.hlsl");
	char* psShadaFuncnameCubemap = "CubeMapPS";

}


CubeMapManager::CubeMapManager() {

}
CubeMapManager::~CubeMapManager() {

}
void CubeMapManager::LoadCubeMap(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand,std::shared_ptr<FenceManager>& fence,std::shared_ptr<RootSignatureManager>& rootsignature,const std::string& texfilepath) {
		std::shared_ptr<TextureManager> tex(new TextureManager());
		tex->LoadDDSTexture(device,comand,fence, texfilepath);
		_texM = tex;
	

}
void CubeMapManager::CreateFBXMesh(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature, std::shared_ptr<FenceManager>& fence,const std::string& fbxfilepath) {
	std::shared_ptr<FBXManager> fbx(new FBXManager());
	fbx->LoadModelDR(FBX_DRAW(device, comand, rootsignature),fence, fbxfilepath,false);
	_fbx = fbx;
}

void CubeMapManager::PreUpdate(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature,std::shared_ptr<FenceManager>& fence, std::shared_ptr<DepthManager>& depth,std::shared_ptr<WhiteTextureManager>& whitetex) {
	//’Êí‚ÌSkyBox
	_texM->DrawImage(comand, 1,TEX_CUBEMAP);
	_fbx->DrawModelDR(FBX_DRAW(device, comand, rootsignature), TEX_CUBEMAP, whitetex,false);


	
}
void CubeMapManager::SetScaleQuaternion(const Vector3& scale) {
	_fbx->SetScaleQuaternion(scale);
}
void CubeMapManager::SetPostionQuaternion(const Vector3& pos) {
	_fbx->SetPostionQuaternion(pos);
}
void CubeMapManager::SetRotateQuaternion(const Vector3& axis,float angle) {
	_fbx->SetRotateQuaternion(axis,angle);
}
void CubeMapManager::SetRotateQuaternion_mul(const Vector3& newaxis, float angle) {
	_fbx->SetRotateQuaternion_mul(newaxis,angle);
}