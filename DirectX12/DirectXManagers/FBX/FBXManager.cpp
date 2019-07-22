#include "FBXManager.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Shada\Vertex\VertexShadaManager.h"
#include "DirectXManagers\Shada\Pixcel\PixcelShadaManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\vertex\VertexBufferManager.h"
#include "DirectXManagers\index\IndexBufferManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\constance\ConstantManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "constance.h"
#include <DirectXMath.h>


#include "DirectXManagers\GbufferRendering\GbufferRenderManager.h"
#include "DirectXManagers\RenderTarget\RenderTargetManager.h"
#include "DirectXManagers\DepthStencil\Depth\DepthManager.h"
#include "WhiteTexture\WhiteTextureManager.h"


#include <tchar.h>



using namespace DirectX;









FBXManager::FBXManager() {
		
	XMFLOAT3 t = { 0,0,0 };
	_origin = XMLoadFloat3(&t);
	_animinfo.animationF = false;
	_animinfo.animationFrame = 0;
	_animinfo.animname = "";
	_cbuffAddress = nullptr;
	_cbuffAddressSkinning = nullptr;
}
FBXManager::~FBXManager() {

}


void FBXManager::LoadModelDR(FBX_DRAW& fbxdraw, std::shared_ptr<FenceManager>& fence, const std::string& filepath, bool animationF) {
	FBXLoader::Load(filepath, fbxdraw.device, fbxdraw.comand, fence, fbxdraw.rootsignature, animationF);
	_animinfo.animationF = animationF;//事前にアニメーション情報があるかどうかを判別します
	CbuffCreate(fbxdraw.device);
}
void FBXManager::DrawModelDR(FBX_DRAW& fbxdraw, TEXTURE_REGISTER texture_register, std::shared_ptr<WhiteTextureManager>& whitetexM,bool texF) {
	DeferredRender(fbxdraw, texture_register, whitetexM,texF);
}
void FBXManager::DeferredRender(FBX_DRAW& fbxdraw, TEXTURE_REGISTER texture_register,std::shared_ptr<WhiteTextureManager>& whitetexM, bool texF) {
	//Animationさせます
	auto cbffmat_bone = _cbuffAddressSkinning;
	if (_animinfo.animationF) {
		FBXLoader::Animation(_animinfo.animname,_animinfo.animationFrame);
		for (int i = 0; i < FBXLoader::GetPaletteBone().size(); i++) {
			cbffmat_bone->jointMatrix[i] = FBXLoader::GetPaletteBone()[i].bindPose;//合成行列を計算するためのjointmatrixを定数経由でシェーダへ送ります
		}
	}
	else {
		for (int i = 0; i < FBXLoader::GetPaletteBone().size(); i++) {//初期メッシュポーズにします。
			cbffmat_bone->jointMatrix[i] = DirectX::XMMatrixIdentity();
		}
		
	}
	cbffmat_bone = (JOINTBONE*)(((char*)cbffmat_bone) + ((sizeof(JOINTBONE) + 0xff) & ~0xff));
	auto handle_cbuff_bone = _cbbone->GetDescHeap()->GetGPUDescriptorHandleForHeapStart();
	auto heap = _cbbone->GetDescHeap();
	fbxdraw.comand->GetGraphicsCommandList()->SetDescriptorHeaps(1, &heap);
	fbxdraw.comand->GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(ROOT_PARAM_CONSTANT_TESTBONE, handle_cbuff_bone);


	//モデルを描画します
	auto cbffmat = _cbuffAddress;
	auto handle_cbuff = _cb->GetDescHeap()->GetGPUDescriptorHandleForHeapStart();
		unsigned int indexcount = 0;
		fbxdraw.comand->GetGraphicsCommandList()->IASetVertexBuffers(0, 1, FBXLoader::GetVertexResoce()[0].vertexmanager->GetVertexBufferView());
		//マテリアルループ
		for (int materialidx = 0; materialidx < FBXLoader::GetMaterialTable()[0].size(); materialidx++)
		{
			*_cbuffAddress = *cbffmat;
			fbxdraw.comand->GetGraphicsCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			
			if (FBXLoader::GetMaterialTable()[0][materialidx].fecenum == 0)
			{
				continue;
			}
			//インデックスバッファーをセット
			fbxdraw.comand->GetGraphicsCommandList()->IASetIndexBuffer(FBXLoader::GetVertexIndexData()[0][materialidx].idxbuff->GetIndexBufferView());
			if (texF) {//テクスチャを使用するなら
				if (FBXLoader::GetMaterialTable()[0][materialidx].textureName.size() <= 0 ) {//そもそもテクスチャは無いなら
					whitetexM->TexregisterDraw(fbxdraw.comand, texture_register);//白テクスチャへ
				}
				else {
					auto texdata = FBXLoader::GetTextureData().at(FBXLoader::GetMaterialTable()[0][materialidx].textureName);//キーを得る
					if (texdata[0] != nullptr) {//レイヤテクスチャに対応しない
						texdata[0]->DrawImage(fbxdraw.comand, 1, texture_register);
					}
					else {
						whitetexM->TexregisterDraw(fbxdraw.comand, texture_register);//白テクスチャへ
					}
				}
				
				
			}
			//定数
			UploadConstant(fbxdraw.comand, 0, materialidx, cbffmat);
			cbffmat = (DR_MAT*)(((char*)cbffmat) + ((sizeof(DR_MAT) + 0xff) & ~0xff));
			auto heap = _cb->GetDescHeap();
			fbxdraw.comand->GetGraphicsCommandList()->SetDescriptorHeaps(1, &heap);
			fbxdraw.comand->GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(ROOT_PARAM_CONSTANT_DR, handle_cbuff);
			handle_cbuff.ptr += fbxdraw.device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			//Draw
			fbxdraw.comand->GetGraphicsCommandList()->DrawIndexedInstanced(FBXLoader::GetMaterialTable()[0][materialidx].fecenum, 1, indexcount, 0, 0);
			indexcount += FBXLoader::GetMaterialTable()[0][materialidx].fecenum;

		}
	


}
void FBXManager::SetScaleQuaternion(const Vector3& scale) {
	_scaling = XMLoadFloat3(&XMFLOAT3(scale.x, scale.y, scale.z));
}
void FBXManager::UploadConstant(std::shared_ptr<ComandManager>& comand, const int meshidx, const int materialidx, DR_MAT* address) {






	//クウォータニオンでワールド行列の作成
	XMFLOAT3 sOrigin = { 0,0,0 };
	XMFLOAT4 svecq = { 0,0,0,1 };
	XMVECTOR so = XMLoadFloat3(&sOrigin);
	XMVECTOR svec = XMLoadFloat4(&svecq);
	auto worldmat =XMMatrixTransformation(
		so,//拡縮するときの原点
		svec,//拡縮するときの向きベクトル
		_scaling,//各縮率
		_origin, //回転軸の”原点”の平行移動
		_rotationAxis,//回転軸と回転角度
		_translation //座標
	);

	
	address->dr_diffuse_color = FBXLoader::GetMaterialTable()[meshidx][materialidx].diffuse;
	address->dr_ambient_color = FBXLoader::GetMaterialTable()[meshidx][materialidx].ambient;
	address->dr_specular_color = FBXLoader::GetMaterialTable()[meshidx][materialidx].specular;
	//クウォータニオンでワールド行列作成
	address->dr_world_inv = XMMatrixInverse(nullptr, worldmat);
	address->dr_world_trans = XMMatrixTranspose(worldmat);
	address->dr_world = worldmat;

	
}

