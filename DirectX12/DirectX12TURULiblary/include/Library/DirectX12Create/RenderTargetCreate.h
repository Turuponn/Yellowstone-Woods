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
	///  RT�p�o�b�t�@�̍쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="sizex">�ꉞ�e�N�X�`���Ȃ̂ł��̃T�C�Y </param>
	/// <param name="sizey"></param>
	/// <param name="resocestate">���\�[�X�̍ŏ��̏��</param>
	/// <param name="format">�^</param>
	/// <param name="pResource">[out]</param>
	void CreateRTBuffer(ID3D12Device* device, const int sizex, const int sizey, D3D12_RESOURCE_STATES resocestate, DXGI_FORMAT format, ID3D12Resource** pResource);
	/// <summary>
	/// �����_�[�^�[�Q�b�g���쐬���� ���łɓo�^����
	/// </summary>
	/// <param name="device"></param>
	/// <param name="descriptorHeap"></param>
	/// <param name="swapchain"></param>
	/// <returns>�@�ۑ��p�����_�[�^�[�Q�b�g���\�[�X�@</returns>
	std::vector<ID3D12Resource*> CreateRenderTargetView(ID3D12Device* device, ID3D12DescriptorHeap* descriptorHeap, IDXGISwapChain3* swapchain);
	/// <summary>
	/// RTV�p�f�B�X�N���v�^�q�[�v��Ԃ�
	/// </summary>
	/// <param name="device"></param>
	/// <param name="_rtvdescheap">[out]</param>
	void RTVCreateHeap(ID3D12Device* device, ID3D12DescriptorHeap** _rtvdescheap);
	/// <summary>
	/// RT�r���[���쐬����
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rtvdescheap"></param>
	/// <param name="pResource">�������ݗp�o�b�t�@���w�肷��</param>
	/// <param name="format">�������ݗp�o�b�t�@�̌^</param>
	void CreateRTVView(ID3D12Device* device, ID3D12DescriptorHeap* rtvdescheap, ID3D12Resource *pResource, DXGI_FORMAT format);
	/// <summary>
	/// RTVHeap �̍쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="numdesc">�f�B�X�N���v�^�̐�</param>
	/// <param name="_rtvdescheap">[out]</param>
	void RTVCreateHeaps(ID3D12Device* device, const int numdesc, ID3D12DescriptorHeap** _rtvdescheap);
	/// <summary>
	/// RTVView�̍쐬 : ����numdesc�p
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rtvdescheap"></param>
	/// <param name="pResource"></param>
	/// <param name="format"></param>
	void CreateRTVViews(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE& rtvdescheap, ID3D12Resource *pResource, DXGI_FORMAT format);
private:

};
