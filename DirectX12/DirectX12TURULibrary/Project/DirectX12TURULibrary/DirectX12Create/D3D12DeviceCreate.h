#pragma once


struct ID3D12Device;
struct IDXGIAdapter;

class D3D12DeviceCreate {
public:
	D3D12DeviceCreate();
	virtual ~D3D12DeviceCreate();

	/// <summary>
	/// D3D12�f�o�C�X���쐬����
	/// </summary>
	/// <param name="device">[out]�f�o�C�X��Ԃ�</param>
	/// <param name="adapter">�@�O���{�I��pgi�A�_�v�^������ </param>
	void CreateDevice(ID3D12Device** device, IDXGIAdapter* adapter);
private:
	
};