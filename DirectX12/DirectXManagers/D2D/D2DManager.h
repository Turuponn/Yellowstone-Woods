#pragma once

#include "Geometori.h"
#include <wrl.h>
#include <memory>
#include <vector>
struct ID2D1Factory3;
struct ID2D1HwndRenderTarget;
struct ID2D1SolidColorBrush;
struct ID2D1Device;
struct ID2D1DeviceContext;
struct IDXGIDevice;
struct IDWriteFactory;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
struct ID3D11Resource;
struct ID2D1Bitmap1;
struct ID2D1SolidColorBrush;
struct IDWriteTextFormat;
class D3D12DeviceManager;
class D3D11On12DeviceManager;
class SwapChainManager;
class ComandManager;

struct DPI {
	float dpiX;
	float dpiY;
};

class D2DManager {
private:
	
private:
	void CreateFactory();
	void CreateRTV(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<SwapChainManager>& swapchain);
	void CreateFrameResoce(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<D3D11On12DeviceManager>& device11on12,std::shared_ptr<SwapChainManager>& swapchain);
public:
	D2DManager();
	virtual ~D2DManager();


	void Initialize(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<D3D11On12DeviceManager>& device11on12,
		std::shared_ptr<SwapChainManager>& swapchain
	);
	/// <summary>
	/// デスクトップのdpi(解像度)設定を取得
	/// </summary>
	void DpiInfo();

	void RenderUI(std::shared_ptr<D3D11On12DeviceManager>& device11on12,std::shared_ptr<SwapChainManager>& swapchain, std::shared_ptr<ComandManager>& comand);
	

	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>& GetRTVResoce();

private:
	ID2D1Factory3* _d2dFactory;
	Microsoft::WRL::ComPtr<ID2D1Device> _d2ddevice;
	Microsoft::WRL::ComPtr<ID2D1DeviceContext> _d2ddevicecontext;
	Microsoft::WRL::ComPtr<IDWriteFactory> _idwritefactory;
	Microsoft::WRL::ComPtr<IDXGIDevice> _dxgiDevice;
	//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvdescheap;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> _textFormat;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> _d2dRenderTargets;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> _renderTargets;
	std::vector<Microsoft::WRL::ComPtr<ID3D11Resource>> _wrappedBackBuffers;
	DPI _dpi;



	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> _textBrush;//テキスト情報用入れ
};