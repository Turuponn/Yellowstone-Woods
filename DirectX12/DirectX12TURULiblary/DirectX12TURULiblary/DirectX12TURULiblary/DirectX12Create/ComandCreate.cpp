#include "ComandCreate.h"
#include <d3d12.h>
#include "../GameError.h"

ComandCreate::ComandCreate() {

}
ComandCreate::~ComandCreate() {

}


void ComandCreate::CreateComandAllocator(ID3D12Device* device, ID3D12CommandAllocator** newcommandAllocator) {
	HRESULT result = E_FAIL;
	//コマンド周りを作る 
	//アロケータ(メモリを確保しておく)
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(newcommandAllocator));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T("ComandCreate::CreateComandAllocator result != S_OK")));
	}
}
void ComandCreate::CreateComandList(ID3D12Device* device, ID3D12CommandAllocator* comandallocator, ID3D12GraphicsCommandList** newcomandList) {
	//コマンドリスト作成　アロケートした場所にグラフィックスコマンド用リストを作る
	HRESULT result = E_FAIL;
	result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, comandallocator, nullptr, IID_PPV_ARGS(newcomandList));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR,_T("ComandCreate::CreateComandList result != S_OK")));
	}
}
void ComandCreate::CreateCommandQueue(ID3D12Device* device, ID3D12CommandQueue** newcomand_queue) {
	HRESULT result = E_FAIL;
	D3D12_COMMAND_QUEUE_DESC cmd_desc = {};
	cmd_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	cmd_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;//上のアロケータ、リストと同じにする
	cmd_desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cmd_desc.NodeMask = 0; //For single GPU operation, set this to zero
	result = device->CreateCommandQueue(&cmd_desc, IID_PPV_ARGS(newcomand_queue));
	if (result != S_OK) {
		throw(GameError::GameError(GameErrorNS::FATAL_ERROR, _T(" ComandCreate::CreateCommandQueue result != S_OK")));
	}
}