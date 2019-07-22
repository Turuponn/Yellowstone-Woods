#include "IndexBufferView.h"
#include <d3d12.h>
#include "GameError.h"




IndexBufferView::IndexBufferView() {

}
IndexBufferView::~IndexBufferView() {

}

void IndexBufferView::CreateIndexView(ID3D12Resource* indexbuffer, const UINT allindexsize, const size_t oneindexsize,const UINT vartexnum,D3D12_INDEX_BUFFER_VIEW** indexbufferview) {
	(*indexbufferview) = new D3D12_INDEX_BUFFER_VIEW();
	UINT limitvertex = 65535;
	auto format = DXGI_FORMAT_R32_UINT;
	if (limitvertex > vartexnum) {
		format = DXGI_FORMAT_R16_UINT;
	}
	else {
		format = DXGI_FORMAT_R32_UINT;
	}
	(*indexbufferview)->BufferLocation = indexbuffer->GetGPUVirtualAddress();
	(*indexbufferview)->Format = format;
	(*indexbufferview)->SizeInBytes = (UINT)(allindexsize * oneindexsize);//index size

}


void IndexBufferView::CreateIndexViewR16(ID3D12Resource* indexbuffer, const UINT allindexsize, const size_t oneindexsize, const UINT vartexnum, D3D12_INDEX_BUFFER_VIEW** indexbufferview) {
	(*indexbufferview) = new D3D12_INDEX_BUFFER_VIEW();
	auto format = DXGI_FORMAT_R16_UINT;
	(*indexbufferview)->BufferLocation = indexbuffer->GetGPUVirtualAddress();
	(*indexbufferview)->Format = format;
	(*indexbufferview)->SizeInBytes = (UINT)(allindexsize * oneindexsize);//index size

}
void IndexBufferView::CreateIndexViewR32(ID3D12Resource* indexbuffer, const UINT allindexsize, const size_t oneindexsize, const UINT vartexnum, D3D12_INDEX_BUFFER_VIEW** indexbufferview) {
	(*indexbufferview) = new D3D12_INDEX_BUFFER_VIEW();
	auto format = DXGI_FORMAT_R32_UINT;
	(*indexbufferview)->BufferLocation = indexbuffer->GetGPUVirtualAddress();
	(*indexbufferview)->Format = format;
	(*indexbufferview)->SizeInBytes = (UINT)(allindexsize * oneindexsize);//index size

}