#include "RECTUI.h"
#include "GameEngine/GameEngine.h"
#include "DirectXManagers/Device/D3D12DeviceManager.h"
#include "DirectXManagers/comand/ComandManager.h"
#include "DirectXManagers/rootsignature/RootSignatureManager.h"
#include "../Canvas/Canvas.h"
#include "Camera/Camera.h"
#include "WhiteTexture/WhiteTextureManager.h"
#include <d3d12.h>

namespace RECT_NS {
	wchar_t* _vsfilepath = _T("resource/ShadaFile/UI/UIRectVertexShada.hlsl");
	wchar_t* _psfilepath = _T("resource/ShadaFile/UI/UIRectPixelShada.hlsl");
	char* _vsfuncname = "UIRectVertexShada";
	char* _psfuncname = "UIRectPixelShada";

	D3D12_INPUT_ELEMENT_DESC _inputLaout[] = {
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
		}
	};
}

RECTUI::RECTUI() {

}
RECTUI::~RECTUI() {

}


void RECTUI::CreateUIRect(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand,std::shared_ptr<RootSignatureManager>& rootsignature,const std::string& filepath) {
	std::shared_ptr<Canvas> canvas(new Canvas());
	_canvas = canvas;
	SHADA_CANVAS shadacanvas = {};
	shadacanvas.VSFilepath = RECT_NS::_vsfilepath;
	shadacanvas.FancnameVS = RECT_NS::_vsfuncname;
	shadacanvas.PSFilepath = RECT_NS::_psfilepath;
	shadacanvas.FancnamePS = RECT_NS::_psfuncname;
	std::vector<D3D12_INPUT_ELEMENT_DESC> _inputlaout;
	for (auto& in : RECT_NS::_inputLaout) {
		_inputlaout.push_back(in);
	}
	shadacanvas.inputLaout = _inputlaout;
	_canvas->CreateCanvas(device, rootsignature, comand, shadacanvas, filepath);
}

void RECTUI::DrawRect(std::shared_ptr<ComandManager>& comand,std::shared_ptr<Camera>& camera,std::shared_ptr<WhiteTextureManager>& whitetexM) {
	_canvas->DrawCanvas(comand, camera, whitetexM);
}
void RECTUI::SetPos(const Vector3& newpos) {
	_canvas->SetPos(newpos);
}
void RECTUI::SetScale(const Vector3& newscale) {
	_canvas->SetScale(newscale);
}
void RECTUI::SetRotate(const float newrotate) {
	_canvas->SetRotate(newrotate);
}
void RECTUI::SetRotateOrigin(const Vector3& newrotateorigin) {
	_canvas->SetRotateOrigin(newrotateorigin);
}
void RECTUI::SetColor(const Vector4& newcolor) {
	_canvas->SetColor(newcolor);
}