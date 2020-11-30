#include "CommonIncludes.hpp"
#include "Ard.hpp"
#include <Psapi.h>
#include "Click.hpp"
#include "AutoPot.hpp"
#include <string>
#include <thread>
#include "Config.hpp"
#include "Random.h"

bool bMcInFocus() {
	HWND hWnd = GetForegroundWindow();
	char filename[256];
	GetWindowText(hWnd, filename, sizeof(filename));
	if (std::string(filename).find("Minecraft") != std::string::npos || std::string(filename).find("Lunar") != std::string::npos || std::string(filename).find("Badlion") != std::string::npos)
		return true;
	else
		return false;
}

void Print_UI(HANDLE consolehandle,Options & st_Options) {
	SetConsoleCursorPosition(consolehandle, COORD({ 0,0 }));
	std::cout << "                                                     " << std::endl;
	std::cout << "                                                     " << std::endl;
	std::cout << "                                                     " << std::endl;
	std::cout << "                                                     " << std::endl;
	std::cout << "                                                     " << std::endl;
	SetConsoleCursorPosition(consolehandle, COORD({ 0,0 }));
	std::cout << "L - AC" << std::endl;
	printf("MC-Only = %s\n", (st_Options.bMcOnly ? "True" : "False"));
	printf("AC-Toggle = %s\n", (st_Options.bClicker ? "Online" : "Offline"));
	printf("AP-Toggle = %s\n", (st_Options.bAutoPot ? "Online": "Offline"));
	printf("AP-SP = %s\n", (st_Options.bSoupPot ? "Soup" : "Pot"));
}

int main(int argc, char* argv[]) {

	SetConsoleTitle("AnyDesk");

	arduino ard;
	ard.attach("Serielles USB-Gerät");
	Options st_Options;

#pragma region CursorOff
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO* cursorInfo = new CONSOLE_CURSOR_INFO;
	GetConsoleCursorInfo(out, cursorInfo);
	cursorInfo->bVisible = false;
	SetConsoleCursorInfo(out, cursorInfo);
	delete cursorInfo;
#pragma endregion CursorOff

	Print_UI(out, st_Options);

	unsigned int randNum = 0;

	cRandomDevice.Initialize();

	std::thread c(tClicker);
	std::thread p(tAutoPot);


	int UiToggleTimer = clock();

	while (!GetAsyncKeyState(VK_ADD)) {
		Sleep(1);
		if ((GetAsyncKeyState(VK_XBUTTON1) & 0x8000) && st_Options.bClicker == true && ((st_Options.bMcOnly == true && bMcInFocus()) || (st_Options.bMcOnly == false && st_Options.bClicker == true))) { //CLICKER
			cClicker.StartClickTime();
			std::string buf = "C";

			buf += std::to_string(cClicker.GetClickDelay());
			buf += ":";
			buf += std::to_string(cClicker.GetInBetweenClickDelay());

			ard.send_data(buf.c_str(), sizeof(buf));
		}
		else if (!(GetAsyncKeyState(VK_XBUTTON1) & 0x8000)) {
			cClicker.EndClickTime();
		}
		if ((GetAsyncKeyState(cAutoPot.cKeyBind) & 0x8000) && st_Options.bAutoPot == true && bMcInFocus() && cAutoPot.CanPot()) {//THROWPOT
			std::string buf = "T";
			if (st_Options.bSoupPot)
				buf += "S";
			else
				buf += "P";
			buf += std::to_string(cAutoPot.cHotkeys[1]); // SWORD SLOT
			buf += ":";
			buf += std::to_string(cAutoPot.cHotkeys[cAutoPot.iCurrentSlot]);
			buf += ":";
			buf += std::to_string(cAutoPot.cHotkeys[0]);
			cAutoPot.canPotTimer = clock();
			cAutoPot.bCanPot = false;

			cAutoPot.iCurrentSlot++;
			if (cAutoPot.iCurrentSlot > 9)
				cAutoPot.iCurrentSlot = 2;


			ard.send_data(buf.c_str(), sizeof(buf));
		}

		if (clock() - UiToggleTimer > 300) {
			if ((GetAsyncKeyState(VK_INSERT) & 0x8000)) {
				UiToggleTimer = clock();
				st_Options.bShowUi = !st_Options.bShowUi;
				st_Options.bShowUi ? (ShowWindow(GetConsoleWindow(), SW_SHOW)) : ShowWindow(GetConsoleWindow(), SW_HIDE);
			}
			else if ((GetAsyncKeyState(VK_NUMPAD1) & 0x8000)) {
				UiToggleTimer = clock();
				st_Options.bClicker = !st_Options.bClicker;
				Print_UI(out, st_Options);
			}
			else if ((GetAsyncKeyState(VK_NUMPAD2) & 0x8000)) {
				UiToggleTimer = clock();
				st_Options.bAutoPot = !st_Options.bAutoPot;
				Print_UI(out, st_Options);
			}
			else if ((GetAsyncKeyState(VK_NUMPAD3) & 0x8000)) {
				UiToggleTimer = clock();
				st_Options.bSoupPot = !st_Options.bSoupPot;
				Print_UI(out, st_Options);
			}
		}
	}

	c.join();
	p.join();
	CloseHandle(out);
	return 1;
}