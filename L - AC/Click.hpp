#pragma once
#include <utility>

class Clicker {
private:
	double dClickSpeed = 1;

	double inBetweenClicks = 1;

	long ClickTime = 0;

	double fDefaultDropChance = 0.215;
	double fCurrentDropChance = fDefaultDropChance;
	double dDropMax = 0.68;
	double dDropMin = 0.55;


	double fDefaultSpikeChance = 0.098;
	double fCurrentSpikeChance = fDefaultSpikeChance;
	double dSpikeMax = 1.20435;
	double dSpikeMin = 1.055435;

	int chanceMinDuration = 300;
	int chanceMaxDuration = 550;//MS
	int timepoint = 0;
	double changedValue = 0.0;

	std::pair<double, double> dClickRange = { 13.845364 ,10.063455 };// +-0.6 so more like 14.5-12.3; 
	std::pair<double, double> dInBetweenRange = { 18.34565464,6.3456546 };//TRUE DELAYS 4 for 20 cps and 100 for 5 cps


	std::pair<double, double> dBlockRange = { 4.94356 ,2.54533};// +-0.6 so more like 14.5-12.3; 
	std::pair<double, double> dInBetweenBlockRange = { 18.34565464,6.3456546 };//TRUE DELAYS 4 for 20 cps and 100 for 5 cps


	bool Chanced = false;

public:

	void DefaultRandomize();

	void DoChance();

	void StartClickTime();

	void EndClickTime();

	int GetClickTime();

	int GetClickDelay();
	void ChanceShit();

	int GetInBetweenClickDelay();
};

	extern Clicker cClicker;

	void tClicker();
