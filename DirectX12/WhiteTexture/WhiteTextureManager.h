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

	/// ���e�N�X�`���̍쐬
	void CreateWhiteTexture(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand);

public:
	WhiteTextureManager();
	virtual ~WhiteTextureManager();


	
	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand);
	/// <summary>
	/// �e�N�X�`���̕`��
	/// </summary>
	/// <param name="comand"></param>
	/// <param name="texture_register">�^�����ɂ������e�N�X�`���̃��W�X�^�ԍ�</param>
	void TexregisterDraw(std::shared_ptr<ComandManager>& comand, TEXTURE_REGISTER texture_register);

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> _writetexbuff;//�z���C�g�e�N�X�`���p
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _writetexheap;//�z���C�g�e�N�X�`���p

	std::shared_ptr<TextureManager> _texm;
};

