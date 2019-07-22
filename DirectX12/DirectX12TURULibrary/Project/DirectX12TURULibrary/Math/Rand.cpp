#include "Rand.h"
#include <random>

Rand::Rand() {

}
Rand::~Rand() {

}

int Rand::Rand_mt() {
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	return engine();
}
int Rand::Rand_mt_int(int min = 0,int max = 1.0) {
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());//メルセンヌツイスタディストリビューション
	std::uniform_int_distribution<int> rdintDistribution(min, max);
	return rdintDistribution(engine);
}
float Rand::Rand_mt_float(float min = 0.0,float max = 1.0) {
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());//メルセンヌツイスタディストリビューション
	std::uniform_real_distribution<float> randomFloatDistribution(min, max);
	return randomFloatDistribution(engine);
}