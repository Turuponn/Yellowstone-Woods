#include "D2DManager.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\DX11on12\D3D11On12DeviceManager.h"
#include "Library\DirectX12Create\RenderTargetCreate.h"
#include "DirectXManagers\swapchain\SwapChainManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_3.h>//Factory3
#include <d3d12.h>
#include <d3d11.h>
#include <dxgi1_4.h>
#include <dwrite.h>
#include <d3dx12.h>
#include <d3d11on12.h>
using namespace Microsoft::WRL;

namespace {
	D2D1_BITMAP_PROPERTIES1 _bitmapProperties = {};
}

/*
スワップチェインのバックバッファに書き込むUIのテストクラスです
テキストは表示できましたが、途中でエクゼキュートするため画面がちらつきます。
*/

D2DManager::D2DManager() {
	_d2dFactory = nullptr;
}
D2DManager::~D2DManager() {
	_d2dFactory->Release();
}


void D2DManager::CreateFactory() {
	D2D1_FACTORY_OPTIONS d2dFactoryOptions = {};
#if defined(_DEBUG)
	// Enable the D2D debug layer.
	d2dFactoryOptions.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		d2dFactoryOptions,
		&_d2dFactory
	); 
	if (hr != S_OK) {
		throw(1);
	}
}

void D2DManager::CreateFrameResoce(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<D3D11On12DeviceManager>& device11on12,std::shared_ptr<SwapChainManager>& swapchain) {
	auto backbuffernum = swapchain->GetFrameBufferCount();
	_renderTargets.resize(backbuffernum);
	_wrappedBackBuffers.resize(backbuffernum);
	_d2dRenderTargets.resize(backbuffernum);
	/*
	TODO: ComPtr依存の設計
	*/
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(swapchain->GetSwapChainDescHeap()->GetCPUDescriptorHandleForHeapStart());
		auto rtvoffset = device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		for (UINT n = 0; n < swapchain->GetFrameBufferCount(); n++)
		{
			if (!(SUCCEEDED(swapchain->GetSwapChain()->GetBuffer(n, IID_PPV_ARGS(&_renderTargets[n]))))) {//キャンバスをスワップチェインから取得
				throw(1);
			}
			device->GetDevice()->CreateRenderTargetView(_renderTargets[n].Get(), nullptr, rtvHandle);//キャンバスへ紐づけ
			D3D11_RESOURCE_FLAGS d3d11Flags = { D3D11_BIND_RENDER_TARGET };
			if (!(SUCCEEDED(
				device11on12->GetD3D11on12Device()->CreateWrappedResource( //リソースの状態を設定
				_renderTargets[n].Get(),
				&d3d11Flags,
				D3D12_RESOURCE_STATE_RENDER_TARGET,
				D3D12_RESOURCE_STATE_PRESENT,
				IID_PPV_ARGS(&_wrappedBackBuffers[n])//バックバッファ
			)))) {
				throw(1);
			}
			ComPtr<IDXGISurface> surface;
			if (!(SUCCEEDED(_wrappedBackBuffers[n].As(&surface)))){
				throw(1);
			}
			if (!(SUCCEEDED(_d2ddevicecontext->CreateBitmapFromDxgiSurface(
				surface.Get(),
				&_bitmapProperties,
				&_d2dRenderTargets[n]
			)))) {
				throw(1);
			}
			rtvHandle.Offset(1, rtvoffset);
		}
}
void D2DManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<D3D11On12DeviceManager>& device11on12,std::shared_ptr<SwapChainManager>& swapchain) {
	CreateFactory();
	D2D1_DEVICE_CONTEXT_OPTIONS deviceOptions = D2D1_DEVICE_CONTEXT_OPTIONS_NONE;
	device11on12->GetD3D11on12Device().As(&_dxgiDevice);
	if (!(SUCCEEDED(_d2dFactory->CreateDevice(_dxgiDevice.Get(), &_d2ddevice)))) {
		throw(1);
	}
	if (!(SUCCEEDED(_d2ddevice->CreateDeviceContext(deviceOptions, &_d2ddevicecontext)))) {
		throw(1);
	}
	if (!(SUCCEEDED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &_idwritefactory)))) {//テキスト等ブラシ作成するなら
		throw(1);
	}
	DpiInfo();
	CreateFrameResoce(device,device11on12, swapchain);
	
	//TODO: 文字情報、フォント等の設定
	if (!(SUCCEEDED(_d2ddevicecontext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &_textBrush)))) {
		throw(1);
	}
	if (!(SUCCEEDED((_idwritefactory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50,
		L"en-us",
		&_textFormat
	))))) {
		throw(1);
	}
	if (!(SUCCEEDED(_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)))) {
		throw(1);
	}
	if (!(SUCCEEDED(_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)))) {
		throw(1);
	}
}
void D2DManager::DpiInfo() {
	_d2dFactory->GetDesktopDpi(&_dpi.dpiX, &_dpi.dpiY);
	_bitmapProperties = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		_dpi.dpiX,
		_dpi.dpiY
	);
	
}
void D2DManager::RenderUI(std::shared_ptr<D3D11On12DeviceManager>& device11on12,std::shared_ptr<SwapChainManager>& swapchain,std::shared_ptr<ComandManager>& comand)
{
	
	D2D1_SIZE_F rtSize = _d2dRenderTargets[swapchain->GetFrameBufferIndex()]->GetSize();
	D2D1_RECT_F textRect = D2D1::RectF(0, 0, rtSize.width, rtSize.height);
	static const WCHAR text[] = L"11On12";

	// Acquire our wrapped render target resource for the current back buffer.
	device11on12->GetD3D11on12Device()->AcquireWrappedResources(_wrappedBackBuffers[swapchain->GetFrameBufferIndex()].GetAddressOf(), 1);

	// Render text directly to the back buffer.
	_d2ddevicecontext->SetTarget(_d2dRenderTargets[swapchain->GetFrameBufferIndex()].Get());
	_d2ddevicecontext->BeginDraw();
	_d2ddevicecontext->SetTransform(D2D1::Matrix3x2F::Identity());
	_d2ddevicecontext->DrawTextW(
		text,
		_countof(text) - 1,
		_textFormat.Get(),
		&textRect,
		_textBrush.Get()
	);
	if (!(SUCCEEDED(_d2ddevicecontext->EndDraw()))) {
		throw(1);
	}
	//リソース状態遷移
	device11on12->GetD3D11on12Device()->ReleaseWrappedResources(_wrappedBackBuffers[swapchain->GetFrameBufferIndex()].GetAddressOf(), 1);
	device11on12->GetD3D11DeviceContext()->Flush();

}


std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>& D2DManager::GetRTVResoce() {
	return _renderTargets;
}
