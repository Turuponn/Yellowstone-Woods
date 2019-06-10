#include "FenceCreate.h"
#include <d3d12.h>
#include "../GameError.h"
FenceCreate::FenceCreate() {

}
FenceCreate::~FenceCreate() {

}


void FenceCreate::CreateFance(ID3D12Device* device, UINT64 initializefenceValue, ID3D12Fence** fence) {

	HRESULT result = E_FAIL;

	//��{�I�ɂ͓���Value���g�p���܂��A�}���`�X���b�h�̃~���[�e�b�N�X�̂悤��
	//�r������Ɏg�p����@�Ǝv���܂��B
	result = device->CreateFence(initializefenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("FenceCreate::CreateFance() result != S_OK")));
	}
}