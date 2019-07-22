#pragma once


struct ID3D12Resource;
struct ID3D12DescriptorHeap;
struct ID3D12Device;
struct D3D12_CPU_DESCRIPTOR_HANDLE;
enum DXGI_FORMAT;
typedef unsigned int UINT;



class TextureCreate {
public:
	TextureCreate();
	virtual ~TextureCreate();
	/// <summary>
	/// �e�N�X�`���p�o�b�t�@�̍쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="texwidth"></param>
	/// <param name="texheight"></param>
	/// <param name="format"></param>
	/// <param name="texturebuffer"></param>
	void CreateBuffer(ID3D12Device* device, const int texwidth, const int texheight, DXGI_FORMAT format, ID3D12Resource** texturebuffer);
	/// <summary>
	/// �T�u���\�[�X������ : �e�N�X�`���o�b�t�@�Ƀf�[�^����������
	/// </summary>
	/// <param name="texwidth">�C���[�W�T�C�Y</param>
	/// <param name="texheight"></param>
	/// <param name="imagedata_address">(char*)�f�[�^�@�Ƃ��ē����</param>
	/// <param name="texturebuffer"></param>
	void TextureBufferSubresource(const int texwidth, const int texheight, char* imagedata_address, ID3D12Resource* texturebuffer);
	/// <summary>
	/// �e�N�X�`���p�V�F�[�_���\�[�X�r���[�̍쐬 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="texturebuffer"></param>
	/// <param name="texdescheap">�f�B�X�N���v�^�q�[�v�̏ꏊ</param>
	/// <param name="cpuhandle"></param>
	/// <param name="format"></param>
	void TextureShadaResoceView(ID3D12Device* device, ID3D12Resource* texturebuffer, ID3D12DescriptorHeap* texdescheap, D3D12_CPU_DESCRIPTOR_HANDLE& cpuhandle,const DXGI_FORMAT& format);
	/// <summary>
	/// �f�[�^���o�b�t�@�փR�s�[����
	/// </summary>
	/// <param name="texwidth"></param>
	/// <param name="texheight"></param>
	/// <param name="imagedata_address"></param>
	/// <param name="descindex"> �f�X�N���v�^�[�p�C���f�b�N�X</param>
	/// <param name="texturebuffer"></param>
	void TextureBufferSubresourceArry(
		const int texwidth,
		const int texheight,
		char* imagedata_address,
		const int descindex,
		ID3D12Resource* texturebuffer
	);
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�̍쐬 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="numdesc">���[�g�V�O�l�`���͈̔͂̃f�B�X�N���v�^��,�܂��͕K�v�ȃf�B�X�N���v�^������</param>
	/// <param name="texdescheap">[out]�e�N�X�`���p�f�B�X�N���v�^�q�[�v��Ԃ�</param>
	void CreateDescHeap(ID3D12Device* device, const UINT numdesc, ID3D12DescriptorHeap** texdescheap);

private:
};
