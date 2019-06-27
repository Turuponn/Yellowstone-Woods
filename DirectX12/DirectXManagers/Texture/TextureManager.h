#pragma once


#include <wrl.h>
#include <string>
#include <memory>
#include <stdint.h>
#include <vector>



class ComandManager;
class FenceManager;
struct ID3D12Resource;
class D3D12DeviceManager;
struct ID3D12DescriptorHeap;
class ResourceBarrier;
class WICTexTextureCreate;
class TextureCreate;
class RootSignatureManager;
enum TEXTURE_REGISTER;
enum DXGI_FORMAT;
struct D3D12_SUBRESOURCE_DATA;
enum D3D12_RESOURCE_FLAGS;

struct TextureMemory {
	Microsoft::WRL::ComPtr<ID3D12Resource> Resource;
	std::unique_ptr<uint8_t[]> ddsData;
	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
};


class TextureManager {
private:
	


public:
	TextureManager();
	virtual ~TextureManager();

	/// <summary>
	/// WIC���������e�N�X�`�����[�h
	/// </summary>
	void WICLoadTexture(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		const std::string& filepath
	);
	void LoadTGATexture(
		std::shared_ptr<D3D12DeviceManager>& device,
		const std::string& filepath
	);
	/// <summary>
	/// DDSTex�̃��[�h : �L���[�u�}�b�v�p�Ƀ��[�h
	/// </summary>
	void LoadDDSTexture(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		const std::string& texfilepath
	);
	/// <summary>
	/// �e�N�X�`���p�q�[�v�̍쐬
	/// </summary>
	void SRVCreateHeap(std::shared_ptr<D3D12DeviceManager>& device);
	void SRVCreateHeap(
		std::shared_ptr<D3D12DeviceManager>& device,
		const int descnum);
	/// <summary>
	/// SRV�p�r���[�̍쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="srvtexformat"> Texture�^�ƍ��킹��</param>
	/// <param name="buff"> �o�b�t�@������</param>
	void SRVCreateView(
		std::shared_ptr<D3D12DeviceManager>& device,
		DXGI_FORMAT srvtexformat,
		Microsoft::WRL::ComPtr<ID3D12Resource>& buff
	);
	void SRVCreateView(
		std::shared_ptr<D3D12DeviceManager>& device,
		DXGI_FORMAT srvtexformat
	);
	/// <summary>
	/// �o�b�t�@�쐬
	/// </summary>
	void SRVBuffer(
		std::shared_ptr<D3D12DeviceManager>& device,
		void* pdata,
		const int size_x, 
		const int size_y
	);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="descnum"></param>
	/// <param name="texture_register"></param>
	void DrawImage(
		std::shared_ptr<ComandManager>& comand,
		const int descnum,
		TEXTURE_REGISTER texture_register
	);
	/// <summary>
	/// imgui�� �ʂɕ\���������ꍇ�p
	/// </summary>
	/// <param name="comand"></param>
	void DrawSrv(std::shared_ptr<ComandManager>& comand);

	


	//TODO:�@���ȎQ��
	ID3D12DescriptorHeap* GetSrvHeap();
	const std::string& GetTextureName();
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> _texturebuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> _texuploadheap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _texdescheap;



	std::shared_ptr<ResourceBarrier> _resocebarrier;

	std::string _texpath;

	
	//CubeMap
	Microsoft::WRL::ComPtr<ID3D12Resource> textureUploadHeap;
};

