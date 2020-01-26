#pragma once

#include <vector>
#include <string>

#include "Core/Color.hpp"
#include "Core/Size.hpp"

class System {
private:
	System();
public:

	/// <summary>	Prepara il modulo per le chiamate di sistema. </summary>

	static void initialise();

	/// <summary>	Controlla se un certo tasto "reale" è al
	/// 			momento premuto. </summary>
	///
	/// <param name="key">	Il codice del tasto. </param>
	///
	/// <returns>	True se il tasto è abbassato, false altrimenti. </returns>

	static bool keyIsDown(int key);

	/// <summary>	Restituisce la dimensione in celle della console. </summary>
	///
	/// <returns>	La dimensione della console. </returns>

	static Size getConsoleSize();

	/// <summary>	Ripulisce la schermata della console. </summary>

	static void clearScreen();

	/// <summary>	Sposta il cursore su una specifica cella. </summary>
	///
	/// <param name="x">	La coordinata x del cursore. </param>
	/// <param name="y">	La coordinata y del cursore. </param>

	static void moveCursor(int x, int y);

	/// <summary>	Imposta il colore del testo. </summary>
	///
	/// <remarks>	Color::No_Color viene interpretato come
	/// 			Color::White per foreground, come
	/// 			Color::Black per background. </remarks>
	///
	/// <param name="foreground">	Il colore del testo. </param>
	/// <param name="background">	Il colore dello sfondo. </param>

	static void setTextColor(Color foreground, Color background);

	/// <summary>	Restituisce un numero casuale a virgola
	/// 			mobile tra 0 e 1 (inclusivo). </summary>
	/// <returns>	Il numero casuale. </returns>

	static float randomFloat();

	/// <summary>	Restituisce il percorso della cartella in
	/// 			cui si trova il file eseguibile. </summary>
	///
	/// <returns>	Il percorso della cartella in cui si trova il
	/// 			file eseguibile. </returns>

	static std::string getExecutableDirectory();

	/// <summary>	Apre un file e lo legge riga per riga. </summary>
	/// <param name="path">	Percorso completo del file. </param>
	///
	/// <returns>	Un vettore contenente ogni riga del file. </returns>

	static std::vector<std::string> loadFile(std::string path);
};