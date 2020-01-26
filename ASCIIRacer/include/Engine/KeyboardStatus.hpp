#pragma once

#include <vector>

#include "Key.hpp"

class KeyboardStatus
{
public:

	/// <summary>	I tasti appena premuti in questo ciclo. </summary>
	std::vector<Key> pressedKeys;

	/// <summary>	I tasti mantenuti premuti in questo ciclo. </summary>
	std::vector<Key> downKeys;

	/// <summary>	I tasti rilasciati in questo ciclo. </summary>
	std::vector<Key> releasedKeys;

	/// <summary>	Controlla se un tasto è appena stato premuto. </summary>
	///
	/// <param name="key">	Il tasto. </param>
	///
	/// <returns>	True se è stato appena premuto, false altrimenti. </returns>

	bool isPressed(Key key);

	/// <summary>	Controlla se un tasto è mantenuto premuto. </summary>
	///
	/// <param name="key">	Il tasto. </param>
	///
	/// <returns>	True se è mantenuto premuto, false altrimenti. </returns>
	bool isDown(Key key);

	/// <summary>	Controlla se un tasto è appena stato rilasciato. </summary>
	///
	/// <param name="key">	Il tasto. </param>
	///
	/// <returns>	True se è stato appena stato rilasciato, false altrimenti. </returns>
	bool isReleased(Key key);

	/// <summary>	Costruttore di default. </summary>

	KeyboardStatus();

	/// <summary>	Costruttore con pressed, down e released. </summary>
	/// <param name="pressedKeys"> 	I tasti appena premuti. </param>
	/// <param name="downKeys">	   	I tasti mantenuti premuti. </param>
	/// <param name="releasedKeys">	I tasti appena rilasciati. </param>

	KeyboardStatus(std::vector<Key> pressedKeys, std::vector<Key> downKeys, std::vector<Key> releasedKeys);
};