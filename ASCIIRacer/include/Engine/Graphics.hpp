#include <string>

#include "Core/Rect.hpp"
#include "Core/Size.hpp"
#include "Core/Typedefs.hpp"
#include "GameObjects/GameObject.hpp"

class Graphics {
private:
	Graphics();
	static ScreenBuffer oldBuffer;

	static Sprite parseSprite(std::vector<std::string> lines, Size& size);

	static Color hexToColor(char value);

public:

	/// <summary>	Il buffer dello schermo, contenente le celle che
	/// 			verranno disegnate in questo ciclo. </summary>
	static ScreenBuffer buffer;

	/// <summary>	La dimensione (in celle) della console. </summary>
	static Size screenSize;


	/// <summary>	La dimensione da usare nel caso in cui non
	/// 			sia possibile caricare lo sprite. </summary>
	static const Size errorSize;

	/// <summary>	Lo sprite da usare nel caso in cui non sia
	/// 			possibile caricare lo sprite. </summary>
	static const Sprite errorSprite;

	/// <summary>	Carica uno sprite dato un percorso. </summary>
	///
	/// <remarks>	In caso di errore nel caricamento:
	/// 			-In modalità Debug, stampa l'errore
	/// 			-In modalità Release, restituisce lo sprite di errore. </remarks>
	///
	/// <param name="path">	Percorso del file .txt contenente lo sprite. </param>
	/// <param name="size">	[in,out] La dimensione dello sprite. </param>
	///
	/// <returns>	Lo sprite caricato. </returns>

	static Sprite loadSpriteFromFile(std::string path, Size& size);

	/// <summary>	Crea un nuovo sprite. </summary>
	///
	/// <param name="width">	   	La larghezza. </param>
	/// <param name="height">	   	L'altezza. </param>
	/// <param name="defaultValue">	Il carattere che verrà usato
	/// 							per riempire lo sprite. </param>
	///
	/// <returns>	Lo sprite creato. </returns>

	static Sprite newSprite(int width, int height, char defaultValue);

	/// <summary>	Prepara il modulo grafico. </summary>
	
	static void initialise();

	/// <summary>	Svuota il buffer, preparando il modulo
	/// 			per un nuovo ciclo. </summary>

	static void clearBuffer();

	/// <summary>	Disegna uno sprite. </summary>
	/// <param name="rect">  	Il Rect dello sprite. </param>
	/// <param name="sprite">	Lo sprite. </param>

	static void draw(Rect rect, Sprite sprite);

	/// <summary>	Disegna un GameObject. </summary>
	///
	/// <param name="gameObject">	Il GameObject da disegnare. </param>

	static void draw(ptr_GameObject gameObject);

	/// <summary>	Scrive del testo. </summary>
	///
	/// <param name="x">   	La coordinata x del testo. </param>
	/// <param name="y">   	La coordinata y del testo. </param>
	/// <param name="text">	Il testo. </param>

	static void write(float x, float y, std::string text);

	/// <summary>	Ridisegna la schermata. </summary>
	///
	/// <remarks>	Questo metodo garantisce che non
	/// 			ci siano residui di cicli precedenti,
	/// 			ma è significativamente più lento di
	/// 			<see cref="updateScreen()"> </remarks>

	static void redrawScreen();

	/// <summary>	Aggiorna esclusivamente le celle della
	/// 			console necessarie. </summary>

	static void updateScreen();
};