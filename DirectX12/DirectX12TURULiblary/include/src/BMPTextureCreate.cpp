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
	heap_propatie.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;//�������݁A����
	heap_propatie.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;//GPU�������� 
	heap_propatie.CreationNodeMask = 0;
	heap_propatie.VisibleNodeMask = 0;


	D3D12_RESOURCE_DESC texResourceDesc = {};
	texResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texResourceDesc.Alignment = 0;//�A���C�����g�z�u
	texResourceDesc.Width = texwidth;//�e�N�X�`���T�C�Y
	texResourceDesc.Height = texheight;//�e�N�X�`���T�C�Y
	texResourceDesc.DepthOrArraySize = 1;//�z��̃T�C�Y���w�� 
	texResourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//32bit�ő��M
	texResourceDesc.SampleDesc.Count = 1;//�A���`�G�C���A�V���O�p
	texResourceDesc.SampleDesc.Quality = 0;//�Œ�i��
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
	//�e�N�X�`���o�b�t�@�ւ̏�������
	HRESULT result = E_FAIL;
	D3D12_BOX texbox = { 0 };//�����̂̎w��
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
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//32bit�̃e�N�X�`��
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//���̃��\�[�X��2D�e�N�X�`�����g�p����
	srvDesc.Texture2D.MipLevels = 1;//�~�b�v�}�b�v
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//SRV�̔C�Ӄ}�b�s���O�w��
	srvHandle = texdescheap->GetCPUDescriptorHandleForHeapStart();


	device->CreateShaderResourceView(texturebuffer, &srvDesc, srvHandle);
}



void BMPTextureCreate::CreateDescHeap(ID3D12Device* device, const UINT rootsignaturenumdesc, ID3D12DescriptorHeap** texdescheap) {
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC texHeapDesc = {};
	texHeapDesc.NumDescriptors = rootsignaturenumdesc;//�f�B�X�N���v�^�̐�
	texHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//�R���s���[�g�V�F�[�_�Ɏg���p
	texHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	//�V�F�[�_���\�[�X�r���[�쐬
	result = device->CreateDescriptorHeap(&texHeapDesc, IID_PPV_ARGS(texdescheap));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T(" TextureManager::CreateDescHeap() result != S_OK")));
	}
}