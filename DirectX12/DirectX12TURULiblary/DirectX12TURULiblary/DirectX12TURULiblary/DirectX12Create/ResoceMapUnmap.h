#pragma once





struct ID3D12Resource;

class ResoceMapUnmap {
public:
	ResoceMapUnmap();
	virtual ~ResoceMapUnmap();
	/// <summary>
	/// リソースバッファをマップする
	/// </summary>
	/// <param name="address">リストデータへのアドレス [in]参照渡し</param>
	/// <param name="resourcebuffer">マップする対象バッファー</param>
	void Buffer_Map(void* address, ID3D12Resource* resourcebuffer);
	/// <summary>
	/// リソースバッファをアンマップする
	/// </summary>
	/// <param name="resourcebuffer"> アンマップしたいバッファ</param>
	void Buffer_Unmap(ID3D12Resource* resourcebuffer);
	/// <summary>
	/// リソースのメモリ範囲を記述したもの
	/// </summary>
	/// <param name="address"></param>
	/// <param name="resourcebuffer"></param>
	void Buffer_Map_Renge(void* address, ID3D12Resource* resourcebuffer);

private:
};