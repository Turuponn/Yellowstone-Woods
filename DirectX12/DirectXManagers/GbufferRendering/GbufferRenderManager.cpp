#include "GbufferRenderManager.h"
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
#include "DirectXManagers\swapchain\SwapChainManager.h"
#include "Graphics\Graphics.h"
#include "d3dx12.h"

using namespace std;


enum class GbuffLaout {
	COLOR,
	NORMAL,
	POS,
};

namespace {
	const int RTVNUM = 3;//オフスクリーンバッファの数
	DXGI_FORMAT _rtvFormat[RTVNUM] = {//Gバッファのレイアウト
		DXGI_FORMAT_R8G8B8A8_UNORM,//カラーマップ
		DXGI_FORMAT_R10G10B10A2_UNORM,//法線データ
		DXGI_FORMAT_R32G32B32A32_FLOAT,//ポジションマップ 　精度はMAX
	};




	//Gバッファ計算用シェーダ
	wchar_t* VSFilepath = _T("resource/ShadaFile/Gbuffer/GbufferVertexShader.hlsl");
	wchar_t* PSFilepath = _T("resource/ShadaFile/Gbuffer/GbufferPixelShader.hlsl");
	char* FancnameVS = "GbufferVS";
	char* FancnamePS = "GbufferPS";
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

	//Gbuff CubeMap
	wchar_t* Cmap_VSFilepath = _T("resource/ShadaFile/Gbuffer/DRCMapVertexShader.hlsl");
	wchar_t* Cmap_PSFilepath = _T("resource/ShadaFile/Gbuffer/DRCMapPixelShader.hlsl");
	char* Cmap_FancnameVS = "DRCMapVS";
	char* Cmap_FancnamePS = "DRCMapPS";
	D3D12_INPUT_ELEMENT_DESC iLaoutCMap[] = {
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

	//追加機能========================================
	wchar_t* GSFilepath = _T("resource/ShadaFile/GS/DRGeometryShader.hlsl");
	char* FancnameGS = "GSMain";
}

GbufferRenderManager::GbufferRenderManager() {

}
GbufferRenderManager::~GbufferRenderManager() {
	
}


void GbufferRenderManager::CreateGbuffer(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature) {
	_rtvformats.resize(RTVNUM);
	for (int i = 0; i < RTVNUM; i++) {
		_rtvformats[i] = _rtvFormat[i];
	}
	CreateRT(device);
	CreateSRV(device, comand);
	CreateVS();
	CreatePS();
	CreateGS();
	CreatePipeline(device, rootsignature);
}
void GbufferRenderManager::CreateRT(std::shared_ptr<D3D12DeviceManager>& device) {
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
			_rtvformats[i],
			&_rtvbuffer[i]
		);
		offsetted = ptr + static_cast<SIZE_T>(i * device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		D3D12_CPU_DESCRIPTOR_HANDLE desc = {};
		desc.ptr = offsetted;
		rtc->CreateRTVViews(
			device->GetDevice().Get(),
			desc,
			_rtvbuffer[i].Get(),
			_rtvformats[i]
		);
	}
}
void GbufferRenderManager::CreateSRV(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand) {
	for (int i = 0; i < RTVNUM; i++) {
		shared_ptr<TextureManager> texM(new TextureManager());
		_texMs.push_back(texM);
		_texMs[i]->SRVCreateHeap(device);
		auto b = _rtvbuffer[i].Get();
		_texMs[i]->SRVCreateView(device, _rtvformats[i], b);
	}
}
void GbufferRenderManager::CreateVS() {
	//通常
	shared_ptr<VertexShadaManager> vs(new VertexShadaManager());
	_vs = vs;
	_vs->CreateVertexShada(VSFilepath, FancnameVS);
	//キューブマップ
	shared_ptr<VertexShadaManager> cmapvs(new VertexShadaManager());
	_cmapvs = cmapvs;
	_cmapvs->CreateVertexShada(Cmap_VSFilepath, Cmap_FancnameVS);

}
void GbufferRenderManager::CreatePS() {
	//通常
	shared_ptr<PixcelShadaManager> ps(new PixcelShadaManager());
	_ps = ps;
	_ps->CreatePixelShada(PSFilepath, FancnamePS);
	//キューブマップ
	shared_ptr<PixcelShadaManager> cmapps(new PixcelShadaManager());
	_cmapps = cmapps;
	_cmapps->CreatePixelShada(Cmap_PSFilepath, Cmap_FancnamePS);
}
void GbufferRenderManager::CreateGS() {
	shared_ptr<GSManager> gs(new GSManager());
	_gs = gs;
	_gs->CreateShada(GSFilepath, FancnameGS);
}
void GbufferRenderManager::CreatePipeline(shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature) {



	//通常
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
	_rtvformats.resize(RTVNUM);
	_mrtPipeline->CreatePStateDeferred(psatate, _rtvformats);
	//CubaMap
	shared_ptr<PipelineStateManager> cmapp(new PipelineStateManager());
	_cmapP = cmapp;
	PSTATEM cmap_psatate = {
		device,
		rootsignature,
		iLaoutCMap,
		_countof(iLaoutCMap),
		_cmapvs,
		_cmapps,
		_gs
	};
	_rtvformats.resize(RTVNUM);
	_cmapP->CreatePStateDeferred(cmap_psatate, _rtvformats);

}

void GbufferRenderManager::PreRender(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<Graphics>& graphics, std::shared_ptr<SwapChainManager>& swapchain) {
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
}
void GbufferRenderManager::PostRender(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence) {
	Draw(comand, fence);
}
void GbufferRenderManager::Draw(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence) {
	//Gバッファのレイアウト通りにテクスチャへ
	auto c = _texMs[(int)GbuffLaout::COLOR]->GetSrvHeap().Get();
	comand->ComandSetDescriptorHeaps(1, c);
	comand->ComandSetGraphicsRootDescriptorTable(TEX_DR_COLOR, c);

	auto n = _texMs[(int)GbuffLaout::NORMAL]->GetSrvHeap().Get();
	comand->ComandSetDescriptorHeaps(1, n);
	comand->ComandSetGraphicsRootDescriptorTable(TEX_DR_NORMALMAP, n);

	auto p = _texMs[(int)GbuffLaout::POS]->GetSrvHeap().Get();
	comand->ComandSetDescriptorHeaps(1, p);
	comand->ComandSetGraphicsRootDescriptorTable(TEX_DR_POSMAP, p);


}
void GbufferRenderManager::SetCMapPipeline(std::shared_ptr<ComandManager>& comand) {
	_cmapP->SetPipeline(comand);
}
void GbufferRenderManager::SetDrawPipeline(std::shared_ptr<ComandManager>& comand) {
	_mrtPipeline->SetPipeline(comand);
}