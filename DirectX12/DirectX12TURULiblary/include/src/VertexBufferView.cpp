#include "VertexBufferView.h"
#include <d3d12.h>
#include "GameError.h"


VertexBufferView::VertexBufferView() {

}
VertexBufferView::~VertexBufferView() {

}


void VertexBufferView::CreateVertexBufferView(ID3D12Resource* vertexbuffer, const UINT allvertexsize, const size_t onevertexsize, D3D12_VERTEX_BUFFER_VIEW** vertexbuffview) {
	*vertexbuffview = new D3D12_VERTEX_BUFFER_VIEW();

	//バーテックスバッファビュー
	(*vertexbuffview)->BufferLocation = vertexbuffer->GetGPUVirtualAddress();//仮想アドレス
	(*vertexbuffview)->SizeInBytes = allvertexsize;
	(*vertexbuffview)->StrideInBytes = (UINT)onevertexsize;//ストライド：歩幅


}