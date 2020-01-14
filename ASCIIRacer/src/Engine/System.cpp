#include "Engine/System.hpp"
#include "stdlib.h"
#include "windows.h"

#include <exception>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::getline;
using std::runtime_error;

HANDLE hStdout, hStdin;

void System::initialise() {
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

bool System::keyIsDown(int key) {
	return GetKeyState(key) & 0x8000;
}

void System::clearScreen() {
	system("cls");
}

Size System::getConsoleSize() {
	//TODO: Ritornare la dimensione vera
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(hStdout, &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return Size(columns, rows);
}

void System::moveCursor(int x, int y) {
	COORD windowsCoord;
	windowsCoord.X = x;
	windowsCoord.Y = y;
	SetConsoleCursorPosition(hStdout, windowsCoord);
}

std::string System::getExecutableDirectory()
{
	char result[MAX_PATH];
	string executablePath = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
	//return executablePath.substr(0, executablePath.find_last_of("\\/")-9)+"ASCIIRacer";	//questa funziona per Filip
	return executablePath.substr(0, executablePath.find_last_of("\\/"));				//questa funziona per Sam ed Edo
}

vector<string> System::loadFile(string path) {
	ifstream file;
	vector<string> content;

	file.open(path);

	if (!file.is_open()) {
		throw runtime_error("Impossibile aprire il file. "+path);
	}

	string str;
	while (std::getline(file, str))
	{
		content.push_back(str);
	}

	file.close();

	return content;
}