#pragma once

#include <memory>
#include <wrl.h>

class D3D12DeviceManager;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;
class ComandCreate;
class FenceManager;
class PipelineStateManager;
class RootSignatureManager;
struct D3D12_VIEWPORT;

struct CD3DX12_CPU_DESCRIPTOR_HANDLE;
class DepthManager;
class ResourceBarrier;
enum D3D12_RESOURCE_STATES;
struct ID3D12Resource;

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

struct tagRECT;

class VertexBufferManager;
class IndexBufferManager;
class ConstantManager;
class TextureManager;
enum D3D_PRIMITIVE_TOPOLOGY;

struct ID3D12DescriptorHeap;

class ComandManager{
protected:
	
public:
	ComandManager();
	virtual ~ComandManager();
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device);
	// �o�b�N�o�b�t�@�`�抮���܂Ń|�[�����O�őҋ@����
	void ComandListWaitPorlling(std::shared_ptr<FenceManager>& fence);
	//�R�}���h�����ׂĕ���
	void ComandClose();
	//�q�[�v�ɗ��܂��Ă���R�}���h�����ׂă��Z�b�g����
	void ComandReset();
	//�p�C�v���C�����Z�b�g����
	void SetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate);
	//�p�C�v���C�������Z�b�g����
	void ReSetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate);
	//���ׂẴp�C�v���C�������Z�b�g
	void ReSetPipeline();
	//���[�g�V�O�l�`�����A�^�b�`����
	void RootSignatureAttach(std::shared_ptr<RootSignatureManager>& rootsignature);
	//�r���[�|�[�g�̎w��
	void ComandRSSetViewPorts(const int viewportnum, D3D12_VIEWPORT& viewport);
	//�V�U�[��`(������͈͂̎w��
	void ComandRSSetScissorRects(const int scissorrectnum, tagRECT& scissorRect);
	//�`��Ώۂ̎w��
	void ComandOMSetRenderTargets(const int numrtv, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descheap, std::shared_ptr<DepthManager>& depth);
	//�[�x�����N���A
	void ComandClearDepthStencilView(std::shared_ptr<DepthManager>& depth);
	//�`��Ώۂ̐F�ݒ�
	void ComandClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE& rtv, float* clearcolor);
	//���\�[�X�̏�Ԃ�ݒ肷��
	void ComandRBarrier(D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource* tergetresoce);
	/// <summary>
	/// ���\�[�X�̏�Ԃ�ݒ肷�� : �z���
	/// </summary>
	/// <param name="resocenum"> ���̃o�b�t�@�S�̂̃��\�[�X��</param>
	/// <param name="statebefore"></param>
	/// <param name="stateafter"></param>
	/// <param name="tergetresoce"></param>
	void ComandRBarrierArry(const int resocenum,D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource* tergetresoce);
	//
	void ComandIASetVertexBuffers(std::shared_ptr<VertexBufferManager>& vbm);
	//�g�|���W
	void ComandIASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);
	//
	void ComandIASetIndexBuffer(std::shared_ptr<IndexBufferManager>& indexm);
	//�C���f�b�N�X�Â����ꂽ�`��
	void ComandDrawIndexedInstanced(const int instancenum, const int fecenum);
	// �C���f�b�N�X�Â�����Ă��Ȃ��`��
	void ComandDrawInstanced(const int vertexnum, const int instancenum);
	//�q�[�v�̐ݒ�
	void ComandSetDescriptorHeaps(const int descheapnum, ID3D12DescriptorHeap*  heap);
	//���[�g�V�O�l�`���̃X���b�g�ƒ萔�𓯊�������
	void ComandSetGraphicsRootDescriptorTable(const int rootparamidx, ID3D12DescriptorHeap* heap);
	//�R�}���h���X�g�ɂ��߂Ă������R�}���h�����ׂĎ��s������
	void ComandExecuteCommandList();

	//�L���[��Ԃ�
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>& GetComandQueue();
	//�A���P�[�^��Ԃ�
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>& GetComandAllocator();
	//���X�g��Ԃ�
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& GetGraphicsCommandList();
private:
	std::shared_ptr<ComandCreate> _comandcreate;
	std::shared_ptr<ResourceBarrier> _rb;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _comandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _comandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> _comand_queue;
};