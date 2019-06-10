#include "TextureManager.h"
#include <d3d12.h>
#include "Library\GameError.h"
#include "constance.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "Library\DirectX12Create\ResourceBarrier.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "Library\DirectX12Create\TextureCreate.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"


#include <WICTextureLoader\WICTextureLoader12.h>
#include <DirectXTex\DirectXTex.h>
#include <DDSTextureLoader\DDSTextureLoader12.h>
#include "Loder\bmpLoder\BMP_Loader.h"
#include "Loder\TGALoader\TGALoader.h"
#include "Library\DirectX12Create\String.h"
#include "d3dx12.h"



using namespace DirectX;
using namespace Microsoft::WRL;



TextureManager::TextureManager() {
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);//Windowsの機能を使うためにCOMの初期化が必要 ムービー再生でも使用する

}
TextureManager::~TextureManager() {

}
void TextureManager::WICLoadTextureBinary(std::shared_ptr<D3D12DeviceManager>& device) {
	
}
void TextureManager::WICLoadTexture(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence,  const std::string& filepath) {

	std::shared_ptr<TextureCreate> tex_create(new TextureCreate());
	std::shared_ptr<ResourceBarrier> r(new ResourceBarrier());

	_texpath = filepath;
	tex_create->CreateDescHeap(device->GetDevice(), 1, &_texdescheap);
	TexMetadata metadata = {};
	ScratchImage img;
	std::wstring path(filepath.begin(), filepath.end());
	auto result = LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &metadata, img);
	if (result != S_OK) {
		throw(1);
	}
	tex_create->CreateBuffer(device->GetDevice(), (int)metadata.width, (int)metadata.height, &_texturebuffer);
	tex_create->TextureBufferSubresource((int)metadata.width, (int)metadata.height, (char*)img.GetPixels(), _texturebuffer.Get());
	tex_create->TextureShadaResoceView(
		device->GetDevice(),
		_texturebuffer.Get(),
		_texdescheap.Get(),
		_texdescheap->GetCPUDescriptorHandleForHeapStart(),
		DXGI_FORMAT_R8G8B8A8_UNORM 
	);
	
	
}

void TextureManager::SRVCreateHeap(std::shared_ptr<D3D12DeviceManager>& device) {
	std::shared_ptr<TextureCreate> tex_create(new TextureCreate());
	tex_create->CreateDescHeap(device->GetDevice(), 1, &_texdescheap);
}
void TextureManager::SRVCreateHeap(std::shared_ptr<D3D12DeviceManager>& device, const int descnum) {
	std::shared_ptr<TextureCreate> tex_create(new TextureCreate());
	tex_create->CreateDescHeap(device->GetDevice(), descnum, &_texdescheap);
}
void TextureManager::SRVCreateView(std::shared_ptr<D3D12DeviceManager>& device, DXGI_FORMAT srvtexformat, Microsoft::WRL::ComPtr<ID3D12Resource>& buff) {
	std::shared_ptr<TextureCreate> tex_create(new TextureCreate());
	tex_create->TextureShadaResoceView(
		device->GetDevice(),
		buff.Get(),
		_texdescheap.Get(),
		_texdescheap->GetCPUDescriptorHandleForHeapStart(),
		srvtexformat
	);
}
void TextureManager::SRVCreateView(std::shared_ptr<D3D12DeviceManager>& device, DXGI_FORMAT srvtexformat) {
	std::shared_ptr<TextureCreate> tex_create(new TextureCreate());
	tex_create->TextureShadaResoceView(
		device->GetDevice(),
		_texturebuffer.Get(),
		_texdescheap.Get(),
		_texdescheap->GetCPUDescriptorHandleForHeapStart(),
		srvtexformat
	);
}
void TextureManager::SRVBuffer(std::shared_ptr<D3D12DeviceManager>& device,void* pdata,const int size_x, const int size_y) {
	std::shared_ptr<TextureCreate> tex_create(new TextureCreate());
	tex_create->CreateBuffer(device->GetDevice(), size_x, size_y, &_texturebuffer);
	tex_create->TextureBufferSubresource(size_x, size_y, (char*)pdata, _texturebuffer.Get());
}
void TextureManager::DrawSrv(std::shared_ptr<ComandManager>& comand) {
	comand->ComandSetDescriptorHeaps(1, _texdescheap.Get());
}
ID3D12DescriptorHeap* TextureManager::GetSrvHeap() {
	return _texdescheap.Get();
}


