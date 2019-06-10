#include "ResourceBarrier.h"
#include <d3d12.h>
#include "GameError.h"



ResourceBarrier::ResourceBarrier() {
	
}
ResourceBarrier::~ResourceBarrier() {

}



void ResourceBarrier::Barrier(ID3D12GraphicsCommandList* cmdgraphicslist,const int resocenum,D3D12_RESOURCE_STATES statebefore,D3D12_RESOURCE_STATES stateafter,ID3D12Resource* targetbuffer) {
	
	// バックバッファの描画完了を待つためのバリアを設置
	D3D12_RESOURCE_BARRIER resource_barrier = {};

	resource_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                    // バリアはリソースの状態遷移に対して設置->遷移バリア
	resource_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	resource_barrier.Transition.pResource = targetbuffer;                               //対象リソース
	resource_barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES; //すべてのサブリソースに対応
	resource_barrier.Transition.StateBefore = statebefore;                             //遷移前は : 前 状態
	resource_barrier.Transition.StateAfter = stateafter;                               // 遷移後は : 後 状態

	//リソースバリアおよびフェンス待ち 1はリソースの数
	cmdgraphicslist->ResourceBarrier(resocenum, &resource_barrier);
}
