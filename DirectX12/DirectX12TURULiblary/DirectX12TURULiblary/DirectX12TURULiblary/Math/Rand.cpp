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