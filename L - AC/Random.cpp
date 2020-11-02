#include "Random.h"

Random cRandomDevice;


Random::Random() = default;

bool Random::Initialize() {
	unsigned int timer = clock();

	DWORD lpWord;
	GetVolumeInformation("C:\\", NULL, NULL, &lpWord, NULL, NULL, NULL, NULL);

	HCRYPTPROV bois;
	CryptAcquireContextA(&bois, NULL, NULL, NULL, NULL);
	BYTE buffer[30];

	unsigned int buf;
	CryptGenRandom(bois, sizeof(buffer), buffer);

	for (int c = 0; c < sizeof(buffer); ++c) {
		if (buffer[c] == 0)
			continue;
		if (!(c % 2)) {
			buf += buffer[c];
		}
		else if (!(c % 3)) {
			buf -= buffer[c];
		}
		else {
			buf *= buffer[c];
		}
	}

	CryptReleaseContext(bois, NULL);

	unsigned char Keypress = 0;

	while (Keypress == 0) {
		for (unsigned int c= 0; c < UCHAR_MAX; ++c) {
			if (GetAsyncKeyState(c)) {
				Keypress = c;
				break;
			}
		}
	}

	mt_Rand.seed(HashedSeed(GetProcessId(GetCurrentProcess()),lpWord, buf,(unsigned int)(Keypress * buffer[2]), (clock()-timer)));
	return true;
}

unsigned int Random::HashedSeed(int h1,int h2, int h3,int h4,int h5) {
	unsigned int buf = unsigned int((((mt_Rand() * (unsigned int)time(NULL)) / h1 + h2) * h3 - h4) * h5);
	if (buf < 0)
		buf *= -1;


	return buf;
}

double Random::RandomDouble(double dMax, double dMin) {
	std::uniform_real_distribution<double> rng(dMin, dMax);
	return rng(mt_Rand);
}
unsigned int Random::RandomInt(unsigned int dMax, unsigned int dMin) {
	std::uniform_int_distribution<unsigned int> rng(dMin, dMax);
	return rng(mt_Rand);
}