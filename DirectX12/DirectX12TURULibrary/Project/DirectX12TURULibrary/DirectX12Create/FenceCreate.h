#pragma once

struct ID3D12Device;
struct ID3D12Fence;
typedef unsigned __int64    UINT64;


class FenceCreate {
public:
	FenceCreate();
	virtual ~FenceCreate();
	/// <summary>
	///�t�F���X�쐬 
	/// </summary>
	/// <param name="device"></param>
	/// <param name="initializefenceValue">�t�F���X�J�E���^������</param>
	/// <param name="fence">[out] �t�F���X���쐬���Ԃ�</param>
	void CreateFance(ID3D12Device* device, UINT64 initializefenceValue, ID3D12Fence** fence);

private:
};