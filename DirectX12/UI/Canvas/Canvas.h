#pragma once

#include <memory>
#include <string>
#include <vector>
#include <tchar.h>
#include "Geometori.h"

struct D3D12_INPUT_ELEMENT_DESC;
class VertexShadaManager;
class PipelineStateManager;
class PixcelShadaManager;
class VertexBufferManager;
class ConstantManager;
class D3D12DeviceManager;
class RootSignatureManager;
class ComandManager;
class Camera;
class TextureManager;
class WhiteTextureManager;


struct SHADA_CANVAS {
	wchar_t* VSFilepath;
	wchar_t* PSFilepath;
	char* FancnameVS;
	char* FancnamePS;
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLaout;
};
struct CBUFF_CANVAS {
	DirectX::XMMATRIX canvas_world;
	DirectX::XMFLOAT4 canvas_color;
};
struct VERTEX_CANVAS {
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;
	VERTEX_CANVAS() {}
	VERTEX_CANVAS(DirectX::XMFLOAT3& newp, DirectX::XMFLOAT3& newn, DirectX::XMFLOAT2& newuv) : pos(newp), normal(newn), uv(newuv) {}
};
struct WORLDMAT_CANVAS {
	DirectX::XMVECTOR canvas_scale;
	DirectX::XMVECTOR canvas_translate;
	DirectX::XMVECTOR canvas_rotateorigin;
	float canvas_rotate;
	DirectX::XMFLOAT4 canvas_color;
};


class Canvas {
private:
	void UpdateCbuffer(std::shared_ptr<Camera>& camera, std::shared_ptr<ComandManager>& comand);
private:
	void CreateShada(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature, SHADA_CANVAS& shadalayer);
	void CreateVertexBuffer(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateConstanceBuffer(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateMeshData();
	void CreateTextureCanvas(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		const std::string& filepath
	);
public:
	Canvas();
	~Canvas();
	/// <summary>
	/// キャンバスを作成します
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rootsignature"></param>
	/// <param name="comand"></param>
	/// <param name="shadacanvas"></param>
	/// <param name="filepath"></param>
	void CreateCanvas(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		std::shared_ptr<ComandManager>& comand,
		SHADA_CANVAS& shadacanvas,
		const std::string& filepath
	);
	/// <summary>
	/// キャンバスにuiを表示します
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="camera"></param>
	/// <param name="whitetexm"></param>
	void DrawCanvas(
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<Camera>& camera,
		std::shared_ptr<WhiteTextureManager>& whitetexm
	);
	/// <summary>
	/// 新しい座標を入力
	/// </summary>
	void SetPos(const Vector3& newpos);
	/// <summary>
	/// 新しい拡縮率を入れる
	/// </summary>
	/// <param name="newscale"></param>
	void SetScale(const Vector3& newscale);
	/// <summary>
	/// 回転原点を入力します
	/// </summary>
	/// <param name="neworigin"></param>
	void SetRotateOrigin(const Vector3& neworigin);
	/// <summary>
	/// 色を指定します
	/// </summary>
	/// <param name="newcolor"></param>
	void SetColor(const Vector4& newcolor);
	/// <summary>
	/// 回転量を入れる
	/// </summary>
	/// <param name="newrotate"></param>
	void SetRotate(const float newrotate);


private:
	std::shared_ptr<VertexShadaManager> _vs;
	std::shared_ptr<PixcelShadaManager> _ps;
	std::shared_ptr<PipelineStateManager> _pipe;
	std::shared_ptr<VertexBufferManager> _vertexM;
	std::shared_ptr<ConstantManager> _cbuff;
	std::shared_ptr<TextureManager> _textureM;
	std::vector<VERTEX_CANVAS> _vertexs;
	VERTEX_CANVAS* _vaddress;
	CBUFF_CANVAS*_cbuffaddress;
	WORLDMAT_CANVAS _canvasmat;
	bool _usetextureF;//テクスチャ使用するかどうか true:使用する false:使用しない
};
