#pragma once
#include "CommonIncludes.hpp"
#include "AutoPot.hpp"
#include "Config.hpp"
#include "Random.h"

AutoPot cAutoPot;

bool AutoPot::CanPot() {

	if (bIsInChat || bIsInInventory || bCanPot==false)
		return false;
	else
		return true;
}


void tAutoPot() {

	int invclock = clock();

	while (!GetAsyncKeyState(VK_ADD)) {

		if (clock() - cAutoPot.canPotTimer > (long)cRandomDevice.RandomDouble(cAutoPot.DelayBetweenPots.first, cAutoPot.DelayBetweenPots.second)) {
			cAutoPot.bCanPot = true;
		}

		if (cAutoPot.canPressInventory && cAutoPot.bIsInInventory && ((GetAsyncKeyState(cAutoPot.cInventory) & 0x8000) || (GetAsyncKeyState(VK_ESCAPE) & 0x8000))) {
			cAutoPot.bIsInInventory = false;
			invclock = clock();
		}
		else if (clock()-invclock>200&&(GetAsyncKeyState(cAutoPot.cInventory) & 0x8000) && cAutoPot.bIsInInventory == false) {
			cAutoPot.bIsInInventory = true;
			cAutoPot.iCurrentSlot = 2;
			cAutoPot.canPressInventory = false;
		}
		else if (!(GetAsyncKeyState(cAutoPot.cInventory) & 0x8000)&& cAutoPot.canPressInventory==false) {
			cAutoPot.canPressInventory = true;
		}

		if ((GetAsyncKeyState(cAutoPot.cChat) & 0x8000)) {
			cAutoPot.bIsInChat = true;
		}
		if (cAutoPot.bIsInChat && (GetAsyncKeyState(VK_RETURN) & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
			cAutoPot.bIsInChat = false;
		}

		Sleep(1);
	}
}
