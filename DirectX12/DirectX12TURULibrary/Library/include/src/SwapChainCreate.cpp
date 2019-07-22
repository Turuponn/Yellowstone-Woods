#include "SwapChainCreate.h"
#include <d3d12.h>
#include <dxgi1_4.h>//dxgi�p
#include "GameError.h"



SwapChainCreate::SwapChainCreate() {

}

SwapChainCreate::~SwapChainCreate() {

}

void SwapChainCreate::CreateSwapChain(const unsigned int screensize_x,const unsigned int screensize_y, IDXGIFactory4* dxgifac4, HWND& windowhwnd, ID3D12Device* device, ID3D12CommandQueue* comand_queue, IDXGISwapChain3** swap_chain) {
	//�X���b�v�`�F�C���쐬
	HRESULT result = E_FAIL;

	result = E_FAIL;
	DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
	swap_chain_desc.Width = screensize_x;
	swap_chain_desc.Height = screensize_y;
	swap_chain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.Stereo = false;
	swap_chain_desc.SampleDesc.Count = 1;//�A���`�G�C���A�V���O�p�@1�Ŏg��Ȃ�
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//Usage�g�p���@
	swap_chain_desc.BufferCount = 2;//�X�N���[���o�b�t�@��
	swap_chain_desc.Scaling = DXGI_SCALING_STRETCH;//��ʂ̏k�ڂ�������ꂽ��ǂ��Ή����邩
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_chain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;//�w�肵�Ȃ�
	swap_chain_desc.Flags = 0;//��]�łǂ�����邩�̐ݒ�
	result = dxgifac4->CreateSwapChainForHwnd(
		comand_queue,//�R�}���h�L���[������
		windowhwnd,
		&swap_chain_desc,
		nullptr,//�t���X�N���[��
		nullptr,
		(IDXGISwapChain1**)(swap_chain)
	);

	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("SwapChainCreate::CreateSwapChain result != S_OK")));
	}
}
