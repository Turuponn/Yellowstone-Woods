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
	/// テクスチャ用バッファの作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="texwidth"></param>
	/// <param name="texheight"></param>
	/// <param name="format"></param>
	/// <param name="texturebuffer"></param>
	void CreateBuffer(ID3D12Device* device, const int texwidth, const int texheight, DXGI_FORMAT format, ID3D12Resource** texturebuffer);
	/// <summary>
	/// サブリソース化する : テクスチャバッファにデータを書き込む
	/// </summary>
	/// <param name="texwidth">イメージサイズ</param>
	/// <param name="texheight"></param>
	/// <param name="imagedata_address">(char*)データ　として入れる</param>
	/// <param name="texturebuffer"></param>
	void TextureBufferSubresource(const int texwidth, const int texheight, char* imagedata_address, ID3D12Resource* texturebuffer);
	/// <summary>
	/// テクスチャ用シェーダリソースビューの作成 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="texturebuffer"></param>
	/// <param name="texdescheap">ディスクリプタヒープの場所</param>
	/// <param name="cpuhandle"></param>
	/// <param name="format"></param>
	void TextureShadaResoceView(ID3D12Device* device, ID3D12Resource* texturebuffer, ID3D12DescriptorHeap* texdescheap, D3D12_CPU_DESCRIPTOR_HANDLE& cpuhandle,const DXGI_FORMAT& format);
	/// <summary>
	/// データをバッファへコピーする
	/// </summary>
	/// <param name="texwidth"></param>
	/// <param name="texheight"></param>
	/// <param name="imagedata_address"></param>
	/// <param name="descindex"> デスクリプター用インデックス</param>
	/// <param name="texturebuffer"></param>
	void TextureBufferSubresourceArry(
		const int texwidth,
		const int texheight,
		char* imagedata_address,
		const int descindex,
		ID3D12Resource* texturebuffer
	);
	/// <summary>
	/// ディスクリプタヒープの作成 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="numdesc">ルートシグネチャの範囲のディスクリプタ数,または必要なディスクリプタを入れる</param>
	/// <param name="texdescheap">[out]テクスチャ用ディスクリプタヒープを返す</param>
	void CreateDescHeap(ID3D12Device* device, const UINT numdesc, ID3D12DescriptorHeap** texdescheap);

private:
};
