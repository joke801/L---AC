#include "CommonIncludes.hpp"
#include "Click.hpp"
#include "Random.h"

Clicker cClicker;

void tClicker() {

	long timerforDefault = clock();

	long timerforChance= clock();

	while (!GetAsyncKeyState(VK_ADD)) {
		Sleep(1);
		if (clock() - timerforDefault > signed int(cRandomDevice.RandomInt(1400, 1000))) {
			cClicker.DefaultRandomize();
			timerforDefault = clock();
		}
		if (clock() - timerforChance > signed int(cRandomDevice.RandomInt(1300, 1200))) {
			cClicker.DoChance();
			timerforChance = clock();
		}
		cClicker.ChanceShit();

	}
}
void Clicker::DefaultRandomize() {
	dClickSpeed = cRandomDevice.RandomDouble(dClickRange.first, dClickRange.second);
	if(Chanced)
		dClickSpeed *= changedValue;
	inBetweenClicks = cRandomDevice.RandomDouble(dInBetweenRange.first, dInBetweenRange.second);
	DoChance();
}

void Clicker::DoChance() {
	if (Chanced)
		return;
	double chanceBuffer = cRandomDevice.RandomDouble(0.0, 1.01);
	if (chanceBuffer < fCurrentDropChance) {
		if (changedValue == 1 ||changedValue<1) {
			this->Chanced = true;
			this->changedValue = cRandomDevice.RandomDouble(dDropMax, dDropMin);
			this->dClickSpeed *= this->changedValue;
			this->timepoint = this->ClickTime;
			this->fCurrentDropChance -= 0.01;
			this->fCurrentSpikeChance += 0.005;
		}
		else {
			changedValue = 1;
		}
	}
	else {
		chanceBuffer = cRandomDevice.RandomDouble(0.0, 1.01);
		if (chanceBuffer < fCurrentSpikeChance) {
			if (changedValue == 1 || changedValue>1) {
				this->Chanced = true;
				this->changedValue = cRandomDevice.RandomDouble(dSpikeMax, dSpikeMin);
				this->dClickSpeed *= this->changedValue;
				this->timepoint = this->ClickTime;
				this->fCurrentSpikeChance -= 0.02;
				this->fCurrentDropChance +=0.012;

			}
			else {
				changedValue = 1;
			}

		}
	}
}

void Clicker::StartClickTime() {
	if (ClickTime == 0)
		ClickTime = clock();
}

void Clicker::EndClickTime() {
	ClickTime = 0;
}

int Clicker::GetClickTime() {
	return ClickTime;
}

int Clicker::GetClickDelay() {
	return (int)((1000 / dClickSpeed)- inBetweenClicks);
}

int Clicker::GetInBetweenClickDelay() {
	return int(inBetweenClicks);
}
void Clicker::ChanceShit() {
	if (!Chanced)
		return;

	if ((clock()-ClickTime) - timepoint > cRandomDevice.RandomInt(chanceMaxDuration, chanceMinDuration)) {
		Chanced = false;
	}

}
