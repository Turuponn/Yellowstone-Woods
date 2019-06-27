#pragma once

#include "Geometori.h"
#include <string>
#include <memory>
#include <wrl.h>


class D3D12DeviceManager;
class ComandManager;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11On12Device;

class D3D11On12DeviceManager {
public:
	D3D11On12DeviceManager();
	virtual ~D3D11On12DeviceManager();

	/// <summary>
	/// Dx11の機能を12で利用できるようなデバイスを作成します。
	/// </summary>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	void Create11On12Device(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand
	);
	Microsoft::WRL::ComPtr<ID3D11On12Device>& GetD3D11on12Device();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>& GetD3D11DeviceContext();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> _d3d11Device;
	Microsoft::WRL::ComPtr<ID3D11On12Device> _d3d11On12Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3d11DeviceContext;
};