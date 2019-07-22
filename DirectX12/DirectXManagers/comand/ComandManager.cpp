#include "ComandManager.h"
#include <d3d12.h>
#include "constance.h"
#include "Library\GameError.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "Library\DirectX12Create\ComandCreate.h"
#include "Library\DirectX12Create\ResourceBarrier.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\DepthStencil\Depth\DepthManager.h"
#include "DirectXManagers\vertex\VertexBufferManager.h"
#include "DirectXManagers\index\IndexBufferManager.h"
#include "DirectXManagers\constance\ConstantManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\swapchain\SwapChainManager.h"
#include "d3dx12.h"


UINT64 fencevalue = 0;


ComandManager::ComandManager() {
	Initialize();
}
ComandManager::~ComandManager() {

}

void ComandManager::Initialize() {
	std::shared_ptr<ComandCreate> cmdcreate(new ComandCreate());
	std::shared_ptr<ResourceBarrier> rb(new ResourceBarrier());
	_rb = rb;
	_comandcreate = cmdcreate;
}
void ComandManager::CreateComandAllocators(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain) {
	_comandAllocators.resize(swapchain->GetFrameBufferCount());
	for (int i = 0; i < swapchain->GetFrameBufferCount(); i++) {
		_comandcreate->CreateComandAllocator(device->GetDevice().Get(), &_comandAllocators[i]);
	}
}
void ComandManager::CreateComandQueue(std::shared_ptr<D3D12DeviceManager>& device) {
	_comandcreate->CreateCommandQueue(device->GetDevice().Get(), &_comandQueue);
}
void ComandManager::CreateComandList(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain) {
	_comandcreate->CreateComandList(device->GetDevice().Get(), _comandAllocators[swapchain->GetFrameBufferIndex()].Get(), &_comandList);
}
void ComandManager::ComandListWaitPorlling(std::shared_ptr<FenceManager>& fence) {
	fencevalue++;
	_comandQueue->Signal(fence->GetFence().Get(), fencevalue);
	while (fence->GetFence()->GetCompletedValue() != fencevalue) {}
}
void ComandManager::ComandExecuteCommandList() {
	ID3D12CommandList* cmdlists[] = { _comandList.Get() };
	_comandQueue->ExecuteCommandLists(_countof(cmdlists), cmdlists);
}
void ComandManager::ComandClose() {
	if (_comandList->Close() != S_OK) {
		printf("Comand:  comandClose Error!\n");
	}
}
void ComandManager::ComandReset(std::shared_ptr<SwapChainManager>& swapchain) {
	if (_comandAllocators[swapchain->GetFrameBufferIndex()]->Reset()!= S_OK) {
		throw(1);
	}
}
void ComandManager::SetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate) {
	_comandList->SetPipelineState(pipelinestate->GetPipelineState().Get());
}
void ComandManager::ReSetPipeline(std::shared_ptr<PipelineStateManager>& pipelinestate, std::shared_ptr<SwapChainManager>& swapchain) {
	_comandList->Reset(_comandAllocators[swapchain->GetFrameBufferIndex()].Get(), pipelinestate->GetPipelineState().Get());
}
void ComandManager::ReSetPipeline(std::shared_ptr<SwapChainManager>& swapchain) {
	_comandList->Reset(_comandAllocators[swapchain->GetFrameBufferIndex()].Get(),nullptr);
}
void ComandManager::RootSignatureAttach(std::shared_ptr<RootSignatureManager>& rootsignature) {
	_comandList->SetGraphicsRootSignature(rootsignature->GetRootSignature().Get());
}
void ComandManager::ComandRSSetViewPorts(const int viewportnum,D3D12_VIEWPORT& viewport) {
	_comandList->RSSetViewports(viewportnum, &viewport);
}
void ComandManager::ComandRSSetScissorRects(const int scissorrectnum, tagRECT& scissorRect) {
	_comandList->RSSetScissorRects(scissorrectnum, &scissorRect);
}
void ComandManager::ComandOMSetRenderTargets(const int numrtv, ID3D12DescriptorHeap*& descheap,std::shared_ptr<DepthManager>& depth) {
	_comandList->OMSetRenderTargets(numrtv, &CD3DX12_CPU_DESCRIPTOR_HANDLE(descheap->GetCPUDescriptorHandleForHeapStart()), false, &depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());
}
void ComandManager::ComandClearDepthStencilView(std::shared_ptr<DepthManager>& depth) {
	_comandList->ClearDepthStencilView(depth->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}
void ComandManager::ComandClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE& rtv, float* clearcolor) {
	_comandList->ClearRenderTargetView(rtv, clearcolor, 0, nullptr);
}
void ComandManager::ComandRBarrier(D3D12_RESOURCE_STATES statebefore,D3D12_RESOURCE_STATES stateafter,ID3D12Resource*& tergetresoce) {
	_rb->Barrier(_comandList.Get(),1, statebefore, stateafter, tergetresoce);
}
void ComandManager::ComandRBarrierArry(const int resocenum,D3D12_RESOURCE_STATES statebefore, D3D12_RESOURCE_STATES stateafter, ID3D12Resource*& tergetresoce) {
	_rb->Barrier(_comandList.Get(), resocenum, statebefore, stateafter, tergetresoce);
}
void ComandManager::ComandIASetVertexBuffers(std::shared_ptr<VertexBufferManager>& vbm) {
	_comandList->IASetVertexBuffers(0, 1,vbm->GetVertexBufferView());
}
void ComandManager::ComandIASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology) {
	_comandList->IASetPrimitiveTopology(topology);
}
void ComandManager::ComandIASetIndexBuffer(std::shared_ptr<IndexBufferManager>& indexm) {
	_comandList->IASetIndexBuffer(indexm->GetIndexBufferView());
}
void ComandManager::ComandDrawIndexedInstanced(const int instancenum,const int fecenum) {
	_comandList->DrawIndexedInstanced(fecenum, instancenum, 0, 0, 0);
}
void ComandManager::ComandDrawInstanced(const int vertexnum,const int instancenum) {
	_comandList->DrawInstanced(vertexnum, instancenum, 0, 0);
}
void ComandManager::ComandSetDescriptorHeaps(const int descheapnum, ID3D12DescriptorHeap*&  heap) {
	_comandList->SetDescriptorHeaps(descheapnum, &heap);
}
void ComandManager::ComandSetGraphicsRootDescriptorTable(const int rootparamidx, ID3D12DescriptorHeap*& heap) {
	_comandList->SetGraphicsRootDescriptorTable(rootparamidx, heap->GetGPUDescriptorHandleForHeapStart());
}
std::vector< Microsoft::WRL::ComPtr<ID3D12CommandAllocator>>& ComandManager::GetComandAllocators() {
	return _comandAllocators;
}
Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList>& ComandManager::GetGraphicsCommandList() {
	return _comandList;
}
Microsoft::WRL::ComPtr<ID3D12CommandQueue>& ComandManager::GetComandQueue() {
	return _comandQueue;
}

