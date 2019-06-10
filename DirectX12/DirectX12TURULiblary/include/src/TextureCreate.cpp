#include "TextureCreate.h"
#include "GameError.h"
#include <d3d12.h>
#include <stdint.h>//uint32_t


TextureCreate::TextureCreate() {

}
TextureCreate::~TextureCreate() {

}
void TextureCreate::CreateBuffer(ID3D12Device* device, const int texwidth, const int texheight, ID3D12Resource** texturebuffer) {

	HRESULT result = E_FAIL;
	D3D12_HEAP_PROPERTIES heap_propatie = {};
	heap_propatie.Type = D3D12_HEAP_TYPE_CUSTOM;//カスタム
	heap_propatie.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;//書き込み、結合
	heap_propatie.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;//GPUかきこみ
	heap_propatie.CreationNodeMask = 1;
	heap_propatie.VisibleNodeMask = 1;
	

	D3D12_RESOURCE_DESC texResourceDesc = {};
	texResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;//2Dのテクスチャ
	texResourceDesc.Alignment = 0;//アライメント配置
	texResourceDesc.Width = texwidth;//テクスチャサイズ
	texResourceDesc.Height = texheight;//テクスチャサイズ
	texResourceDesc.DepthOrArraySize = 1;//配列のサイズを指定
	texResourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texResourceDesc.SampleDesc.Count = 1;//アンチエイリアシング用
	texResourceDesc.SampleDesc.Quality = 0;//最低品質
	texResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	texResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	


	result = device->CreateCommittedResource(
		&heap_propatie,
		D3D12_HEAP_FLAG_NONE,
		&texResourceDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,//リソースを書き込み専用にする
		nullptr,
		IID_PPV_ARGS(texturebuffer)
	);
	if (result != S_OK) {
		throw(1);
	}

}
void TextureCreate::TextureBufferSubresource(const int texwidth, const int texheight, char* imagedata_address, ID3D12Resource* texturebuffer) {




	//テクスチャバッファへの書き込み
	HRESULT result = E_FAIL;
	D3D12_BOX texbox = { 0 };//直方体の指定
	texbox.left = 0;
	texbox.top = 0;
	texbox.right = texwidth;
	texbox.bottom = texheight;
	texbox.front = 0;
	texbox.back = 1;


	result = texturebuffer->WriteToSubresource(
		0,
		&texbox,
		imagedata_address,
		sizeof(uint32_t)* texwidth,//sizeof(uint32_t)==4byte(32bit)==UINT(MSDN) RowPitch
		sizeof(uint32_t)*texwidth*texheight// SlicePitch
	);
	if (result != S_OK) {
		throw(1);
	}
}

void TextureCreate::TextureShadaResoceView(ID3D12Device* device, ID3D12Resource* texturebuffer, ID3D12DescriptorHeap* texdescheap, D3D12_CPU_DESCRIPTOR_HANDLE& cpuhandle, const DXGI_FORMAT& format) {
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;//ミップマップ
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//SRVの任意マッピング指定
	device->CreateShaderResourceView(texturebuffer, &srvDesc, cpuhandle);
}

void TextureCreate::CreateDescHeap(ID3D12Device* device, const UINT numdesc, ID3D12DescriptorHeap** texdescheap) {
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC texHeapDesc = {};
	texHeapDesc.NumDescriptors = numdesc;//ディスクリプタの数
	texHeapDesc.NodeMask = 0;
	texHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//コンピュートシェーダ用
	texHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//
	//シェーダリソースビュー作成
	result = device->CreateDescriptorHeap(&texHeapDesc, IID_PPV_ARGS(texdescheap));
	if (result != S_OK) {
		throw(1);
	}
}
void TextureCreate::TextureBufferSubresourceArry(const int texwidth, const int texheight, char* imagedata_address,const int descindex, ID3D12Resource* texturebuffer) {
	//テクスチャバッファへの書き込み
	HRESULT result = E_FAIL;
	D3D12_BOX texbox = { 0 };//直方体の指定
	texbox.left = 0;
	texbox.top = 0;
	texbox.right = texwidth;
	texbox.bottom = texheight;
	texbox.front = 0;
	texbox.back = 1;


	result = texturebuffer->WriteToSubresource(
		descindex,
		&texbox,
		imagedata_address,
		sizeof(uint32_t)* texwidth,//sizeof(uint32_t)==4byte(32bit)==UINT(MSDN) RowPitch
		sizeof(uint32_t)*texwidth*texheight//SlicePitch
	);
	if (result != S_OK) {
		throw(1);
	}
}