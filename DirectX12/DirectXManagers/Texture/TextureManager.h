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
	/// WICをつかったテクスチャロード
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="fence"></param>
	/// <param name="filepath"></param>
	void WICLoadTexture(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		const std::string& filepath
	);
	void WICLoadTextureBinary(std::shared_ptr<D3D12DeviceManager>& device);
	void LoadTGATexture(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignaturemanager,
		const std::string& filepath
	);
	/// <summary>
	/// DDSTexのロード : キューブマップ用にロード
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="fence"></param>
	/// <param name="texfilepath"></param>
	void LoadDDSTexture(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence,const std::string& texfilepath);
	/// <summary>
	/// テクスチャ用ヒープの作成
	/// </summary>
	void SRVCreateHeap(std::shared_ptr<D3D12DeviceManager>& device);
	void SRVCreateHeap(std::shared_ptr<D3D12DeviceManager>& device,const int descnum);
	/// <summary>
	/// SRV用ビューの作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="srvtexformat"> Texture型と合わせる</param>
	/// <param name="buff"> バッファを入れる</param>
	void SRVCreateView(std::shared_ptr<D3D12DeviceManager>& device, DXGI_FORMAT srvtexformat, Microsoft::WRL::ComPtr<ID3D12Resource>& buff);
	void SRVCreateView(std::shared_ptr<D3D12DeviceManager>& device, DXGI_FORMAT srvtexformat);
	/// <summary>
	/// バッファ作成
	/// </summary>
	void SRVBuffer(std::shared_ptr<D3D12DeviceManager>& device, void* pdata, const int size_x, const int size_y);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="descnum"></param>
	/// <param name="texture_register"></param>
	void DrawImage(std::shared_ptr<ComandManager>& comand, const int descnum, TEXTURE_REGISTER texture_register);

	void DrawSrv(std::shared_ptr<ComandManager>& comand);

	



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

