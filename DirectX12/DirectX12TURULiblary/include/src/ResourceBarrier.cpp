#include "ResourceBarrier.h"
#include <d3d12.h>
#include "GameError.h"



ResourceBarrier::ResourceBarrier() {
	
}
ResourceBarrier::~ResourceBarrier() {

}



void ResourceBarrier::Barrier(ID3D12GraphicsCommandList* cmdgraphicslist,const int resocenum,D3D12_RESOURCE_STATES statebefore,D3D12_RESOURCE_STATES stateafter,ID3D12Resource* targetbuffer) {
	
	// �o�b�N�o�b�t�@�̕`�抮����҂��߂̃o���A��ݒu
	D3D12_RESOURCE_BARRIER resource_barrier = {};

	resource_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                    // �o���A�̓��\�[�X�̏�ԑJ�ڂɑ΂��Đݒu->�J�ڃo���A
	resource_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	resource_barrier.Transition.pResource = targetbuffer;                               //�Ώۃ��\�[�X
	resource_barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES; //���ׂẴT�u���\�[�X�ɑΉ�
	resource_barrier.Transition.StateBefore = statebefore;                             //�J�ڑO�� : �O ���
	resource_barrier.Transition.StateAfter = stateafter;                               // �J�ڌ�� : �� ���

	//���\�[�X�o���A����уt�F���X�҂� 1�̓��\�[�X�̐�
	cmdgraphicslist->ResourceBarrier(resocenum, &resource_barrier);
}
