#pragma once

#include <DirectXMath.h>
#include <memory>
#include <string>
#include <vector>
#include <wrl.h>

enum LOCKUPVECINDEX {
	CBM_TOP,
	CBM_BOTTOM,
	CBM_LEFT,
	CBM_RIGHT,
	CBM_FRONT,
	CBM_BACK,
	CBM_MAX,
};



struct Vector3;
struct Vector4;

class D3D12DeviceManager;
class TextureManager;
class ComandManager;
class FenceManager;
class RootSignatureManager;
class FBXManager;
class VertexShadaManager;
class PipelineStateManager;
class PixcelShadaManager;
class ConstantManager;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class DepthManager;
class WhiteTextureManager;


class CubeMapManager {
private:
public:
	CubeMapManager();
	virtual ~CubeMapManager();



	void LoadCubeMap(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		const std::string& texfilepath
	);

	void CreateFBXMesh(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		std::shared_ptr<FenceManager>& fence,
		const std::string& fbxfilepath
	);

	//拡縮: クウォータニオン
	void SetScaleQuaternion(const Vector3& scale);
	//座標: クウォータニオン
	void SetPostionQuaternion(const Vector3& pos);
	//回転: クウォータニオン
	void SetRotateQuaternion(const Vector3& axis, float angle);
	//回転: 現在軸と新しい軸の合成
	void SetRotateQuaternion_mul(const Vector3& newaxis, float angle);
	/// <summary>
	/// キューブマップの描画
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="rootsignature"></param>
	/// <param name="fence"></param>
	/// <param name="depth"></param>
	void PreUpdate(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<DepthManager>& depth,
		std::shared_ptr<WhiteTextureManager>& whitetex
	);



private:
	std::shared_ptr<TextureManager> _texM;
	std::shared_ptr<VertexShadaManager> _vsm;
	std::shared_ptr<PixcelShadaManager> _psm;
	std::shared_ptr<PipelineStateManager> _pipelineM;
	std::shared_ptr<ConstantManager> _constantm;
	std::shared_ptr<PipelineStateManager> _pipeline;
	std::shared_ptr<FBXManager> _fbx;
	

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _texdescheap;


};