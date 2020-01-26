#include "Core/Cell.hpp"
#include "Core/Typedefs.hpp"

Cell::Cell() : Cell(IGNORE_CHAR, false, Color::No_Color, Color::No_Color)
{
}

Cell::Cell(char character) : Cell(character, false, Color::No_Color, Color::No_Color)
{
}

Cell::Cell(char character, bool collision) : Cell(character, collision, Color::No_Color, Color::No_Color)
{
}

Cell::Cell(char character, bool collision, Color foreground, Color background)
{
	this->character = character;
	this->collision = collision;
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