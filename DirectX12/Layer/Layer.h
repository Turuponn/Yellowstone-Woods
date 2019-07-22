#pragma once


#include <memory>
#include <string>
#include <vector>
#include <tchar.h>
#include "Geometori.h"


class VertexShadaManager;
class PixcelShadaManager;
class PipelineStateManager;
class D3D12DeviceManager;
class RootSignatureManager;
class RenderTargetManager;
struct ID3D12DescriptorHeap;
class TextureManager;
class ComandManager;
class DepthManager;
struct ID3D12Resource;
class FenceManager;
class VertexBufferManager;
class ConstantManager;
class Camera;
class RenderTargetCreate;
class DeferredRenderManager;
struct D3D12_INPUT_ELEMENT_DESC;


struct VERTEX_LAYER {
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;

	VERTEX_LAYER() {}
	VERTEX_LAYER(DirectX::XMFLOAT3& newp, DirectX::XMFLOAT3& newn, DirectX::XMFLOAT2& newuv) : pos(newp), normal(newn), uv(newuv) {}
};


struct CBUFF_LAYER {
	DirectX::XMMATRIX layer_world;
	DirectX::XMMATRIX layer_scale;
	DirectX::XMMATRIX layer_rotate;
	DirectX::XMMATRIX layer_translate;
};

struct SHADA_LAYER {
	wchar_t* VSFilepath;
	wchar_t* PSFilepath;
	char* FancnameVS;
	char* FancnamePS;
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLaout;
};



class Layer {
private:
	void CreateShada(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature, SHADA_LAYER& shadalayer);
	void CreateVertexBuffer(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateCbuff(std::shared_ptr<D3D12DeviceManager>& device);
	void Cbuffer(std::shared_ptr<ComandManager>& comand, std::shared_ptr<Camera>& camera);
	DirectX::XMMATRIX Billbord(DirectX::XMMATRIX& viewmat);
	void SetParam(std::shared_ptr<Camera>& camera);
public:
	Layer();
	virtual ~Layer();

	/// <summary>
	/// レイヤの作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rootsignature"></param>
	void CreateLayer(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature, SHADA_LAYER& shadalayer);
	/// <summary>
	/// スクリーンの描画
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="device"></param>
	void DrawScreen(std::shared_ptr<ComandManager>& comand, std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<Camera>& camera, std::shared_ptr<FenceManager>& fence);



private:
	std::shared_ptr<VertexShadaManager> _vs;
	std::shared_ptr<PixcelShadaManager> _ps;
	std::shared_ptr<PipelineStateManager> _pipe;
	std::shared_ptr<VertexBufferManager> _vertexM;
	std::shared_ptr<ConstantManager> _cbuff;

	std::vector<VERTEX_LAYER> _vertexs;
	VERTEX_LAYER* _vaddress;
	CBUFF_LAYER *_cbuffaddress;
	

	//回転行列
	DirectX::XMMATRIX _rotatemat;
	Vector3 _rotation;

	//拡縮行列
	DirectX::XMMATRIX _scalemat;
	Vector3 _bounds;

	//平行移動行列
	DirectX::XMMATRIX _translationmat;
	Vector3 _postion;

};