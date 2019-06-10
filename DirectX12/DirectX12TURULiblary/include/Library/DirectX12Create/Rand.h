#pragma once



class Rand {
public:
	Rand();
	virtual ~Rand();

	/// <summary>
	/// ランダム(メルセンヌツイスタ)の値を整数で返す
	/// </summary>
	/// <returns></returns>
	int Rand_mt();
private:

};
