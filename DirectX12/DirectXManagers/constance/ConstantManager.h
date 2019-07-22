#pragma once


#include <memory>
#include <wrl.h>

class ConstanceBufferCreate;
class ConstantBufferViewCreate;
class D3D12DeviceManager;
class ResoceMapUnmap;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
typedef unsigned __int64 UINT64;

class ConstantManager{
private:
	void CreateHeapDesc(std::shared_ptr<D3D12DeviceManager>& device, const int numdesccout);
	void CreateBuffer(std::shared_ptr<D3D12DeviceManager>& device, const size_t& cbufferlayoutstructsize);
	void CreateViewDesc(std::shared_ptr<D3D12DeviceManager>& device);
public:
	ConstantManager();
	~ConstantManager();
	/// <summary>
	/// �萔�o�b�t�@���쐬����@���łɃr���[�����
	/// </summary>
	/// <param name="device"></param>
	/// <param name="cbufferlayoutstructsize">�@1�萔�o�b�t�@�̑傫�� </param>
	/// <param name="numdesccout"> �r���[�̐�(�f�B�X�N���v�^�̐�) </param>
	void CreateConstantBufferAndView(std::shared_ptr<D3D12DeviceManager>& device, const size_t& cbufferlayoutstructsize, const int numdesccout);
	/// <summary>
	///�R���X�^���g�o�b�t�@���}�b�v���� 
	/// </summary>
	/// <param name="address">  �Q�Ƃœn��</param>
	void ConstantbufferMap(void* address);
	//�R���X�^���g�o�b�t�@���A���}�b�v����
	void ConstantbufferUnMap();
	ID3D12DescriptorHeap*& GetDescHeap();
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> _cbuffer;
	ID3D12DescriptorHeap* _descHeap;//TODO: ���L���Ē萔���g�p���邽�߁ACom���g�p����Ə��ł��Ă��܂��\��������
	std::shared_ptr<ResoceMapUnmap> _resocemapunmap;
	int _desc_count;
	UINT64 _agin;
};
