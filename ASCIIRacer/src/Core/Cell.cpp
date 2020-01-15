#include "Core/Cell.hpp"
#include "Core/Typedefs.hpp"

Cell::Cell() : Cell(IGNORE_CHAR, Color::No_Color, Color::No_Color)
{
}

Cell::Cell(char character) : Cell(character, Color::No_Color, Color::No_Color)
{
}

Cell::Cell(char character, Color foreground) : Cell(character, foreground, Color::No_Color)
{
}

Cell::Cell(char character, Color foreground, Color background)
{
	this->character = character;
	this->foreground = foreground;
	this->background = background;
}

bool Cell::operator==(const Cell& other) {
	return this->character == other.character && this->foreground == other.foreground && this->background == other.background;
}

bool Cell::operator!=(const Cell& other)
{
	return !(*this == other);
}
