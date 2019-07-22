#pragma once

#include <vector>



struct ID3D12Device;
struct ID3D12DescriptorHeap;
struct IDXGISwapChain3;
struct ID3D12Resource;
enum DXGI_FORMAT;
enum D3D12_RESOURCE_STATES;
struct D3D12_CPU_DESCRIPTOR_HANDLE;

class RenderTargetCreate {
public:
	RenderTargetCreate();
	virtual ~RenderTargetCreate();
	/// <summary>
	///  RT用バッファの作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="sizex">一応テクスチャなのでそのサイズ </param>
	/// <param name="sizey"></param>
	/// <param name="resocestate">リソースの最初の状態</param>
	/// <param name="format">型</param>
	/// <param name="pResource">[out]</param>
	void CreateRTBuffer(ID3D12Device* device, const int sizex, const int sizey, D3D12_RESOURCE_STATES resocestate, DXGI_FORMAT format, ID3D12Resource** pResource);
	/// <summary>
	/// レンダーターゲットを作成する ついでに登録する
	/// </summary>
	/// <param name="device"></param>
	/// <param name="descriptorHeap"></param>
	/// <param name="swapchain"></param>
	/// <returns>　保存用レンダーターゲットリソース　</returns>
	std::vector<ID3D12Resource*> CreateRenderTargetView(ID3D12Device* device, ID3D12DescriptorHeap* descriptorHeap, IDXGISwapChain3* swapchain);
	/// <summary>
	/// RTV用ディスクリプタヒープを返す
	/// </summary>
	/// <param name="device"></param>
	/// <param name="_rtvdescheap">[out]</param>
	void RTVCreateHeap(ID3D12Device* device, ID3D12DescriptorHeap** _rtvdescheap);
	/// <summary>
	/// RTビューを作成する
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rtvdescheap"></param>
	/// <param name="pResource">書き込み用バッファを指定する</param>
	/// <param name="format">書き込み用バッファの型</param>
	void CreateRTVView(ID3D12Device* device, ID3D12DescriptorHeap* rtvdescheap, ID3D12Resource *pResource, DXGI_FORMAT format);
	/// <summary>
	/// RTVHeap の作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="numdesc">ディスクリプタの数</param>
	/// <param name="_rtvdescheap">[out]</param>
	void RTVCreateHeaps(ID3D12Device* device, const int numdesc, ID3D12DescriptorHeap** _rtvdescheap);
	/// <summary>
	/// RTVViewの作成 : 複数numdesc用
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rtvdescheap"></param>
	/// <param name="pResource"></param>
	/// <param name="format"></param>
	void CreateRTVViews(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE& rtvdescheap, ID3D12Resource *pResource, DXGI_FORMAT format);
private:

};
