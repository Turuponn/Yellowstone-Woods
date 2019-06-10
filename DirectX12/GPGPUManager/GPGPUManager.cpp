#include "GPGPUManager.h"
#include <d3d12.h>
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "d3dx12.h"
#include "DirectXManagers\Shada\CS\ComputeShadaManager.h"
#include "DirectXManagers\PipelineState\PipelineStateManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include <wchar.h>
#include <tchar.h>
#include <vector>
#include "constance.h"
namespace {
	wchar_t* ShadaFilename_CS = _T("resource/ShadaFile/CS/TestComputeShader.hlsl");
	char* ShadaFancname_CS = "TestCS";
}




std::vector<float> testdata(256,0);


GPGPUManager::GPGPUManager() {
	_address = nullptr;
}
GPGPUManager::~GPGPUManager() {

}
void GPGPUManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur,std::shared_ptr<ComandManager>& comand) {
	std::shared_ptr<ComputeShadaManager> csm(new ComputeShadaManager());
	_csm = csm;

	CreateUAVHeap(device);
	CreateUAVBuffer(device);
	CreateUAVView(device);
	
	InitShada(device, rootsignetur);
	
}


void GPGPUManager::InitShada(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignetur) {
	CreateCShada();
	CreateCSPipeline(device, rootsignetur);
}
void GPGPUManager::CreateCShada() {
	_csm->CreateShada(ShadaFilename_CS, ShadaFancname_CS);
}
void GPGPUManager::CreateCSPipeline(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<RootSignatureManager>& rootsignetur) {
	std::shared_ptr<PipelineStateManager> p(new PipelineStateManager());
	_pmanager = p;
	PSTATEM_COMPUTE pcs = {
		device,
		rootsignetur,
		_csm,
	};
	_pmanager->CreateComputeShadaPipeline(pcs);

}

void GPGPUManager::CreateUAVBuffer(std::shared_ptr<D3D12DeviceManager>& device) {
	_csm->CreateUAVBuffer(device, sizeof(float), testdata.size());
	_csm->bufferMap(&_address);

	//_csm->bufferUnMap();//UnMap������G���[�ɂȂ�H

}
void GPGPUManager::Update(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence) {
	_pmanager->SetPipeline(comand);
	
	
	//���鑤�@Note: 
	//[���鑤]���K�v�@UAV�̃p�C�v���C���́A�قƂ�ǂ̏ꍇSRV��CBV���g�p���ăO���t�B�N�X�p�C�v���C���Ɍ��|���邪
	//UAV�P�̂ł��Ȃ����ł��� CBV UAV SRV�@�𑗂鑤�Ɏw�肷�邱�Ƃ��\
	auto uavheap = _csm->GetUAVHeap().Get();
	comand->GetGraphicsCommandList()->SetDescriptorHeaps(1, &uavheap);


	//�󂯎�葤
	comand->GetGraphicsCommandList()->SetComputeRootDescriptorTable(ROOT_PARAM_UAV_TEST, uavheap->GetGPUDescriptorHandleForHeapStart());


	
	//�R���s���[�g�V�F�[�_�[�̎��s
	comand->GetGraphicsCommandList()->Dispatch(testdata.size(), 1, 1);
	

	



	



	

	
	

	comand->ComandClose();
	comand->ComandExecuteCommandList();
	comand->ComandListWaitPorlling(fence);
	comand->ComandReset();
	_pmanager->ReSetPipeline(comand);

	testdata.assign((float*)_address, (float*)_address + testdata.size());

}
void GPGPUManager::CreateUAVView(std::shared_ptr<D3D12DeviceManager>& device) {
	_csm->CreateUAView(device, testdata.size(), sizeof(float));
}
void GPGPUManager::CreateUAVHeap(std::shared_ptr<D3D12DeviceManager>& device) {
	_csm->CreateUAVheap(device);
}