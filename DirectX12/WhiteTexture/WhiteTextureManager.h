#pragma once


#include <memory>
#include <wrl.h>//Microsoft::WRL
#include <vector>


struct ID3D12Resource;
struct ID3D12DescriptorHeap;
class D3D12DeviceManager;
class ComandManager;
class TextureManager;
enum TEXTURE_REGISTER;

class WhiteTextureManager {
private:

	/// 白テクスチャの作成
	void CreateWhiteTexture(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand);

public:
	WhiteTextureManager();
	virtual ~WhiteTextureManager();


	
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand);
	/// <summary>
	/// テクスチャの描画
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="texture_register">真っ白にしたいテクスチャのレジスタ番号</param>
	void TexregisterDraw(std::shared_ptr<ComandManager>& comand, TEXTURE_REGISTER texture_register);

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> _writetexbuff;//ホワイトテクスチャ用
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _writetexheap;//ホワイトテクスチャ用

	std::shared_ptr<TextureManager> _texm;
};

