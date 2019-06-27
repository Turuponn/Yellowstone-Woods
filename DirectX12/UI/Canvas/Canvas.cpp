#include "Canvas.h"
#include <d3d12.h>
#include "constance.h"
#include "DirectXManagers/Shada/Vertex/VertexShadaManager.h"
#include "DirectXManagers/Shada/Pixcel/PixcelShadaManager.h"
#include "DirectXManagers/PipelineState/PipelineStateManager.h"
#include "DirectXManagers/Device/D3D12DeviceManager.h"
#include "DirectXManagers/rootsignature/RootSignatureManager.h"
#include "DirectXManagers/comand/ComandManager.h"
#include "DirectXManagers/vertex/VertexBufferManager.h"
#include "DirectXManagers/constance/ConstantManager.h"
#include "DirectXManagers/Texture/TextureManager.h"
#include "WhiteTexture/WhiteTextureManager.h"
#include "Camera/Camera.h"

using namespace DirectX;

namespace {
	//取りうる値がとんでもない値になるためいったん保存
	const int screenn_size_x = SCREEN_SIZE_X;
	const int screenn_size_y = SCREEN_SIZE_Y;
	//正規化用最大値と最小値
	const int MAX = 1;
	const int MIN = -1;
}


Canvas::Canvas() {
	_vaddress = nullptr;
	_usetextureF = false;

	_canvasmat.canvas_rotate = 0;
	_canvasmat.canvas_rotateorigin = { 0,0,0 };
	_canvasmat.canvas_scale = { 1,1,1 };
	_canvasmat.canvas_translate = { 0,0,0 };
}
Canvas::~Canvas() {

}


void Canvas::CreateShada(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature, SHADA_CANVAS& shadalayer) {
	std::shared_ptr<VertexShadaManager> vs(new VertexShadaManager());
	std::shared_ptr<PixcelShadaManager> ps(new PixcelShadaManager());
	std::shared_ptr<PipelineStateManager> pipe(new PipelineStateManager());
	_vs = vs;
	_ps = ps;
	_pipe = pipe;
	_vs->CreateVertexShada(shadalayer.VSFilepath, shadalayer.FancnameVS);
	_ps->CreatePixelShada(shadalayer.PSFilepath, shadalayer.FancnamePS);
	_pipe->CreatePiplineState(device, rootsignature, &shadalayer.inputLaout[0], shadalayer.inputLaout.size(), _vs, _ps);
}
void Canvas::CreateVertexBuffer(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<VertexBufferManager> vbuffM(new VertexBufferManager());
	vbuffM->CreateVertexBuffer(device, _vertexs.size(), sizeof(VERTEX_CANVAS));
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
void Canvas::CreateConstanceBuffer(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<ConstantManager> cbuff(new ConstantManager());
	_cbuff = cbuff;
	_cbuff->CreateConstantBufferAndView(device, sizeof(CBUFF_CANVAS), 1);
	_cbuff->ConstantbufferMap(&_cbuffaddress);
	_cbuffaddress->canvas_world = DirectX::XMMatrixIdentity();
	_cbuff->ConstantbufferUnMap();
}
void Canvas::CreateMeshData() {
	_vertexs.push_back(VERTEX_CANVAS(XMFLOAT3(-1, -1, 0), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 1)));
	_vertexs.push_back(VERTEX_CANVAS(XMFLOAT3(-1, 1, 0), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)));
	_vertexs.push_back(VERTEX_CANVAS(XMFLOAT3(1, -1, 0), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)));
	_vertexs.push_back(VERTEX_CANVAS(XMFLOAT3(1, 1, 0), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)));
}
void Canvas::UpdateCbuffer(std::shared_ptr<Camera>& camera, std::shared_ptr<ComandManager>& comand) {
	_cbuff->ConstantbufferMap(&_cbuffaddress);

	 auto newworldmat = XMMatrixAffineTransformation2D(
		_canvasmat.canvas_scale,
		_canvasmat.canvas_rotateorigin,
		_canvasmat.canvas_rotate,
		_canvasmat.canvas_translate
		);
	 _cbuffaddress->canvas_world = newworldmat;

	
	_cbuff->ConstantbufferUnMap();
	auto heap = _cbuff->GetDescHeap().Get();
	comand->GetGraphicsCommandList()->SetDescriptorHeaps(1, &heap);
	comand->GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(ROOT_PARAM_CONSTANT_CANVAS, heap->GetGPUDescriptorHandleForHeapStart());

}
void Canvas::CreateTextureCanvas(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand,const std::string& filepath) {
	std::shared_ptr<TextureManager> texture(new TextureManager());
	_textureM = texture;
	_textureM->WICLoadTexture(device,comand,filepath);//白テクスチャ
}
void Canvas::SetRotateOrigin(const Vector3& neworigin) {
	_canvasmat.canvas_rotateorigin = { neworigin.x ,neworigin.y,neworigin.z };
}
void Canvas::SetPos(const Vector3& newpos) {
	//スクリーン座標系を作成するために
	//任意のMIN~MAXの範囲に正規化します
	Vector3 newv = {
		((MAX - MIN)*(newpos.x - -screenn_size_x)) / (screenn_size_x - -screenn_size_x) + MIN,
		((MAX - MIN)*(newpos.y - -screenn_size_y)) / (screenn_size_y - -screenn_size_y) + MIN,
		0//Zは無視する
	};
	//原点(0,0)に対し、offset値を足し合わせ左上原点を作成します。
	newv.x += -1;
	newv.y += 1;
	_canvasmat.canvas_translate = { newv.x,newv.y,newv.z };
}
void Canvas::SetScale(const Vector3& newscale) {
	_canvasmat.canvas_scale = { newscale.x ,newscale.y,newscale.z };
}
void Canvas::SetRotate(const float newrotate) {
	_canvasmat.canvas_rotate = newrotate;
}
void Canvas::DrawCanvas(std::shared_ptr<ComandManager>& comand, std::shared_ptr<Camera>& camera, std::shared_ptr<WhiteTextureManager>& whitetexm) {
	_pipe->SetPipeline(comand);
	UpdateCbuffer(camera,comand);
	//TextureDraw
	if (_usetextureF == false) {//テクスチャを使用しない場合
		whitetexm->TexregisterDraw(comand, TEX_CANVAS_COLOR);
	}
	else {
		_textureM->DrawImage(comand,1, TEX_CANVAS_COLOR);
	}
	//MeshDraw
	comand->GetGraphicsCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	comand->GetGraphicsCommandList()->IASetVertexBuffers(0, 1, _vertexM->GetVertexBufferView());
	comand->GetGraphicsCommandList()->DrawInstanced(_vertexs.size(), 1, 0, 0);
}
void Canvas::CreateCanvas(
	std::shared_ptr<D3D12DeviceManager>& device,
	std::shared_ptr<RootSignatureManager>& rootsignature,
	std::shared_ptr<ComandManager>& comand,
	SHADA_CANVAS& shadacanvas,
	const std::string& filepath = ""
) {
	CreateMeshData();
	CreateShada(device, rootsignature, shadacanvas);
	CreateVertexBuffer(device);
	CreateConstanceBuffer(device);
	int b = filepath.capacity();
	if (filepath.size() <= 0) {//パスが空なら　Textureを使わない
		_usetextureF = false;
	}
	else {
		_usetextureF = true;
		CreateTextureCanvas(device,comand,filepath);
	}
}