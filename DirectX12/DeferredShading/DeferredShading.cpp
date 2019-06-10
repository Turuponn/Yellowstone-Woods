#include "DeferredShading/DeferredShading.h"
#include <d3d12.h>
#include "Library\DirectX12Create\RenderTargetCreate.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "constance.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\DepthStencil\Depth\DepthManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\Shada\Vertex\VertexShadaManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Shada\Pixcel\PixcelShadaManager.h"
#include "DirectXManagers\RenderTarget\RenderTargetManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers/Shada/GS/GSManager.h"
#include "Camera/Camera.h"
#include "d3dx12.h"
#include "Layer/Layer.h"

using namespace std;

namespace {
	enum class GbuffLaout {
		COLOR,
	};

	const int RTVNUM = 1;
	DXGI_FORMAT _rtvFormat[RTVNUM] = {//Gバッファのレイアウト
		DXGI_FORMAT_R8G8B8A8_UNORM,//カラーマップ
	};




	//Gバッファ計算用シェーダ
	wchar_t* VSFilepath = _T("resource/ShadaFile/DeferredShading/DeferredShadingVS.hlsl");
	wchar_t* PSFilepath = _T("resource/ShadaFile/DeferredShading/DeferredShadingPS.hlsl");
	wchar_t* GSFilepath = _T("resource/ShadaFile/DeferredShading/DeferredShadingGS.hlsl");
	char* FancnameVS = "DSVS";
	char* FancnamePS = "DSPS";
	char* FancnameGS = "DSGS";

	D3D12_INPUT_ELEMENT_DESC inputLaout[] = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0,
		},
		{
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		  {
			"WEIGHTIDX",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0,
		},
		{
			"JOINTIDX",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0,
		 },
	};

	//レイヤ用
	wchar_t* VSFilepath2 = _T("resource/ShadaFile/DeferredShading/ShadingVS.hlsl");
	wchar_t* PSFilepath2 = _T("resource/ShadaFile/DeferredShading/ShadingPS.hlsl");
	char* FancnameVS2 = "SVS";
	char* FancnamePS2 = "SPS";

	D3D12_INPUT_ELEMENT_DESC inputLaout2[] = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0,
		},
		{
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};
	
}

DeferredShading::DeferredShading() {

}
DeferredShading::~DeferredShading() {

}
void DeferredShading::CreateGbuffer(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature) {
	
	
	CreateRT(device);
	CreateSRV(device, comand);
	CreateVS();
	CreatePS();
	CreateGS();
	CreatePipeline(device, rootsignature);
}
void DeferredShading::Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature) {
	std::shared_ptr< Layer> layer(new Layer());
	_layer = layer;
	SHADA_LAYER l = {};
	l.FancnamePS = FancnamePS2;
	l.FancnameVS = FancnameVS2;
	std::vector<D3D12_INPUT_ELEMENT_DESC> _inputlaout;
	for (auto& in : inputLaout) {
		_inputlaout.push_back(in);
	}
	l.inputLaout = _inputlaout;
	l.PSFilepath = PSFilepath2;
	l.VSFilepath = VSFilepath2;

	_layer->CreateLayer(device,rootsignature,l);
	CreateGbuffer(device,comand,rootsignature);
}
void DeferredShading::CreateRT(std::shared_ptr<D3D12DeviceManager>& device) {
	shared_ptr<RenderTargetCreate> rtc(new RenderTargetCreate());
	rtc->RTVCreateHeaps(device->GetDevice(), RTVNUM, &_rtvheap);
	_rtvbuffer.resize(RTVNUM);
	SIZE_T ptr = _rtvheap->GetCPUDescriptorHandleForHeapStart().ptr;
	SIZE_T offsetted = 0;
	for (int i = 0; i < RTVNUM; i++) {
		rtc->CreateRTBuffer(
			device->GetDevice(),
			SCREEN_SIZE_X,
			SCREEN_SIZE_Y,
			D3D12_RESOURCE_STATE_RENDER_TARGET,//リソースの状態を切り替える必要がない
			DXGI_FORMAT_R8G8B8A8_UNORM,//テクスチャ用フォーマット
			&_rtvbuffer[i]
		);
		offsetted = ptr + static_cast<SIZE_T>(i * device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		D3D12_CPU_DESCRIPTOR_HANDLE desc = {};
		desc.ptr = offsetted;
		rtc->CreateRTVViews(
			device->GetDevice(),
			desc,
			_rtvbuffer[i].Get(),
			DXGI_FORMAT_R8G8B8A8_UNORM //テクスチャ用フォーマット
		);
	}
}
void DeferredShading::CreateSRV(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand) {
	for (int i = 0; i < RTVNUM; i++) {
		shared_ptr<TextureManager> texM(new TextureManager());
		_texMs.push_back(texM);
		_texMs[i]->SRVCreateHeap(device);
		_texMs[i]->SRVCreateView(device, DXGI_FORMAT_R8G8B8A8_UNORM, _rtvbuffer[i]);
	}
}
void DeferredShading::CreateVS() {
	//通常
	shared_ptr<VertexShadaManager> vs(new VertexShadaManager());
	_vs = vs;
	_vs->CreateVertexShada(VSFilepath, FancnameVS);
}
void DeferredShading::CreatePS() {
	//通常
	shared_ptr<PixcelShadaManager> ps(new PixcelShadaManager());
	_ps = ps;
	_ps->CreatePixelShada(PSFilepath, FancnamePS);
}
void DeferredShading::CreateGS() {
	shared_ptr<GSManager> gs(new GSManager());
	_gs = gs;
	_gs->CreateShada(GSFilepath, FancnameGS);
}
void DeferredShading::CreatePipeline(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature) {
	_rtvformats.resize(RTVNUM);
	for (int i = 0; i < RTVNUM; i++) {
		_rtvformats[i] = _rtvFormat[i];
	}

	shared_ptr<PipelineStateManager> p(new PipelineStateManager());
	_mrtPipeline = p;
	PSTATEM psatate = {
		device,
		rootsignature,
		inputLaout,
		_countof(inputLaout),
		_vs,
		_ps,
		_gs
	};
	_mrtPipeline->CreatePStateDeferred(psatate, _rtvformats);
}

void DeferredShading::PreRender(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RenderTargetManager>& rtvmanager, std::shared_ptr<DepthManager>& depth,std::shared_ptr< Camera>& camera,std::shared_ptr< FenceManager>& fence) {
	_mrtPipeline->SetPipeline(comand);
	for (auto& buff : _rtvbuffer) {
		comand->ComandRBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET,D3D12_RESOURCE_STATE_PRESENT, buff.Get());
	}
	rtvmanager->UpdataRTVs(device, comand, depth, _rtvheap->GetCPUDescriptorHandleForHeapStart(), RTVNUM);
	for (auto& buff : _rtvbuffer) {
		comand->ComandRBarrier(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, buff.Get());
	}
	_layer->DrawScreen(comand,device, camera, fence);
}
void DeferredShading::PostRender(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence) {
	Draw(comand, fence);
}
void DeferredShading::Draw(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence) {
	comand->ComandSetDescriptorHeaps(1, _texMs[(int)GbuffLaout::COLOR]->GetSrvHeap());
	comand->ComandSetGraphicsRootDescriptorTable(ROOT_PARAM_TEXTURE_DL_COLOR, _texMs[(int)GbuffLaout::COLOR]->GetSrvHeap());
}
void DeferredShading::SetDrawPipeline(std::shared_ptr<ComandManager>& comand) {
	_mrtPipeline->SetPipeline(comand);
}