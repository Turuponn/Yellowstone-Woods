#pragma once

#include <memory>
#include <vector>
#include <wrl.h>

enum D3D_PRIMITIVE_TOPOLOGY;
enum D3D12_RESOURCE_STATES;

struct ID3D12DescriptorHeap;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;
struct D3D12_VIEWPORT;
struct CD3DX12_CPU_DESCRIPTOR_HANDLE;
struct ID3D12Resource;
struct tagRECT;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;


class VertexBufferManager;
class IndexBufferManager;
class ConstantManager;
class TextureManager;
class SwapChainManager;
class DepthManager;
class ResourceBarrier;
class D3D12DeviceManager;
class ComandCreate;
class FenceManager;
class PipelineStateManager;
class RootSignatureManager;

class ComandManager{
private:
	void Initialize();
public:
	ComandManager();
	~ComandManager();
	/// <summary>
	/// �R�}���h�L���[���쐬���܂�
	/// </summary>
	/// <param name="device"></param>
	void CreateComandQueue(std::shared_ptr<D3D12DeviceManager>& device);
	/// <summary>
	/// �R�}���h���X�g���쐬���܂�
	/// </summary>
	/// <param name="device"></param>
	void CreateComandList(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain);
	/// <summary>
	/// �R�}���h�A���P�[�^���t���[���o�b�t�@�������쐬���܂�
	/// </summary>
	/// <param name="device"></param>
	/// <param name="swapchain"></param>
	void CreateComandAllocators(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain);
	// �o�b�N�o�b�t�@�`�抮���܂Ń|�[�����O�őҋ@����
	void ComandListWaitPorlling(std::shared_ptr<FenceManager>& fence);
	//�R�}���h�����ׂĕ���
	void ComandClose();
	//�q�[�v�ɗ��܂��Ă���R�}���h�����ׂă��Z�b�g����
	void ComandReset(std::shared_ptr<SwapChainManager>& swapchain);
	//�p�C�v���C�����Z�b�g����
	void SetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate);
	//�p�C�v���C�������Z�b�g����
	void ReSetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate, std::shared_ptr<SwapChainManager>& swapchain);
	//���ׂẴp�C�v���C�������Z�b�g
	void ReSetPipeline(std::shared_ptr<SwapChainManager>& swapchain);
	//���[�g�V�O�l�`�����A�^�b�`����
	void RootSignatureAttach(std::shared_ptr<RootSignatureManager>& rootsignature);
	//�r���[�|�[�g�̎w��
	void ComandRSSetViewPorts(const int viewportnum, D3D12_VIEWPORT& viewport);
	//�V�U�[��`(������͈͂̎w��
	void ComandRSSetScissorRects(const int scissorrectnum, tagRECT& scissorRect);
	//�`��Ώۂ̎w��
	void ComandOMSetRenderTargets(const int numrtv, ID3D12DescriptorHeap*& descheap, std::shared_ptr<DepthManager>& depth);
	//�[�x�����N���A
	void ComandClearDepthStencilView(std::shared_ptr<DepthManager>& depth);
	//�`��Ώۂ̐F�ݒ�
	void ComandClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE& rtv, float* clearcolor);
	//���\�[�X�̏�Ԃ�ݒ肷��
	void ComandRBarrier(D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource*& tergetresoce);
	/// <summary>
	/// ���\�[�X�̏�Ԃ�ݒ肷�� : �z���
	/// </summary>
	/// <param name="resocenum"> ���̃o�b�t�@�S�̂̃��\�[�X��</param>
	/// <param name="statebefore"></param>
	/// <param name="stateafter"></param>
	/// <param name="tergetresoce"></param>
	void ComandRBarrierArry(const int resocenum,D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource*& tergetresoce);
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
	void ComandSetDescriptorHeaps(const int descheapnum, ID3D12DescriptorHeap*&  heap);
	//���[�g�V�O�l�`���̃X���b�g�ƒ萔�𓯊�������
	void ComandSetGraphicsRootDescriptorTable(const int rootparamidx, ID3D12DescriptorHeap*& heap);
	//�R�}���h���X�g�ɂ��߂Ă������R�}���h�����ׂĎ��s������
	void ComandExecuteCommandList();

	//�L���[��Ԃ�
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>& GetComandQueue();
	//�A���P�[�^��Ԃ�
	std::vector< Microsoft::WRL::ComPtr<ID3D12CommandAllocator>>& GetComandAllocators();
	//���X�g��Ԃ�
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList>& GetGraphicsCommandList();
private:
	std::shared_ptr<ComandCreate> _comandcreate;
	std::shared_ptr<ResourceBarrier> _rb;
	std::vector< Microsoft::WRL::ComPtr<ID3D12CommandAllocator>> _comandAllocators;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> _comandQueue;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> _comandList;
};
