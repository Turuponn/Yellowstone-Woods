#include "Layer/Layer.h"
#include <d3d12.h>
#include "DirectXManagers\Shada\Vertex\VertexShadaManager.h"
#include "DirectXManagers\Shada\Pixcel\PixcelShadaManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\RenderTarget\RenderTargetManager.h"
#include "DirectXManagers\DepthStencil\Depth\DepthManager.h"
#include <tchar.h>
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\vertex\VertexBufferManager.h"
#include "d3dx12.h"
#include "constance.h"
#include "DirectXManagers\constance\ConstantManager.h"
#include "Camera\Camera.h"
#include "Library\DirectX12Create\RenderTargetCreate.h"
#include "DirectXManagers\GbufferRendering\GbufferRenderManager.h"


using namespace DirectX;



Layer::Layer() {
	_vaddress = nullptr;
	_bounds = { 1,1,1 };
	_postion = { 1,1,1 };
	_rotation = { 1,1,1 };
}
Layer::~Layer() {

}
void Layer::CreateShada(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature, SHADA_LAYER& shadalayer) {
	std::shared_ptr<VertexShadaManager> vs(new VertexShadaManager());
	std::shared_ptr<PixcelShadaManager> ps(new PixcelShadaManager());
	std::shared_ptr<PipelineStateManager> pipe(new PipelineStateManager());
	_vs = vs;
	_ps = ps;
	_pipe = pipe;
	_vs->CreateVertexShada(shadalayer.VSFilepath, shadalayer.FancnameVS);
	_ps->CreatePixelShada(shadalayer.PSFilepath, shadalayer.FancnamePS);
	_pipe->CreatePipelineState(device, rootsignature, &shadalayer.inputLaout[0], shadalayer.inputLaout.size(), _vs, _ps);

}
void Layer::CreateLayer(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature, SHADA_LAYER& shadalayer) {
	std::shared_ptr<RenderTargetCreate> rtc(new RenderTargetCreate());
	CreateShada(device, rootsignature, shadalayer);
	CreateCbuff(device);
	_vertexs.push_back(VERTEX_LAYER(XMFLOAT3(-1, -1, 0), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 1)));
	_vertexs.push_back(VERTEX_LAYER(XMFLOAT3(-1, 1, 0), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)));
	_vertexs.push_back(VERTEX_LAYER(XMFLOAT3(1, -1, 0), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)));
	_vertexs.push_back(VERTEX_LAYER(XMFLOAT3(1, 1, 0), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)));
	CreateVertexBuffer(device);
}

void Layer::DrawScreen(std::shared_ptr<ComandManager>& comand, std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<Camera>& camera, std::shared_ptr<FenceManager>& fence) {
	_pipe->SetPipeline(comand);
	comand->GetGraphicsCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	comand->GetGraphicsCommandList()->IASetVertexBuffers(0, 1, _vertexM->GetVertexBufferView());
	SetParam(camera);
	Cbuffer(comand, camera);
	comand->GetGraphicsCommandList()->DrawInstanced(_vertexs.size(), 1, 0, 0);
}

void Layer::SetParam(std::shared_ptr<Camera>& camera) {
	_postion = camera->GetCameraPosition();
	_translationmat = DirectX::XMMatrixIdentity();
	_scalemat = XMMatrixScaling(1, 1, 1);
}
XMMATRIX Layer::Billbord(DirectX::XMMATRIX& viewmat) {
	XMMATRIX inv_mat = DirectX::XMMatrixInverse(nullptr, viewmat);
	return inv_mat;
}
void Layer::Cbuffer(std::shared_ptr<ComandManager>& comand, std::shared_ptr<Camera>& camera) {
	_cbuff->ConstantbufferMap(&_cbuffaddress);
	_cbuffaddress->layer_world = DirectX::XMMatrixIdentity();
	_cbuffaddress->layer_scale = _scalemat;
	_cbuffaddress->layer_translate = _translationmat;
	auto invmat = Billbord(camera->GetCameraView());
	_cbuffaddress->layer_rotate = invmat;
	_cbuff->ConstantbufferUnMap();
	auto heap = _cbuff->GetDescHeap();//TODO:
	comand->GetGraphicsCommandList()->SetDescriptorHeaps(1, &heap);
	comand->GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(ROOT_PARAM_CONSTANT_LAYER, heap->GetGPUDescriptorHandleForHeapStart());
}
void Layer::CreateVertexBuffer(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<VertexBufferManager> vbuffM(new VertexBufferManager());
	vbuffM->CreateVertexBuffer(device, _vertexs.size(), sizeof(VERTEX_LAYER));
	vbuffM->ResoceMap(&_vaddress);
	DISABLE_C4996
		std::copy(
			_vertexs.begin(),
			_vertexs.end(),
			_vaddress
		);
	ENABLE_C4996
		vbuffM->ResoceUnmap();
	_vertexM = vbuffM;
}
void Layer::CreateCbuff(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<ConstantManager> cbuff(new ConstantManager());
	_cbuff = cbuff;
	_cbuff->CreateConstantBufferAndView(device, sizeof(CBUFF_LAYER), 1);
	_cbuff->ConstantbufferMap(&_cbuffaddress);
	_cbuffaddress->layer_world = DirectX::XMMatrixIdentity();
	_cbuffaddress->layer_scale = DirectX::XMMatrixScaling(1, 1, 1);
	_cbuffaddress->layer_rotate = DirectX::XMMatrixRotationY(0);
	_cbuffaddress->layer_translate = DirectX::XMMatrixIdentity();
	_cbuff->ConstantbufferUnMap();
}