void TextureManager::LoadDDSTexture(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, const std::string& texfilepath) {

	HRESULT result = E_FAIL;

	std::string path2 = texfilepath.c_str();
	auto path = StringtoWString(path2);


	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	result = device->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&_texdescheap));
	if (result != S_OK) {
		throw(1);
	}


	std::unique_ptr<uint8_t[]> ddsData;
	std::vector<D3D12_SUBRESOURCE_DATA> subresouceData;
	LoadDDSTextureFromFile(
		device->GetDevice(),
		path.c_str(),
		&_texturebuffer,
		ddsData,
		subresouceData
	);
	D3D12_RESOURCE_DESC textureDesc = _texturebuffer->GetDesc();
	const UINT subresoucesize = static_cast<UINT>(subresouceData.size());
	const UINT64 uploadBufferSize = GetRequiredIntermediateSize(_texturebuffer.Get(), 0, subresoucesize);


	auto desc = _texturebuffer.Get()->GetDesc();
	result = device->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&textureUploadHeap));
	if (result != S_OK) {
		throw(1);
	}


	
	UpdateSubresources(
		comand->GetGraphicsCommandList().Get(),
		_texturebuffer.Get(),
		textureUploadHeap.Get(),
		0,
		0,
		subresoucesize,//11*6 = 66
		&subresouceData[0]);
	



	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = textureDesc.Format;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = _texturebuffer->GetDesc().MipLevels;//1mip 11
	srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
	device->GetDevice()->CreateShaderResourceView(
	_texturebuffer.Get(),
	&srvDesc,
	_texdescheap->GetCPUDescriptorHandleForHeapStart());


}
void TextureManager::LoadTGATexture(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<RootSignatureManager>& rootsignaturemanager,const std::string& filepath) {

	std::shared_ptr<TGALoader> tga(new TGALoader());
	std::shared_ptr<TextureCreate> tex_create(new TextureCreate());
	std::shared_ptr<ResourceBarrier> r(new ResourceBarrier());
	tex_create->CreateDescHeap(device->GetDevice(), rootsignaturemanager->GetRengeType()[ROOT_PARAM_TEXTURE].NumDescriptors, &_texdescheap);

	TGAImageData* pixdata = nullptr;
	tga->LoadImageTGA(filepath, &pixdata);
	tex_create->CreateBuffer(device->GetDevice(), (int)pixdata->header.imagewidth[0], (int)pixdata->header.imageheight[0], &_texturebuffer);
	tex_create->TextureBufferSubresource((int)pixdata->header.imagewidth[0], (int)pixdata->header.imageheight[0], (char*)&pixdata->pixdataList[0], _texturebuffer.Get());

	comand->ComandRBarrier(D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, _texturebuffer.Get());
	comand->GetGraphicsCommandList()->Close();
	comand->ComandExecuteCommandList();
	comand->ComandListWaitPorlling(fence);	

	tex_create->TextureShadaResoceView(
		device->GetDevice(),
		_texturebuffer.Get(),
		_texdescheap.Get(),
		_texdescheap->GetCPUDescriptorHandleForHeapStart(),
		DXGI_FORMAT_R8G8B8A8_UNORM  //24 32どちらもメモリ効率的に累乗に合わせるため RGBのみのformatは存在しない
	);

}


void TextureManager::DrawImage(std::shared_ptr<ComandManager>& comand,const int descnum, TEXTURE_REGISTER texture_register) {
	comand->ComandSetDescriptorHeaps(descnum, _texdescheap.Get());
	comand->ComandSetGraphicsRootDescriptorTable(texture_register, _texdescheap.Get());
	
}
const std::string& TextureManager::GetTextureName() {
	return _texpath;
}