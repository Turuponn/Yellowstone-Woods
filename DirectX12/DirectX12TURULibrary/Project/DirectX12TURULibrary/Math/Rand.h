#pragma once



class Rand {
public:
	Rand();
	virtual ~Rand();
	/// <summary>
	/// �����_��(�����Z���k�c�C�X�^)�̒l�����S�����_���ŕԂ�
	/// </summary>
	/// <returns>[out]</returns>
	int Rand_mt();
	/// <summary>
	/// �����_��(�����Z���k�c�C�X�^)�̒l���w�萮���͈͂ŕԂ�
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns>[out]</returns>
	int Rand_mt_int(int min, int max);
	/// <summary>
	/// �����_��(�����Z���k�c�C�X�^)�̒l���w�蕂�������_�͈͂ŕԂ�
	/// </summary>
	/// <returns>[out]</returns>
	float Rand_mt_float(float min, float max);
private:

};
