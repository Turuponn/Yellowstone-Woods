#pragma once



struct ID3D12Device;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;

class ComandCreate {
public:

	/// <summary>
	/// コマンドアロケータを作ります
	/// </summary>
	/// <param name="device"></param>
	/// <param name="newcommandAllocator">[out]</param>
	void CreateComandAllocator(ID3D12Device* device, ID3D12CommandAllocator** newcommandAllocator);
	/// <summary>
	/// コマンドリストを作ります
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comandallocator"></param>
	/// <param name="newcomandList">[out]</param>
	void CreateComandList(ID3D12Device* device, ID3D12CommandAllocator* comandallocator, ID3D12GraphicsCommandList** newcomandList);
	/// <summary>
	/// コマンドキューを作ります
	/// </summary>
	/// <param name="device"></param>
	/// <param name="newcomand_queue">[out]</param>
	void CreateCommandQueue(ID3D12Device* device, ID3D12CommandQueue** newcomand_queue);

	ComandCreate();
	virtual ~ComandCreate();
};

