#pragma once



class Rand {
public:
	Rand();
	virtual ~Rand();
	/// <summary>
	/// ランダム(メルセンヌツイスタ)の値を完全ランダムで返す
	/// </summary>
	/// <returns>[out]</returns>
	int Rand_mt();
	/// <summary>
	/// ランダム(メルセンヌツイスタ)の値を指定整数範囲で返す
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns>[out]</returns>
	int Rand_mt_int(int min, int max);
	/// <summary>
	/// ランダム(メルセンヌツイスタ)の値を指定浮動小数点範囲で返す
	/// </summary>
	/// <returns>[out]</returns>
	float Rand_mt_float(float min, float max);
private:

};
