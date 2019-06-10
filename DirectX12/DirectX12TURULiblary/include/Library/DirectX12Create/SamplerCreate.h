#pragma once

struct D3D12_STATIC_SAMPLER_DESC;
enum D3D12_TEXTURE_ADDRESS_MODE;
enum D3D12_FILTER;
enum D3D12_COMPARISON_FUNC;

struct AddressingMode {
	D3D12_TEXTURE_ADDRESS_MODE addressU;
	D3D12_TEXTURE_ADDRESS_MODE addressV;
	D3D12_TEXTURE_ADDRESS_MODE addressW;
};

class SamplerCreate {
public:
	SamplerCreate();
	virtual ~SamplerCreate();
	/// <summary>
	/// サンプラを作成する
	/// </summary>
	/// <param name="registerslotnum"> ルートシグネチャに登録したサンプラのレジスタ番号</param>
	/// <returns>[out] サンプラデスクリプタを返す</returns>
	D3D12_STATIC_SAMPLER_DESC StaticSampTexture(const unsigned int registerslotnum);
	/// <summary>
	/// サンプラを作成
	/// </summary>
	/// <param name="registerslotnum"> ルートシグネチャに登録したサンプラのレジスタ番号 </param>
	/// <param name="mode">D3D12_TEXTURE_ADDRESS_MODE </param>
	/// <returns>サンプラデスクリプタを返す</returns>
	D3D12_STATIC_SAMPLER_DESC StaticSampTexture2(const unsigned int registerslotnum, AddressingMode& mode);
	/// <summary>
	/// フィルタリングする
	/// </summary>
	/// <param name="registerslotnum"></param>
	/// <param name="mode"></param>
	/// <param name="filltermode"> フィルターモードを入れる</param>
	/// <param name="maxmaxAnisotropy">最大異方性値</param>
	/// <returns></returns>
	D3D12_STATIC_SAMPLER_DESC StaticSampTextureFilltering(const unsigned int registerslotnum, AddressingMode& mode, D3D12_FILTER& filltermode, int maxmaxAnisotropy);
	D3D12_STATIC_SAMPLER_DESC StaticSampTextureFilltering(const unsigned int registerslotnum, AddressingMode& mode, D3D12_FILTER& filltermode, D3D12_COMPARISON_FUNC&  comparison, int maxmaxAnisotropy);

private:

};
