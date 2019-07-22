#pragma once



struct ID3D12Device;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;

class ComandCreate {
public:

	/// <summary>
	/// �R�}���h�A���P�[�^�����܂�
	/// </summary>
	/// <param name="device"></param>
	/// <param name="newcommandAllocator">[out]</param>
	void CreateComandAllocator(ID3D12Device* device, ID3D12CommandAllocator** newcommandAllocator);
	/// <summary>
	/// �R�}���h���X�g�����܂�
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comandallocator"></param>
	/// <param name="newcomandList">[out]</param>
	void CreateComandList(ID3D12Device* device, ID3D12CommandAllocator* comandallocator, ID3D12GraphicsCommandList** newcomandList);
	/// <summary>
	/// �R�}���h�L���[�����܂�
	/// </summary>
	/// <param name="device"></param>
	/// <param name="newcomand_queue">[out]</param>
	void CreateCommandQueue(ID3D12Device* device, ID3D12CommandQueue** newcomand_queue);

	ComandCreate();
	virtual ~ComandCreate();
};

