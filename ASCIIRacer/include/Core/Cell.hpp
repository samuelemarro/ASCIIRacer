#pragma once
#include "Color.hpp"

class Cell {
public:
	Color foreground;
	Color background;
	char character;

	Cell();
	Cell(char character);
	Cell(char character, Color foreground);
	Cell(char character, Color foreground, Color background);
	bool operator==(const Cell& other);
	bool operator!=(const Cell& other);
};