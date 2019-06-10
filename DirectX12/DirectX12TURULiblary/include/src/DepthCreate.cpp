#include "DepthCreate.h"
#include <d3d12.h>
#include "GameError.h"


DepthCreate::DepthCreate() {

}
DepthCreate::~DepthCreate() {

}

void DepthCreate::CreateDepthBuffer(ID3D12Device* device,const unsigned int screensize_x, const unsigned int screensize_y,ID3D12Resource** depthbuffer) {
	HRESULT result = E_FAIL;

	//�[�x�o�b�t�@�̍쐬												
	D3D12_CLEAR_VALUE _depthClearValue = {};
	_depthClearValue.DepthStencil.Depth = 1.0f;//�[���ő�l�͂P
	_depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	//�e�N�X�`���Ƃ��Ďg��
	D3D12_HEAP_PROPERTIES depthHeapProp = {};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;//�f�t�H���g
	depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	//�[�x�o�b�t�@���\�[�X
	D3D12_RESOURCE_DESC depthResourceDesc = {};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;//�e�N�X�`���炵��
	depthResourceDesc.Width = screensize_x;//��ʕ�
	depthResourceDesc.Height = screensize_y;//��ʍ���
	depthResourceDesc.DepthOrArraySize = 1;//�z��̃T�C�Y
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthResourceDesc.SampleDesc.Count = 1;//�A���`�G�C���A�V���O�p
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;



	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE, //�f�v�X�������݂Ɏg���܂�
		&_depthClearValue,
		IID_PPV_ARGS(depthbuffer)
	);
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("DepthCreate::CreateBuffer() result != S_OK")));
	}
}
void DepthCreate::CreateDepthBufferView(ID3D12Device* device, ID3D12Resource* depthbuffer, ID3D12DescriptorHeap* depthheapedesc) {
	D3D12_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};
	//�[�x�o�b�t�@�̃r���[�ݒ�
	//�r���[�𗘗p����Ƃ��̑�����̃C���[�W
	depthViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Flags = D3D12_DSV_FLAG_NONE;
	device->CreateDepthStencilView(depthbuffer, &depthViewDesc, depthheapedesc->GetCPUDescriptorHandleForHeapStart());
}
void DepthCreate::CreateDepthDescHeap(ID3D12Device* device, ID3D12DescriptorHeap** depthheapedesc) {
	//�f�B�X�N���v�^�[
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC _dsvHeapDesc = {};
	_dsvHeapDesc.NumDescriptors = 1;
	_dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//DSV�Ő[�x�Ƃ��ċ�ʂ�����

	result = device->CreateDescriptorHeap(&_dsvHeapDesc, IID_PPV_ARGS(depthheapedesc));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("DepthCreate::CreateDepthDescHeap() result != S_OK")));
	}
}