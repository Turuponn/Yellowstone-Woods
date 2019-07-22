#pragma once


#include <memory>
#include <wrl.h>

class IndexBufferCreate;
struct ID3D12Resource;
struct D3D12_INDEX_BUFFER_VIEW;
class D3D12DeviceManager;
class IndexBufferView;
class ResoceMapUnmap;






class IndexBufferManager {
private:
	//�C���f�b�N�X�o�b�t�@�쐬
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allindexsize, const size_t oneindexsize);
public:
	IndexBufferManager();
	~IndexBufferManager();
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device"></param>
	/// <param name="allindexsize">�S�C���f�b�N�X�T�C�Y������@�C���f�b�N�X��*1���_�ԍ��T�C�Y</param>
	/// <param name="oneindexsize">��C���f�b�N�X�̃T�C�Y</param>
	void CreateIndexBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allindexsize, const size_t oneindexsize);
	/// <summary>
	/// �C���f�b�N�X�r���[�̍쐬
	/// </summary>
	/// <param name="allindexsize">�S�C���f�b�N�X�T�C�Y������@�C���f�b�N�X��*1���_�ԍ��T�C�Y</param>
	/// <param name="oneindexsize">��C���f�b�N�X�̃T�C�Y</param>
	/// <param name="vertexnum"></param>
	void CreateBufferView(const int allindexsize, const size_t oneindexsize, const int vertexnum);
	void CreateBufferViewR16(const int allindexsize, const size_t oneindexsize);
	void CreateBufferViewR32(const int allindexsize, const size_t oneindexsize);
	D3D12_INDEX_BUFFER_VIEW*& GetIndexBufferView();
	/// <summary>
	/// ���\�[�X���}�b�v����
	/// </summary>
	/// <param name="indexaddress"> &�������ăf�[�^�̃A�h���X������</param>
	void ResoceMap(void* indexaddress);
	//���\�[�X���A���}�b�v����
	void ResoceUnmap();
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> _indexbuffer;
	D3D12_INDEX_BUFFER_VIEW* _indexbufferview;
	std::shared_ptr<ResoceMapUnmap> _resocemapunmap;
};