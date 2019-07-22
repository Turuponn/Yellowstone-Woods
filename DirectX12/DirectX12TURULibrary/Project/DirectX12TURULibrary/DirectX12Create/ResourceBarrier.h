#pragma once



struct ID3D12GraphicsCommandList;
struct ID3D12Resource;
enum D3D12_RESOURCE_STATES;

class ResourceBarrier{
public:
	ResourceBarrier();
	virtual ~ResourceBarrier();
	/// <summary>
	/// ���\�[�X���g�p�ړI�ɍ��킹�ăo���A����
	/// </summary>
	/// <param name="cmdgraphicslist"></param>
	/// <param name="resocenum">���\�[�X�̐��@��{1</param>
	/// <param name="statebefore">���݂̃��\�[�X�̏�Ԃ��w�肷��</param>
	/// <param name="stateafter">���݂̃��\�[�X�̏�Ԃ��I��������Ƃǂ�ȏ�Ԃɂ��邩�w�肷��</param>
	/// <param name="targetbuffer"></param>
	void Barrier(
		ID3D12GraphicsCommandList* cmdgraphicslist,
		const int resocenum,
		D3D12_RESOURCE_STATES statebefore,
		D3D12_RESOURCE_STATES stateafter,
		ID3D12Resource* targetbuffer
	);
private:

};