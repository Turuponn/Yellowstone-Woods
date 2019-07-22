#include "SwapChainViewCreate.h"
#include <d3d12.h>
#include "GameError.h"

SwapChainViewCreate::SwapChainViewCreate() {

}
SwapChainViewCreate::~SwapChainViewCreate() {

}

void SwapChainViewCreate::CreateSwapChainViewDesc(ID3D12Device* device, const unsigned int swapchainscreencount, ID3D12DescriptorHeap** descriptorHeap) {
	//�f�B�X�N���v�^���쐬����
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC heap_descripta;
	heap_descripta.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[�Ƃ��Ďg��
	heap_descripta.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//�f�t�H���g�g��
	heap_descripta.NodeMask = 0;//������ʗp
	heap_descripta.NumDescriptors = swapchainscreencount;//���ɐݒ肵�Ă����ʂ̃o�b�t�@��
	result = device->CreateDescriptorHeap(&heap_descripta, IID_PPV_ARGS(descriptorHeap));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("SwapChainCreate::CreateSwapChain result != S_OK")));
	}
}