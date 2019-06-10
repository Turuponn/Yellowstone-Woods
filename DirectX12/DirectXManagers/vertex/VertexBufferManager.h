#pragma once


#include <memory>
#include <wrl.h>

class VertexBufferCreate;
class VertexBufferView;
struct ID3D12Resource;
struct D3D12_VERTEX_BUFFER_VIEW;
class D3D12DeviceManager;
class ResoceMapUnmap;
class FenceManager;
class ComandManager;

class VertexBufferManager {
private:
	//���_�o�b�t�@�쐬
	//@param allvertexsize �S���_�T�C�Y
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allvertexsize);
	//�r���[�쐬
	//@param onevertexsize �꒸�_������̃T�C�Y
	void CreateView(const int onevertexsize);
public:
	VertexBufferManager();
	virtual ~VertexBufferManager();

	//������
	//@param allvertexsize �S���_�T�C�Y
	//@param onevertexsize �꒸�_������̃T�C�Y
	void CreateVertexBuffer(std::shared_ptr<D3D12DeviceManager>& device, const int allvertexsize, const int onevertexsize);

	//�}�b�v
	void ResoceMap(void* vertexaddress);
	//�A���}�b�v
	void ResoceUnmap();
	//GPU�ɑ�����܂ő҂���
	void ResoceGPUWait(std::shared_ptr<FenceManager>& fence, std::shared_ptr<ComandManager>& comand);

	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW*& GetVertexBufferView();



private:
	std::shared_ptr<ResoceMapUnmap> _resocemapunmap;
	Microsoft::WRL::ComPtr<ID3D12Resource> _vertexbuffer;
	D3D12_VERTEX_BUFFER_VIEW* _vertexview;
};
