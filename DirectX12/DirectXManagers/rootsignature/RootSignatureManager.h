#pragma once


#include <vector>
#include <memory>
#include <wrl.h>

class RootSignatureCreate;
struct D3D12_STATIC_SAMPLER_DESC;
struct D3D12_ROOT_PARAMETER;
struct D3D12_DESCRIPTOR_RANGE;
struct ID3D12RootSignature;
class D3D12DeviceManager;
class SamplerCreate;

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

class RootSignatureManager {
private:
	void InitRootParameters();
	void InitStaticRengeType();
	void InitSmpler();
public:
	RootSignatureManager();
	~RootSignatureManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device);
	std::vector<D3D12_DESCRIPTOR_RANGE>& GetRengeType();
	Microsoft::WRL::ComPtr<ID3D12RootSignature>& GetRootSignature();
private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> _rootSignature;//シリアライズ済みのルートシグネチャ
	Microsoft::WRL::ComPtr<ID3DBlob> _signatureblob;//シグネチャ
	
	std::vector<D3D12_STATIC_SAMPLER_DESC> _staticSamplers;//サンプラ入れ
	std::vector<D3D12_ROOT_PARAMETER> _numParameters;//ルートパラメータ入れ
	std::vector<D3D12_DESCRIPTOR_RANGE> _rangeType;//レンジタイプ入れ
};
