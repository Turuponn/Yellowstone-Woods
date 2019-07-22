#include "BMPTextureCreate.h"
#include <d3d12.h>
#include "GameError.h"
#include <stdint.h>//uint32_t



BMPTextureCreate::BMPTextureCreate() {

}
BMPTextureCreate::~BMPTextureCreate() {

}


void BMPTextureCreate::CreateTextureBuffer(ID3D12Device* device, const unsigned int texwidth, const unsigned int texheight, ID3D12Resource** newresourcebuffer) {
	HRESULT result = E_FAIL;

	D3D12_HEAP_PROPERTIES heap_propatie = {};
	heap_propatie.Type = D3D12_HEAP_TYPE_CUSTOM;
	heap_propatie.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;//書き込み、結合
	heap_propatie.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;//GPUかきこみ 
	heap_propatie.CreationNodeMask = 0;
	heap_propatie.VisibleNodeMask = 0;


	D3D12_RESOURCE_DESC texResourceDesc = {};
	texResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texResourceDesc.Alignment = 0;//アライメント配置
	texResourceDesc.Width = texwidth;//テクスチャサイズ
	texResourceDesc.Height = texheight;//テクスチャサイズ
	texResourceDesc.DepthOrArraySize = 1;//配列のサイズを指定 
	texResourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//32bitで送信
	texResourceDesc.SampleDesc.Count = 1;//アンチエイリアシング用
	texResourceDesc.SampleDesc.Quality = 0;//最低品質
	texResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	texResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	result = device->CreateCommittedResource(
		&heap_propatie,
		D3D12_HEAP_FLAG_NONE,
		&texResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(newresourcebuffer)
	);
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("TextureManager::CreateTextureBuffer() result != S_OK")));
	}
}

void BMPTextureCreate::TextureBufferSubresource(const int texwidth, const int texheight, char* imagedata_address, ID3D12Resource* texturebuffer) {
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
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("TextureManager::LoadTexture() result != S_OK")));
	}
}


void BMPTextureCreate::TextureShadaResoceView(ID3D12Device* device, ID3D12Resource* texturebuffer, ID3D12DescriptorHeap* texdescheap) {
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = {};
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//32bitのテクスチャ
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//このリソースは2Dテクスチャを使用する
	srvDesc.Texture2D.MipLevels = 1;//ミップマップ
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//SRVの任意マッピング指定
	srvHandle = texdescheap->GetCPUDescriptorHandleForHeapStart();


	device->CreateShaderResourceView(texturebuffer, &srvDesc, srvHandle);
}



void BMPTextureCreate::CreateDescHeap(ID3D12Device* device, const UINT rootsignaturenumdesc, ID3D12DescriptorHeap** texdescheap) {
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC texHeapDesc = {};
	texHeapDesc.NumDescriptors = rootsignaturenumdesc;//ディスクリプタの数
	texHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//コンピュートシェーダに使う用
	texHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	//シェーダリソースビュー作成
	result = device->CreateDescriptorHeap(&texHeapDesc, IID_PPV_ARGS(texdescheap));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T(" TextureManager::CreateDescHeap() result != S_OK")));
	}
}