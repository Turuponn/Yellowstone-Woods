#pragma once



struct ID3D12GraphicsCommandList;
struct ID3D12Resource;
enum D3D12_RESOURCE_STATES;

class ResourceBarrier{
public:
	ResourceBarrier();
	virtual ~ResourceBarrier();
	/// <summary>
	/// リソースを使用目的に合わせてバリアする
	/// </summary>
	/// <param name="cmdgraphicslist"></param>
	/// <param name="resocenum">リソースの数　基本1</param>
	/// <param name="statebefore">現在のリソースの状態を指定する</param>
	/// <param name="stateafter">現在のリソースの状態が終わったあとどんな状態にするか指定する</param>
	/// <param name="targetbuffer"></param>
	void Barrier(
		ID3D12GraphicsCommandList* cmdgraphicslist,
		const int resocenum,
		D3D12_RESOURCE_STATES statebefore,
		D3D12_RESOURCE_STATES stateafter,
		ID3D12Resource* targetbuffer
	);
private:

};