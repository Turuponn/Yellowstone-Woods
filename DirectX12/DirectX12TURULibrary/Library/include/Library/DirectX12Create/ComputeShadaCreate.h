#pragma once

struct ID3D12Device;
enum D3D12_RESOURCE_STATES;
struct ID3D12Resource;

class ComputeShadaCreate {
public:
	ComputeShadaCreate();
	virtual ~ComputeShadaCreate();
	/// <summary>
	/// UAV: バッファの作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="aligndescsize">アラインされたバッファ(256)のサイズ</param>
	/// <param name="r_startstate">リソース最初の状態</param>
	/// <param name="buffer">[out]作成されたバッファを返します</param>
	void CreateBuffer(ID3D12Device* device, const int aligndescsize, D3D12_RESOURCE_STATES r_startstate, ID3D12Resource** buffer);


private:

};