#pragma once


#include <memory>

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
	~ComputeShadaManager();


	void Initialize();

	//UAV=============================================
	/// <summary>
	/// �R���s���[�g�V�F�[�_�쐬
	/// </summary>
	/// <param name="filename">�t�@�C���p�X</param>
	/// <param name="funcname">�ΏۂƂ��郁�\�b�h��</param>
	void CreateShada(wchar_t* filename, char* funcname);
	/// <summary>
	/// UAV�o�b�t�@�쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="onesize">1�f�[�^�̃T�C�Y</param>
	/// <param name="datasize">1�f�[�^�T�C�Y*�S�̃T�C�Y�́u�S�̃T�C�Y�v������</param>
	void CreateUAVBuffer(std::shared_ptr<D3D12DeviceManager>& device, size_t onesize, int datasize);
	/// <summary>
	/// UAV�r���[�쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="datasize">Dispath�p�f�[�^�̃T�C�Y</param>
	/// <param name="stride">Dispath�p��1�f�[�^�T�C�Y</param>
	void CreateUAView(std::shared_ptr<D3D12DeviceManager>& device, int datasize, size_t stride);
	/// <summary>
	/// UAV�q�[�v�̍쐬
	/// </summary>
	void CreateUAVheap(std::shared_ptr<D3D12DeviceManager>& device);
	/// <summary>
	/// �o�b�t�@�������� 
	/// </summary>
	/// <param name="address">�Q�Ƃœn������</param>
	void bufferMap(void* address);
	void bufferUnMap();
	/// <summary>
	///�@�V�F�[�_�o�C�i����Ԃ�
	/// </summary>
	/// <returns></returns>
	ID3DBlob*& GetCSShada();
	/// <summary>
	/// UAV�p�q�[�v��Ԃ�
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap*& GetUAVHeap();
	//SRV====================================================================
	void CreateSRVHeap(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateSRView(std::shared_ptr<D3D12DeviceManager>& device);
	void CreateSRVBuffer();

	/// <summary>
	/// SRV�p�q�[�v��Ԃ�
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap*& GetSRVHeap();



	ID3D12Resource*& GetUAVBuffer();
	void StartResoce(std::shared_ptr<ComandManager>& comand);
	void EndResoce(std::shared_ptr<ComandManager>& comand);

private:
	ID3DBlob* _cs;
	ID3D12Resource* _csbuffer;
	ID3D12DescriptorHeap* _uavDescHeap;
	ID3D12DescriptorHeap* _srvDescHeap;
	std::shared_ptr<TextureManager> _texm;
	std::shared_ptr<ResoceMapUnmap> _rmap;
};