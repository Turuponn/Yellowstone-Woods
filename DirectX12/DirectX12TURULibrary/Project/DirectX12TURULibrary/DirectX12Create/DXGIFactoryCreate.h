#pragma once


struct IDXGIFactory4;

class DXGIFactoryCreate {
public:
	DXGIFactoryCreate();
	virtual ~DXGIFactoryCreate();
	/// <summary>
	/// DXGIリソースの作成を行います
	/// </summary>
	/// <param name="dxgifac4">[out]</param>
	void CreateDXGIFactory(IDXGIFactory4** dxgifac4);

private:

};