#pragma once


struct IDXGIFactory4;

class DXGIFactoryCreate {
public:
	DXGIFactoryCreate();
	virtual ~DXGIFactoryCreate();
	/// <summary>
	/// DXGI���\�[�X�̍쐬���s���܂�
	/// </summary>
	/// <param name="dxgifac4">[out]</param>
	void CreateDXGIFactory(IDXGIFactory4** dxgifac4);

private:

};