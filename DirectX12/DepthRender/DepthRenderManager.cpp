#include "DepthRenderManager.h"
#include <d3d12.h>
#include "d3dx12.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\Shada\Vertex\VertexShadaManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\Shada\Pixcel\PixcelShadaManager.h"
#include "constance.h"
#include <wchar.h>
#include <tchar.h>


namespace {


	D3D12_RECT							scissor_rect_sm_;
	D3D12_VIEWPORT						viewport_sm_;

}

DepthRenderManager::DepthRenderManager() {

}
DepthRenderManager::~DepthRenderManager() {

}
void DepthRenderManager::CreateBufferHeap(std::shared_ptr<D3D12DeviceManager>& device) {
	HRESULT result = E_FAIL;
	D3D12_DESCRIPTOR_HEAP_DESC descriptor_heap_desc{};
	descriptor_heap_desc.NumDescriptors = 1;
	descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descriptor_heap_desc.NodeMask = 0;
	result = device->GetDevice()->CreateDescriptorHeap(&descriptor_heap_desc, IID_PPV_ARGS(&dh_buffer_));
	if (FAILED(result)) {
		throw(1);
	}
	descriptor_heap_desc.NumDescriptors = 1;
	descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	result = device->GetDevice()->CreateDescriptorHeap(&descriptor_heap_desc, IID_PPV_ARGS(&dh_texture_));
	if (FAILED(result)) {
		throw(1);
	}

	//サイズは特に不問　大きい方がアーティファクトを減らせる
	viewport_sm_.TopLeftX = 0.f;
	viewport_sm_.TopLeftY = 0.f;
	viewport_sm_.Width = SCREEN_SIZE_X;
	viewport_sm_.Height = SCREEN_SIZE_Y;
	viewport_sm_.MinDepth = 0.f;
	viewport_sm_.MaxDepth = 1.f;

	scissor_rect_sm_.top = 0;
	scissor_rect_sm_.left = 0;
	scissor_rect_sm_.right = SCREEN_SIZE_X;
	scissor_rect_sm_.bottom = SCREEN_SIZE_Y;
	
}
void DepthRenderManager::DepthRenderInit(std::shared_ptr<D3D12DeviceManager>& device) {
	CreateBuffer(device);
}

void DepthRenderManager::DepthRenderPre(std::shared_ptr<ComandManager>& comand) {
	//テクスチャを深度書き込みに設定
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_DEPTH_WRITE, d_buffer_.Get());
	//深度バッファをクリア
	comand->GetGraphicsCommandList()->ClearDepthStencilView(
		dh_buffer_->GetCPUDescriptorHandleForHeapStart(),
		D3D12_CLEAR_FLAG_DEPTH,
		1.0f,
		0,
		0,
		nullptr
	);
	//ビューポートとシザー矩形の設定
	comand->GetGraphicsCommandList()->RSSetViewports(1, &viewport_sm_);
	comand->GetGraphicsCommandList()->RSSetScissorRects(1, &scissor_rect_sm_);
	//描画用サンプラ先
	comand->ComandSetDescriptorHeaps(1, dh_texture_.Get());
	comand->ComandSetGraphicsRootDescriptorTable(ROOT_PARAM_TEXTURE_DEPTH, dh_texture_.Get());
	comand->GetGraphicsCommandList()->OMSetRenderTargets(0, nullptr, FALSE, &dh_buffer_->GetCPUDescriptorHandleForHeapStart());


	//普通の描画
}
void DepthRenderManager::DepthRenderPost(std::shared_ptr<ComandManager>& comand,std::shared_ptr<FenceManager>& fence) {
	comand->ComandRBarrier(D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ, d_buffer_.Get());
}
void DepthRenderManager::CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device) {
	CreateBufferHeap(device);
	HRESULT result = E_FAIL;
	
	

	//深度バッファ作成
	D3D12_HEAP_PROPERTIES heap_properties{};
	D3D12_RESOURCE_DESC resource_desc{};
	D3D12_CLEAR_VALUE clear_value{};
	heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 0;
	heap_properties.VisibleNodeMask = 0;


	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resource_desc.Width = SCREEN_SIZE_X;
	resource_desc.Height = SCREEN_SIZE_Y;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 0;
	resource_desc.Format = DXGI_FORMAT_R32_TYPELESS;//深度テクスチャをR32のサイズとして確保
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;
	resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	clear_value.Format = DXGI_FORMAT_D32_FLOAT;
	clear_value.DepthStencil.Depth = 1.0f;
	clear_value.DepthStencil.Stencil = 0;

	result = device->GetDevice()->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, &clear_value, IID_PPV_ARGS(&d_buffer_));
	if (FAILED(result)) {
		throw(result);
	}

	CreateBufferView(device);
}
void DepthRenderManager::CreateBufferView(std::shared_ptr<D3D12DeviceManager>& device) {
	//深度バッファのビューの作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc{};
	dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
	dsv_desc.Texture2D.MipSlice = 0;
	dsv_desc.Flags = D3D12_DSV_FLAG_NONE;
	device->GetDevice()->CreateDepthStencilView(d_buffer_.Get(), &dsv_desc, dh_buffer_->GetCPUDescriptorHandleForHeapStart());



	D3D12_SHADER_RESOURCE_VIEW_DESC resourct_view_desc{};
	resourct_view_desc.Format = DXGI_FORMAT_R32_FLOAT;
	resourct_view_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	resourct_view_desc.Texture2D.MipLevels = 1;
	resourct_view_desc.Texture2D.MostDetailedMip = 0;
	resourct_view_desc.Texture2D.PlaneSlice = 0;
	resourct_view_desc.Texture2D.ResourceMinLODClamp = 0.0F;
	resourct_view_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	device->GetDevice()->CreateShaderResourceView(d_buffer_.Get(), &resourct_view_desc, dh_texture_->GetCPUDescriptorHandleForHeapStart());

}