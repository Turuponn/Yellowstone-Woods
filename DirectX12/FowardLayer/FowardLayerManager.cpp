#include "FowardLayerManager.h"
#include <d3d12.h>
#include <tchar.h>
#include "Layer/Layer.h"
#include "DirectXManagers/Device/D3D12DeviceManager.h"
#include "DirectXManagers/rootsignature/RootSignatureManager.h"
#include "DirectXManagers/comand/ComandManager.h"
#include "Camera/Camera.h"
#include "DirectXManagers/Fence/FenceManager.h"

namespace {
	wchar_t* VSFilepath = _T("resource/ShadaFile/Foward/FowardVS.hlsl");
	wchar_t* PSFilepath = _T("resource/ShadaFile/Foward/FowardPS.hlsl");
	char* FancnameVS = "FVS";
	char* FancnamePS = "FPS";
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
	};
}

FowardLayerManager::FowardLayerManager() {

}
FowardLayerManager::~FowardLayerManager() {

}

void FowardLayerManager::CreateLayer(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<RootSignatureManager>& rootsignature) {
	std::shared_ptr< Layer> layer(new Layer());
	_layer = layer;
	SHADA_LAYER s = {};
	s.VSFilepath = VSFilepath;
	s.PSFilepath = PSFilepath;
	s.FancnameVS = FancnameVS;
	s.FancnamePS = FancnamePS;
	std::vector<D3D12_INPUT_ELEMENT_DESC> _inputlaout;
	for (auto& in : inputLaout) {
		_inputlaout.push_back(in);
	}
	s.inputLaout = _inputlaout;
	_layer->CreateLayer(device, rootsignature, s);

}
void FowardLayerManager::Draw(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand,std::shared_ptr<Camera>& camera,std::shared_ptr<FenceManager>& fence) {
	_layer->DrawScreen(comand,device, camera, fence);
}