#pragma once

#include <vector>
#include <string>

#include "Core/Color.hpp"
#include "Core/Size.hpp"

class System {
private:
	System();
public:
	static void initialise();
	static bool keyIsDown(int key);
	static Size getConsoleSize();
	static void clearScreen();
	static void moveCursor(int x, int y);
	static void setTextColor(Color foreground, Color background);

	static std::string getExecutableDirectory();
	static std::vector<std::string> loadFile(std::string path);
};