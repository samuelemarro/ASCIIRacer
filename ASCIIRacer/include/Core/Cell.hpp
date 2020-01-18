#pragma once
#include "Color.hpp"

class Cell {
public:
	Color foreground;
	Color background;
	char character;
	bool collision;

	Cell();
	Cell(char character);
	Cell(char character, bool collision);
	Cell(char character, bool collision, Color foreground);
	Cell(char character, bool collision, Color foreground, Color background);
	bool operator==(const Cell& other);
	bool operator!=(const Cell& other);
};