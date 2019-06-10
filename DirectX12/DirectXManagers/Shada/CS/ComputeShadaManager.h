#pragma once


#include <memory>
#include <wrl.h>

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;
class ResoceMapUnmap;
struct ID3D12Resource;
class D3D12DeviceManager;
struct ID3D12DescriptorHeap;
class TextureManager;
class ComandManager;

class ComputeShadaManager {
private:

public:
	ComputeShadaManager();
	virtual ~ComputeShadaManager();


	void Initialize();

	//UAV=============================================
	/// <summary>
	/// コンピュートシェーダ作成
	/// </summary>
	/// <param name="filename">ファイルパス</param>
	/// <param name="funcname">対象とするメソッド名</param>
	void CreateShada(wchar_t* filename, char* funcname);
	/// <summary>
	/// UAVバッファ作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="onesize">1データのサイズ</param>
	/// <param name="datasize">1データサイズ*全体サイズの「全体サイズ」を入れる</param>
	void CreateUAVBuffer(std::shared_ptr<D3D12DeviceManager>& device, size_t onesize, int datasize);
	/// <summary>
	/// UAVビュー作成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="datasize">Dispath用データのサイズ</param>
	/// <param name="stride">Dispath用の1データサイズ</param>
	void CreateUAView(std::shared_ptr<D3D12DeviceManager>& device, int datasize, size_t stride);
	/// <summary>
	/// UAVヒープの作成
	/// </summary>
	void CreateUAVheap(std::shared_ptr<D3D12DeviceManager>& device);
	/// <summary>
	/// バッファ書き込み 
	/// </summary>
	/// <param name="address">参照で渡すこと</param>
	void bufferMap(void* address);
	void bufferUnMap();
	/// <summary>
	///　シェーダバイナリを返す
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3DBlob>& GetCSShada();
	/// <summary>
	/// UAV用ヒープを返す
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& GetUAVHeap();
	//SRV====================================================================
	void CreateSRVHeap(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateSRView(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateSRVBuffer();

	/// <summary>
	/// SRV用ヒープを返す
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& GetSRVHeap();



	Microsoft::WRL::ComPtr<ID3D12Resource>& GetUAVBuffer();
	void StartResoce(std::shared_ptr<ComandManager>& comand);
	void EndResoce(std::shared_ptr<ComandManager>& comand);

private:
	Microsoft::WRL::ComPtr<ID3DBlob> _cs;
	Microsoft::WRL::ComPtr<ID3D12Resource> _csbuffer;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _uavDescHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _srvDescHeap;
	std::shared_ptr<TextureManager> _texm;
	std::shared_ptr<ResoceMapUnmap> _rmap;
};