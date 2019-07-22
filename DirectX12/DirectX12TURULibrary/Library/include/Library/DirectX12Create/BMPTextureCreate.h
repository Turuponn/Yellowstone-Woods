#pragma once



struct ID3D12Resource;
struct ID3D12Device;
struct ID3D12DescriptorHeap;
typedef unsigned int UINT;

class BMPTextureCreate {
public:
	BMPTextureCreate();
	virtual ~BMPTextureCreate();

	
	/// <summary>
	/// テクスチャバッファ作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="texwidth"></param>
	/// <param name="texheight"></param>
	/// <param name="newresourcebuffer">[out]</param>
	void CreateTextureBuffer(ID3D12Device* device, const unsigned int texwidth, const unsigned int texheight, ID3D12Resource** newresourcebuffer);
	/// <summary>
	/// テクスチャバッファをサブリソース化
	/// </summary>
	/// <param name="texwidth"></param>
	/// <param name="texheight"></param>
	/// <param name="imagedata_address"></param>
	/// <param name="texturebuffer"></param>
	void TextureBufferSubresource(const int texwidth, const int texheight, char* imagedata_address, ID3D12Resource* texturebuffer);
	/// <summary>
	/// テクスチャ用SRV作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="texturebuffer"></param>
	/// <param name="texdescheap"></param>
	void TextureShadaResoceView(ID3D12Device* device, ID3D12Resource* texturebuffer, ID3D12DescriptorHeap* texdescheap);
	/// <summary>
	/// ディスクリプタヒープの作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="rootsignaturenumdesc"></param>
	/// <param name="texdescheap">[out]</param>
	void CreateDescHeap(ID3D12Device* device, const UINT rootsignaturenumdesc, ID3D12DescriptorHeap** texdescheap);
	
private:

};
