#include "VertexBufferView.h"
#include <d3d12.h>
#include "GameError.h"


VertexBufferView::VertexBufferView() {

}
VertexBufferView::~VertexBufferView() {

}


void VertexBufferView::CreateVertexBufferView(ID3D12Resource* vertexbuffer, const UINT allvertexsize, const size_t onevertexsize, D3D12_VERTEX_BUFFER_VIEW** vertexbuffview) {
	*vertexbuffview = new D3D12_VERTEX_BUFFER_VIEW();

	//�o�[�e�b�N�X�o�b�t�@�r���[
	(*vertexbuffview)->BufferLocation = vertexbuffer->GetGPUVirtualAddress();//���z�A�h���X
	(*vertexbuffview)->SizeInBytes = allvertexsize;
	(*vertexbuffview)->StrideInBytes = (UINT)onevertexsize;//�X�g���C�h�F����


}