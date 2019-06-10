#pragma once


struct ID3D12Device;
struct IDXGIAdapter;

class D3D12DeviceCreate {
public:
	D3D12DeviceCreate();
	virtual ~D3D12DeviceCreate();

	/// <summary>
	/// D3D12デバイスを作成する
	/// </summary>
	/// <param name="device">[out]デバイスを返す</param>
	/// <param name="adapter">　グラボ選択用giアダプタを入れる </param>
	void CreateDevice(ID3D12Device** device, IDXGIAdapter* adapter);
private:
	
};