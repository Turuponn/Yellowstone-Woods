#include "PostProsess\PostProsessManager.h"
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
#include "DirectXManagers\Shada\GS\GSManager.h"
#include "Camera\Camera.h"
#include "d3dx12.h"
#include "Layer\Layer.h"
#include "DirectXManagers\swapchain\SwapChainManager.h"
#include "Graphics\Graphics.h"

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
	wchar_t* VSFilepath = _T("resource/ShadaFile/PostProsess/PostProsessVS.hlsl");
	wchar_t* PSFilepath = _T("resource/ShadaFile/PostProsess/PostProsessPS.hlsl");
	wchar_t* GSFilepath = _T("resource/ShadaFile/PostProsess/PostProsessGS.hlsl");
	char* FancnameVS = "PPVS";
	char* FancnamePS = "PPPS";
	char* FancnameGS = "PPGS";

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
	wchar_t* VSFilepath2 = _T("resource/ShadaFile/PostProsess/PostEffectVS.hlsl");
	wchar_t* PSFilepath2 = _T("resource/ShadaFile/PostProsess/PostEffectPS.hlsl");
	char* FancnameVS2 = "PEVS";
	char* FancnamePS2 = "PEPS";

	

}

PostProsessManager::PostProsessManager() {
}
PostProsessManager::~PostProsessManager() {
}
void PostProsessManager::CreateGbuffer(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature) {


	CreateRT(device);
	CreateSRV(device, comand);
	CreateVS();
	CreatePS();
	CreateGS();
	CreatePipeline(device, rootsignature);
}
void PostProsessManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature) {
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

	_layer->CreateLayer(device, rootsignature, l);
	CreateGbuffer(device, comand, rootsignature);//パスを追加するためにG-bufferの作成を行います。
}
void PostProsessManager::CreateRT(std::shared_ptr<D3D12DeviceManager>& device) {
	shared_ptr<RenderTargetCreate> rtc(new RenderTargetCreate());
	rtc->RTVCreateHeaps(device->GetDevice().Get(), RTVNUM, &_rtvheap);
	_rtvbuffer.resize(RTVNUM);
	SIZE_T ptr = _rtvheap->GetCPUDescriptorHandleForHeapStart().ptr;
	SIZE_T offsetted = 0;
	for (int i = 0; i < RTVNUM; i++) {
		rtc->CreateRTBuffer(
			device->GetDevice().Get(),
			SCREEN_SIZE_X,
			SCREEN_SIZE_Y,
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			DXGI_FORMAT_R8G8B8A8_UNORM,//テクスチャ用フォーマット
			&_rtvbuffer[i]
		);
		offsetted = ptr + static_cast<SIZE_T>(i * device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		D3D12_CPU_DESCRIPTOR_HANDLE desc = {};
		desc.ptr = offsetted;
		rtc->CreateRTVViews(
			device->GetDevice().Get(),
			desc,
			_rtvbuffer[i].Get(),
			DXGI_FORMAT_R8G8B8A8_UNORM //テクスチャ用フォーマット
		);
	}
}
void PostProsessManager::CreateSRV(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand) {
	for (int i = 0; i < RTVNUM; i++) {
		shared_ptr<TextureManager> texM(new TextureManager());
		_texMs.push_back(texM);
		_texMs[i]->SRVCreateHeap(device);
		auto resoce = _rtvbuffer[i].Get();
		_texMs[i]->SRVCreateView(device, DXGI_FORMAT_R8G8B8A8_UNORM, resoce);
	}
}
void PostProsessManager::CreateVS() {
	//通常
	shared_ptr<VertexShadaManager> vs(new VertexShadaManager());
	_vs = vs;
	_vs->CreateVertexShada(VSFilepath, FancnameVS);
}
void PostProsessManager::CreatePS() {
	//通常
	shared_ptr<PixcelShadaManager> ps(new PixcelShadaManager());
	_ps = ps;
	_ps->CreatePixelShada(PSFilepath, FancnamePS);
}
void PostProsessManager::CreateGS() {
	shared_ptr<GSManager> gs(new GSManager());
	_gs = gs;
	_gs->CreateShada(GSFilepath, FancnameGS);
}
void PostProsessManager::CreatePipeline(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature) {
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

void PostProsessManager::PreRender(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<Graphics>& graphics, std::shared_ptr<SwapChainManager>& swapchain, std::shared_ptr< Camera>& camera, std::shared_ptr< FenceManager>& fence) {
	_mrtPipeline->SetPipeline(comand);
	for (auto& buff : _rtvbuffer) {
		auto b = buff.Get();
		comand->ComandRBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, b);
	}
	graphics->RTVUpdata(device, comand, swapchain, _rtvheap->GetCPUDescriptorHandleForHeapStart(), RTVNUM);
	for (auto& buff : _rtvbuffer) {
		auto b = buff.Get();
		comand->ComandRBarrier(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, b);
	}
	graphics->RTVClear(comand, _rtvheap->GetCPUDescriptorHandleForHeapStart());
	_layer->DrawScreen(comand, device, camera, fence);
}
void PostProsessManager::PostRender(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence) {
	Draw(comand, fence);
}
void PostProsessManager::Draw(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence) {
	auto heap = _texMs[(int)GbuffLaout::COLOR]->GetSrvHeap().Get();
	comand->ComandSetDescriptorHeaps(1, heap);
	comand->ComandSetGraphicsRootDescriptorTable(ROOT_PARAM_TEXTURE_PP_COLOR, heap);
}
void PostProsessManager::SetDrawPipeline(std::shared_ptr<ComandManager>& comand) {
	_mrtPipeline->SetPipeline(comand);
}