void FBXManager::SetRotateQuaternion(const Vector3& axis, float angle) {
	_rotationAxis = XMQuaternionRotationAxis(XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(axis.x, axis.y, axis.z))),angle);
}
void FBXManager::SetRotateQuaternion_Slerp(const DirectX::XMVECTOR& oldvec,const DirectX::XMVECTOR& newvector, float t) {
	_rotationAxis = XMQuaternionSlerp(oldvec, newvector,t);
}
void FBXManager::SetRotateQuaternion_mul(const Vector3& axis, float angle) {
	auto newqvec = XMQuaternionRotationAxis(XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(axis.x, axis.y, axis.z))), angle);
	_rotationAxis = XMQuaternionMultiply(_rotationAxis, newqvec);
}
void FBXManager::SetRotateQuaternionOrigin(const Vector3& origin) {
	XMFLOAT3 t = { origin.x,origin.y,origin.z };
	_origin = XMLoadFloat3(&t);
}
void FBXManager::SetPostionQuaternion(const Vector3& pos) {
	_translation = XMLoadFloat3(&XMFLOAT3(pos.x, pos.y, pos.z));
}
XMVECTOR FBXManager::GetRotateQuaternion() {
	return _rotationAxis;
}
DirectX::XMVECTOR FBXManager::CreateRotateQuaternion(const Vector3& axis,float angle) {
	return XMQuaternionRotationAxis(XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(axis.x, axis.y, axis.z))), angle);
}
void FBXManager::SetRotateQuaternion_Euler(const Vector3& rotation) {
	_rotationAxis = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
}
void FBXManager::SetRotateQuaternion_Matrix(XMMATRIX rotatemat) {
	_rotationAxis = XMQuaternionMultiply(_rotationAxis, XMQuaternionRotationMatrix(rotatemat));
}

void FBXManager::CbuffCreate(std::shared_ptr<D3D12DeviceManager>& device) {
	//定数用ヒープの量計算
	int matcountnum = 0;
	matcountnum += static_cast<int>(FBXLoader::GetMaterialTable()[0].size());//1meshだけとする
	std::shared_ptr<ConstantManager> cm(new ConstantManager());
	cm->CreateConstantBufferAndView(device, sizeof(DR_MAT), matcountnum);
	_cbuffAddress = nullptr;
	cm->ConstantbufferMap(&_cbuffAddress);
	_cb = cm;

	//Skin()
	std::shared_ptr<ConstantManager> cmb(new ConstantManager());
	cmb->CreateConstantBufferAndView(device, sizeof(JOINTBONE), 1);
	_cbuffAddressSkinning = nullptr;
	cmb->ConstantbufferMap(&_cbuffAddressSkinning);
	_cbbone = cmb;
	//initpaletteMat
	for (int i = 0; i < 256; i++) {
		_cbuffAddressSkinning->jointMatrix[i] = DirectX::XMMatrixIdentity();
	}

}
int FBXManager::GetAnimFrameEndPos(const std::string& animname) {
	return FBXLoader::GetAnimationFrameEnd(animname);
}
DirectX::XMMATRIX FBXManager::GetWorldMatinv() {
	return _cbuffAddress->dr_world_inv;
}

void FBXManager::AnimationPlay(const std::string& animname, const int frametime) {
	_animinfo.animname = animname;
	_animinfo.animationF = true;//アニメーションをplayする場合問答無用でtrueにします。
	_animinfo.animationFrame = frametime;
}
void FBXManager::AnimationEND() {
	_animinfo.animationF = false;
}
