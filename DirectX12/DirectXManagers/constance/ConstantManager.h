#pragma once


#include <memory>
#include <wrl.h>

class ConstanceBufferCreate;
class ConstantBufferViewCreate;
class D3D12DeviceManager;
class ResoceMapUnmap;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
typedef unsigned __int64 UINT64;

class ConstantManager{
private:
	void CreateHeapDesc(std::shared_ptr<D3D12DeviceManager>& device, const int numdesccout);
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const size_t& cbufferlayoutstructsize);
	void CreateViewDesc(std::shared_ptr<D3D12DeviceManager>& device);
public:
	ConstantManager();
	~ConstantManager();
	/// <summary>
	/// 定数バッファを作成する　ついでにビューも作る
	/// </summary>
	/// <param name="device"></param>
	/// <param name="cbufferlayoutstructsize">　1定数バッファの大きさ </param>
	/// <param name="numdesccout"> ビューの数(ディスクリプタの数) </param>
	void CreateConstantBufferAndView(std::shared_ptr<D3D12DeviceManager>& device, const size_t& cbufferlayoutstructsize, const int numdesccout);
	/// <summary>
	///コンスタントバッファをマップする 
	/// </summary>
	/// <param name="address">  参照で渡す</param>
	void ConstantbufferMap(void* address);
	//コンスタントバッファをアンマップする
	void ConstantbufferUnMap();
	ID3D12DescriptorHeap*& GetDescHeap();
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> _cbuffer;
	ID3D12DescriptorHeap* _descHeap;//TODO: 共有して定数を使用するため、Comを使用すると消滅してしまう可能性がある
	std::shared_ptr<ResoceMapUnmap> _resocemapunmap;
	int _desc_count;
	UINT64 _agin;
};
