#include "System.hpp"
#include "conio.h"
#include "stdlib.h"
#include "windows.h"

HANDLE hStdout, hStdin;

void System::initialise() {
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

bool System::keyPressed() {
	return _kbhit();
}

char System::getCharacter() {
	return _getch();
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