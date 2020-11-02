#pragma once
#include "CommonIncludes.hpp"


class Random {
private:
	std::mt19937 mt_Rand;

	unsigned int HashedSeed(int h1, int h2, int h3, int h4, int h5);

public:

	Random();

	bool Initialize();

	unsigned int RandomInt(unsigned int dMax, unsigned int dMin);
	double RandomDouble(double dMax, double dMin);

};

extern Random cRandomDevice;
