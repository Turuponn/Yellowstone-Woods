#include "ConstantBufferViewCreate.h"
#include <d3d12.h>
#include "GameError.h"
#include <vector>

ConstantBufferViewCreate::ConstantBufferViewCreate() {

}
ConstantBufferViewCreate::~ConstantBufferViewCreate() {

}

void ConstantBufferViewCreate::CreateConstantBufferView(ID3D12Device* device, const int descriptorcount,const UINT64 align, ID3D12Resource* constantbuffer, ID3D12DescriptorHeap* constantdescheap) {

	std::vector<D3D12_CONSTANT_BUFFER_VIEW_DESC> descs;
	auto heapsize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);//�R���X�^���g�o�b�t�@�[�p�A1�T�C�Y
	descs.resize(descriptorcount);
	//�R���X�^���g�o�b�t�@�[�r���[���w�萔�쐬����
	auto heapstart = constantdescheap->GetCPUDescriptorHandleForHeapStart();
	auto bufflocation = constantbuffer->GetGPUVirtualAddress();
	for (int idx = 0; idx < descriptorcount; idx++) {
		descs[idx].BufferLocation = bufflocation;//����Descriptor���������\�[�X��u���Ă���ʒu
		bufflocation += align;
		descs[idx].SizeInBytes = (UINT)align;//1�萔�o�b�t�@�̃T�C�Y
		device->CreateConstantBufferView(&descs[idx], heapstart);
		heapstart.ptr += heapsize;//1�q�[�v�����炷
	}
}