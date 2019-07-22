#pragma once

struct ID3D12Device;
struct ID3D12Fence;
typedef unsigned __int64    UINT64;


class FenceCreate {
public:
	FenceCreate();
	virtual ~FenceCreate();
	/// <summary>
	///フェンス作成 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="initializefenceValue">フェンスカウンタを入れる</param>
	/// <param name="fence">[out] フェンスを作成し返す</param>
	void CreateFance(ID3D12Device* device, UINT64 initializefenceValue, ID3D12Fence** fence);

private:
};