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
	heap_propatie.Type = D3D12_HEAP_TYPE_CUSTOM;//�J�X�^��
	heap_propatie.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;//�������݁A����
	heap_propatie.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;//GPU��������
	heap_propatie.CreationNodeMask = 1;
	heap_propatie.VisibleNodeMask = 1;
	

	D3D12_RESOURCE_DESC texResourceDesc = {};
	texResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;//2D�̃e�N�X�`��
	texResourceDesc.Alignment = 0;//�A���C�����g�z�u
	texResourceDesc.Width = texwidth;//�e�N�X�`���T�C�Y
	texResourceDesc.Height = texheight;//�e�N�X�`���T�C�Y
	texResourceDesc.DepthOrArraySize = 1;//�z��̃T�C�Y���w��
	texResourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texResourceDesc.SampleDesc.Count = 1;//�A���`�G�C���A�V���O�p
	texResourceDesc.SampleDesc.Quality = 0;//�Œ�i��
	texResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	texResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	


	result = device->CreateCommittedResource(
		&heap_propatie,
		D3D12_HEAP_FLAG_NONE,
		&texResourceDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,//���\�[�X���������ݐ�p�ɂ���
		nullptr,
		IID_PPV_ARGS(texturebuffer)
	);
	if (result != S_OK) {
		throw(1);
	}

}
void TextureCreate::TextureBufferSubresource(const int texwidth, const int texheight, char* imagedata_address, ID3D12Resource* texturebuffer) {




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
		throw(1);
	}
}

void TextureCreate::TextureShadaResoceView(ID3D12Device* device, ID3D12Resource* texturebuffer, ID3D12DescriptorHeap* texdescheap, D3D12_CPU_DESCRIPTOR_HANDLE& cpuhandle, const DXGI_FORMAT& format) {
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;//�~�b�v�}�b�v
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//SRV�̔C�Ӄ}�b�s���O�w��
	device->CreateShaderResourceView(texturebuffer, &srvDesc, cpuhandle);
}

void TextureCreate::CreateDescHeap(ID3D12Device* device, const UINT numdesc, ID3D12DescriptorHeap** texdescheap) {
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC texHeapDesc = {};
	texHeapDesc.NumDescriptors = numdesc;//�f�B�X�N���v�^�̐�
	texHeapDesc.NodeMask = 0;
	texHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//�R���s���[�g�V�F�[�_�p
	texHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//
	//�V�F�[�_���\�[�X�r���[�쐬
	result = device->CreateDescriptorHeap(&texHeapDesc, IID_PPV_ARGS(texdescheap));
	if (result != S_OK) {
		throw(1);
	}
}
void TextureCreate::TextureBufferSubresourceArry(const int texwidth, const int texheight, char* imagedata_address,const int descindex, ID3D12Resource* texturebuffer) {
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