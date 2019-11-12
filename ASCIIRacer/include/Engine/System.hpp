#pragma once

#include "Core/Size.hpp"

class System {
private:
	System();
public:
	static void initialise();
	static bool keyPressed();
	static char getCharacter();
	static Size getConsoleSize();
	static void clearScreen();
	static void moveCursor(int x, int y);
};