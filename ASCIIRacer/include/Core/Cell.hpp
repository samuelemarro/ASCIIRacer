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

	/// <summary>	Costruttore di default. </summary>

	Cell();

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="character">	Il carattere da stampare. </param>

	Cell(char character);

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="character"> 	Il carattere da stampare. </param>
	/// <param name="collision"> 	Se questa cella deve essere
	/// 							considerata per il controllo
	/// 							collisioni. </param>
	///
	Cell(char character, bool collision);

	/// <summary>	Costruttore completo. </summary>
	///
	/// <param name="character"> 	Il carattere da stampare. </param>
	/// <param name="collision"> 	Se questa cella deve essere
	/// 							considerata per il controllo
	/// 							collisioni. </param>
	/// <param name="foreground">	Il colore del testo. </param>
	/// <param name="background">	Il colore dello sfondo. </param>

	Cell(char character, bool collision, Color foreground, Color background);

	/// <summary>	Operatore di uguaglianza. </summary>
	///
	/// <param name="other">	L'altra Cell. </param>
	///
	/// <returns>	Vero se gli oggetti sono equivalenti. </returns>

	bool operator==(const Cell& other);

	/// <summary>	Operatore di disuguaglianza. </summary>
	///
	/// <param name="other">	L'altra Cell. </param>
	///
	/// <returns>	Vero se gli oggetti non sono equivelenti. </returns>

	bool operator!=(const Cell& other);
};