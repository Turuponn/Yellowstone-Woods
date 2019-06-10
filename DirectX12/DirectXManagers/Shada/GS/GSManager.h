#pragma once

#include <memory>
#include <string>
#include <wrl.h>

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;


class GSManager {
public:

	GSManager();
	virtual ~GSManager();


	/// <summary>
	/// ジオメトリシェーダ作成
	/// </summary>
	/// <param name="filename">パス</param>
	/// <param name="funcname">メソッド名</param>
	void CreateShada(wchar_t* filename, char* funcname);
	
	/// <summary>
	/// gs用にコンパイル済みのパイプライン用Blobを返す
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3DBlob>& GetBlob();

private:
	Microsoft::WRL::ComPtr<ID3DBlob> _gs;
};
