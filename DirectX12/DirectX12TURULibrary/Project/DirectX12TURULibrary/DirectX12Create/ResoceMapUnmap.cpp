#include "ResoceMapUnmap.h"
#include <d3d12.h>
#include "GameError.h"


ResoceMapUnmap::ResoceMapUnmap() {
}
ResoceMapUnmap::~ResoceMapUnmap() {

}

void ResoceMapUnmap::Buffer_Map(void* address, ID3D12Resource* resourcebuffer) {

	HRESULT result = E_FAIL;
	result = resourcebuffer->Map(
		0,
		nullptr,//D3D12_RANGE�X�̒l���R���s���[�g�V�F�[�_�g�p����ꍇ��null�ȊO�ɕύX����K�v������܂�
		(void**)address
	);
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("Buffer_Map() result != S_OK")));
	}

}
void ResoceMapUnmap::Buffer_Map_Renge(void* address, ID3D12Resource* resourcebuffer) {

	HRESULT result = E_FAIL;
	D3D12_RANGE resoce_renge = {0,1};
	result = resourcebuffer->Map(
		0,//�T�u���\�[�X�ԍ�
		&resoce_renge,
		(void**)address
	);
	if (result != S_OK) {
		throw(1);
	}

}
void ResoceMapUnmap::Buffer_Unmap(ID3D12Resource* resourcebuffer) {
	resourcebuffer->Unmap(0, nullptr);//�}�b�v�����
}