#pragma once
#include "Color.hpp"

/// <summary>	Rappresenta una cella della console. </summary>

class Cell {
public:

	/// <summary>	Il colore del testo. </summary>
	Color foreground;

	/// <summary>	Il colore dello sfondo. </summary>
	Color background;

	/// <summary>	Il carattere da stampare. </summary>
	char character;

	/// <summary>	Se questa cella deve essere considerata
	/// 			per i controlli di collisioni. </summary>
	bool collision;

	Cell();
	Cell(char character);
	Cell(char character, bool collision);
	Cell(char character, bool collision, Color foreground);
	Cell(char character, bool collision, Color foreground, Color background);
	bool operator==(const Cell& other);
	bool operator!=(const Cell& other);
};