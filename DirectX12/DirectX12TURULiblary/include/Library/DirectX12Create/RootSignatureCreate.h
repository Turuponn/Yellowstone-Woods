#pragma once

#include <vector>
struct ID3D12Device;
struct D3D12_ROOT_PARAMETER;
struct D3D12_STATIC_SAMPLER_DESC;
struct ID3D12RootSignature;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

class RootSignatureCreate {
public:
	RootSignatureCreate();
	virtual ~RootSignatureCreate();
	/// <summary>
	/// ルートシグネチャ作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="signature">シリアライズ化したシグネチャを入れる</param>
	/// <param name="rootsignature">[out]　ルートシグネチャを返す</param>
	void CreateRootSigneture(ID3D12Device* device, ID3DBlob* signature, ID3D12RootSignature** rootsignature);
	/// <summary>
	/// ルートシグネチャをシリアライズ化する
	/// </summary>
	/// <param name="staticsamplers">サンプラ</param>
	/// <param name="numparameters">ルートパラメータ</param>
	/// <param name="signature">[out]シリアライズ化したシグネチャを返す</param>
	void SilializeRootsignature(const  std::vector<D3D12_STATIC_SAMPLER_DESC>& staticsamplers, std::vector<D3D12_ROOT_PARAMETER>& numparameters, ID3DBlob** signature);
private:
	ID3DBlob* _errorblob;//エラー用
};
