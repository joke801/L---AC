#pragma once
#include <utility>

class AutoPot {
public:
	// 0 is DropKey;v
	int cHotkeys[10] = { 120 ,49,113,114,99,193,53,51,52,130 };
	// 0 is DropKey;

	char cKeyBind = 'V';
	char cInventory = 'E';
	char cChat = 'T';
	bool bIsInInventory = false;
	bool bCanPot = true;
	bool bIsInChat = false;
	bool canPressInventory = false;
	int iCurrentSlot = 2;// 1 =SWORT SLOT
	long canPotTimer = clock();

	std::pair<double, double> DelayBetweenPots = { 170.945346,120.354365 };

	bool CanPot();

};
extern AutoPot cAutoPot;

void tAutoPot();


